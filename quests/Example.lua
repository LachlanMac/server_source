function event_click_door(e)
    local door_id = e.door:GetDoorID();
    eq.debug("Door: " .. door_id .. " clicked");
  
    if (door_id == 3) then
      -- zone entry is gated via flag checks but expedition can be created if only requester is eligible
      local qglobals = eq.get_qglobals(e.self);
      local has_signets = qglobals["oow_rss_taromani_insignias"]
      local has_trials = qglobals["oow_mpg_raids_complete"]
      local is_gm = (e.self:Admin() >= 80 and e.self:GetGM())
  
      -- the anguish door goes on a 60s cooldown after an expedition request
      -- while on cooldown clicking the door results in "feel the door" message and nothing happens
  
      -- when gate is not already on cooldown:
      -- if requester is in a non-anguish expedition then nothing happens
      -- if requester is in an anguish expedition it zones in without any message
      -- if above conditions pass, a creation request occurs and gate goes on cooldown ("the door swings wide" message)
      -- (unnecessary) cooldown added on a successful creation is probably to compensate for live's instance startup time
      local now = os.time()
      local is_anguish_door_on_cooldown = (anguish_door_cooldown_expire_time > now)
  
      if not is_gm and is_anguish_door_on_cooldown then
        e.self:Message(13, "You can feel the door to Anguish opening underneath your hand.")
      elseif not is_gm and not has_trials then -- unknown original live message
        e.self:Message(13, "You must complete the Muramite Proving Grounds raid trials.")
      elseif not is_gm and not has_signets then
        e.self:Message(13, "Though you carry the seal to enter Anguish, the Fallen Palace, you would be torn asunder by the harsh environment were you to venture within.  You will need to find a way to protect yourself from the powers of Discord.")
      else
        local dz = e.self:GetExpedition()
        if dz.valid and dz:GetZoneName() == "anguish" then
          e.self:MovePCDynamicZone("anguish")
        elseif not dz.valid then
          e.self:Message(15, "The door swings wide and allows you entrance to Anguish, the Fallen Palace.")
  
          dz = e.self:CreateExpedition(expedition_info)
          if dz.valid then
            dz:SetReplayLockoutOnMemberJoin(false) -- live doesn't add "Replay Timer" to new members after spawning aug droppers (bug or intentional?)
          else
            anguish_door_cooldown_expire_time = now + 60
            eq.debug(string.format("Anguish gate placed on 60s cooldown due to failed request by [%s]", e.self:GetCleanName()))
          end
        end
      end
    end
  end
  