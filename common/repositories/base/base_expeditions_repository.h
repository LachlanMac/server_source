/**
 * DO NOT MODIFY THIS FILE
 *
 * This repository was automatically generated and is NOT to be modified directly.
 * Any repository modifications are meant to be made to the repository extending the base.
 * Any modifications to base repositories are to be made by the generator only
 *
 * @generator ./utils/scripts/generators/repository-generator.pl
 * @docs https://eqemu.gitbook.io/server/in-development/developer-area/repositories
 */

#ifndef EQEMU_BASE_EXPEDITIONS_REPOSITORY_H
#define EQEMU_BASE_EXPEDITIONS_REPOSITORY_H

#include "../../database.h"
#include "../../string_util.h"
#include <ctime>

class BaseExpeditionsRepository {
public:
	struct Expeditions {
		int id;
		int dynamic_zone_id;
		int add_replay_on_join;
		int is_locked;
	};

	static std::string PrimaryKey()
	{
		return std::string("id");
	}

	static std::vector<std::string> Columns()
	{
		return {
			"id",
			"dynamic_zone_id",
			"add_replay_on_join",
			"is_locked",
		};
	}

	static std::vector<std::string> SelectColumns()
	{
		return {
			"id",
			"dynamic_zone_id",
			"add_replay_on_join",
			"is_locked",
		};
	}

	static std::string ColumnsRaw()
	{
		return std::string(implode(", ", Columns()));
	}

	static std::string SelectColumnsRaw()
	{
		return std::string(implode(", ", SelectColumns()));
	}

	static std::string TableName()
	{
		return std::string("expeditions");
	}

	static std::string BaseSelect()
	{
		return fmt::format(
			"SELECT {} FROM {}",
			SelectColumnsRaw(),
			TableName()
		);
	}

	static std::string BaseInsert()
	{
		return fmt::format(
			"INSERT INTO {} ({}) ",
			TableName(),
			ColumnsRaw()
		);
	}

	static Expeditions NewEntity()
	{
		Expeditions entry{};

		entry.id                 = 0;
		entry.dynamic_zone_id    = 0;
		entry.add_replay_on_join = 1;
		entry.is_locked          = 0;

		return entry;
	}

	static Expeditions GetExpeditionsEntry(
		const std::vector<Expeditions> &expeditionss,
		int expeditions_id
	)
	{
		for (auto &expeditions : expeditionss) {
			if (expeditions.id == expeditions_id) {
				return expeditions;
			}
		}

		return NewEntity();
	}

	static Expeditions FindOne(
		Database& db,
		int expeditions_id
	)
	{
		auto results = db.QueryDatabase(
			fmt::format(
				"{} WHERE id = {} LIMIT 1",
				BaseSelect(),
				expeditions_id
			)
		);

		auto row = results.begin();
		if (results.RowCount() == 1) {
			Expeditions entry{};

			entry.id                 = atoi(row[0]);
			entry.dynamic_zone_id    = atoi(row[1]);
			entry.add_replay_on_join = atoi(row[2]);
			entry.is_locked          = atoi(row[3]);

			return entry;
		}

		return NewEntity();
	}

	static int DeleteOne(
		Database& db,
		int expeditions_id
	)
	{
		auto results = db.QueryDatabase(
			fmt::format(
				"DELETE FROM {} WHERE {} = {}",
				TableName(),
				PrimaryKey(),
				expeditions_id
			)
		);

		return (results.Success() ? results.RowsAffected() : 0);
	}

	static int UpdateOne(
		Database& db,
		Expeditions expeditions_entry
	)
	{
		std::vector<std::string> update_values;

		auto columns = Columns();

		update_values.push_back(columns[1] + " = " + std::to_string(expeditions_entry.dynamic_zone_id));
		update_values.push_back(columns[2] + " = " + std::to_string(expeditions_entry.add_replay_on_join));
		update_values.push_back(columns[3] + " = " + std::to_string(expeditions_entry.is_locked));

		auto results = db.QueryDatabase(
			fmt::format(
				"UPDATE {} SET {} WHERE {} = {}",
				TableName(),
				implode(", ", update_values),
				PrimaryKey(),
				expeditions_entry.id
			)
		);

		return (results.Success() ? results.RowsAffected() : 0);
	}

	static Expeditions InsertOne(
		Database& db,
		Expeditions expeditions_entry
	)
	{
		std::vector<std::string> insert_values;

		insert_values.push_back(std::to_string(expeditions_entry.id));
		insert_values.push_back(std::to_string(expeditions_entry.dynamic_zone_id));
		insert_values.push_back(std::to_string(expeditions_entry.add_replay_on_join));
		insert_values.push_back(std::to_string(expeditions_entry.is_locked));

		auto results = db.QueryDatabase(
			fmt::format(
				"{} VALUES ({})",
				BaseInsert(),
				implode(",", insert_values)
			)
		);

		if (results.Success()) {
			expeditions_entry.id = results.LastInsertedID();
			return expeditions_entry;
		}

		expeditions_entry = NewEntity();

		return expeditions_entry;
	}

	static int InsertMany(
		Database& db,
		std::vector<Expeditions> expeditions_entries
	)
	{
		std::vector<std::string> insert_chunks;

		for (auto &expeditions_entry: expeditions_entries) {
			std::vector<std::string> insert_values;

			insert_values.push_back(std::to_string(expeditions_entry.id));
			insert_values.push_back(std::to_string(expeditions_entry.dynamic_zone_id));
			insert_values.push_back(std::to_string(expeditions_entry.add_replay_on_join));
			insert_values.push_back(std::to_string(expeditions_entry.is_locked));

			insert_chunks.push_back("(" + implode(",", insert_values) + ")");
		}

		std::vector<std::string> insert_values;

		auto results = db.QueryDatabase(
			fmt::format(
				"{} VALUES {}",
				BaseInsert(),
				implode(",", insert_chunks)
			)
		);

		return (results.Success() ? results.RowsAffected() : 0);
	}

	static std::vector<Expeditions> All(Database& db)
	{
		std::vector<Expeditions> all_entries;

		auto results = db.QueryDatabase(
			fmt::format(
				"{}",
				BaseSelect()
			)
		);

		all_entries.reserve(results.RowCount());

		for (auto row = results.begin(); row != results.end(); ++row) {
			Expeditions entry{};

			entry.id                 = atoi(row[0]);
			entry.dynamic_zone_id    = atoi(row[1]);
			entry.add_replay_on_join = atoi(row[2]);
			entry.is_locked          = atoi(row[3]);

			all_entries.push_back(entry);
		}

		return all_entries;
	}

	static std::vector<Expeditions> GetWhere(Database& db, std::string where_filter)
	{
		std::vector<Expeditions> all_entries;

		auto results = db.QueryDatabase(
			fmt::format(
				"{} WHERE {}",
				BaseSelect(),
				where_filter
			)
		);

		all_entries.reserve(results.RowCount());

		for (auto row = results.begin(); row != results.end(); ++row) {
			Expeditions entry{};

			entry.id                 = atoi(row[0]);
			entry.dynamic_zone_id    = atoi(row[1]);
			entry.add_replay_on_join = atoi(row[2]);
			entry.is_locked          = atoi(row[3]);

			all_entries.push_back(entry);
		}

		return all_entries;
	}

	static int DeleteWhere(Database& db, std::string where_filter)
	{
		auto results = db.QueryDatabase(
			fmt::format(
				"DELETE FROM {} WHERE {}",
				TableName(),
				where_filter
			)
		);

		return (results.Success() ? results.RowsAffected() : 0);
	}

	static int Truncate(Database& db)
	{
		auto results = db.QueryDatabase(
			fmt::format(
				"TRUNCATE TABLE {}",
				TableName()
			)
		);

		return (results.Success() ? results.RowsAffected() : 0);
	}

};

#endif //EQEMU_BASE_EXPEDITIONS_REPOSITORY_H
