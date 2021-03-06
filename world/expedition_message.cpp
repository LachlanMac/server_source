/**
 * EQEmulator: Everquest Server Emulator
 * Copyright (C) 2001-2020 EQEmulator Development Team (https://github.com/EQEmu/Server)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY except by those people which sell it, which
 * are required to give you total support for your newly bought product;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 */

#include "dynamic_zone.h"
#include "expedition_message.h"
#include "cliententry.h"
#include "clientlist.h"
#include "zonelist.h"
#include "zoneserver.h"
#include "../common/servertalk.h"
#include <algorithm>

extern ClientList client_list;
extern ZSList zoneserver_list;

void ExpeditionMessage::HandleZoneMessage(ServerPacket* pack)
{
	switch (pack->opcode)
	{
	case ServerOP_ExpeditionCreate:
	{
		zoneserver_list.SendPacket(pack);
		break;
	}
	case ServerOP_ExpeditionDzAddPlayer:
	{
		ExpeditionMessage::AddPlayer(pack);
		break;
	}
	case ServerOP_ExpeditionDzMakeLeader:
	{
		ExpeditionMessage::MakeLeader(pack);
		break;
	}
	case ServerOP_ExpeditionCharacterLockout:
	{
		auto buf = reinterpret_cast<ServerExpeditionCharacterLockout_Struct*>(pack->pBuffer);
		auto cle = client_list.FindCLEByCharacterID(buf->character_id);
		if (cle && cle->Server())
		{
			cle->Server()->SendPacket(pack);
		}
		break;
	}
	case ServerOP_ExpeditionSaveInvite:
	{
		ExpeditionMessage::SaveInvite(pack);
		break;
	}
	case ServerOP_ExpeditionRequestInvite:
	{
		ExpeditionMessage::RequestInvite(pack);
		break;
	}
	}
}

void ExpeditionMessage::AddPlayer(ServerPacket* pack)
{
	auto buf = reinterpret_cast<ServerDzCommand_Struct*>(pack->pBuffer);

	ClientListEntry* invited_cle = client_list.FindCharacter(buf->target_name);
	if (invited_cle && invited_cle->Server())
	{
		// continue in the add target's zone
		buf->is_char_online = true;
		invited_cle->Server()->SendPacket(pack);
	}
	else
	{
		// add target not online, return to inviter
		ClientListEntry* inviter_cle = client_list.FindCharacter(buf->requester_name);
		if (inviter_cle && inviter_cle->Server())
		{
			inviter_cle->Server()->SendPacket(pack);
		}
	}
}

void ExpeditionMessage::MakeLeader(ServerPacket* pack)
{
	auto buf = reinterpret_cast<ServerDzCommandMakeLeader_Struct*>(pack->pBuffer);

	// notify requester (old leader) and new leader of the result
	ZoneServer* new_leader_zs = nullptr;
	ClientListEntry* new_leader_cle = client_list.FindCharacter(buf->new_leader_name);
	if (new_leader_cle && new_leader_cle->Server())
	{
		auto dz = DynamicZone::FindDynamicZoneByID(buf->dz_id);
		if (dz && dz->GetLeaderID() == buf->requester_id)
		{
			buf->is_success = dz->SetNewLeader(new_leader_cle->CharID());
		}

		buf->is_online = true;
		new_leader_zs = new_leader_cle->Server();
		new_leader_zs->SendPacket(pack);
	}

	// if old and new leader are in the same zone only send one message
	ClientListEntry* requester_cle = client_list.FindCLEByCharacterID(buf->requester_id);
	if (requester_cle && requester_cle->Server() && requester_cle->Server() != new_leader_zs)
	{
		requester_cle->Server()->SendPacket(pack);
	}
}

void ExpeditionMessage::SaveInvite(ServerPacket* pack)
{
	auto buf = reinterpret_cast<ServerDzCommand_Struct*>(pack->pBuffer);

	ClientListEntry* invited_cle = client_list.FindCharacter(buf->target_name);
	if (invited_cle)
	{
		// store packet on cle and re-send it when client requests it
		buf->is_char_online = true;
		pack->opcode = ServerOP_ExpeditionDzAddPlayer;
		invited_cle->SetPendingExpeditionInvite(pack);
	}
}

void ExpeditionMessage::RequestInvite(ServerPacket* pack)
{
	auto buf = reinterpret_cast<ServerExpeditionCharacterID_Struct*>(pack->pBuffer);
	ClientListEntry* cle = client_list.FindCLEByCharacterID(buf->character_id);
	if (cle)
	{
		auto invite_pack = cle->GetPendingExpeditionInvite();
		if (invite_pack && cle->Server())
		{
			cle->Server()->SendPacket(invite_pack.get());
		}
	}
}
