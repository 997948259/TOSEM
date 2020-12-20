#pragma once

#include <iostream>
#include <vector>
#include "Trooper.h"
#include "DatabaseManager.h"
#include "sqlite3.h"

/*
 * Handles calls to the SQLite database.
 */
class SQLiteManager : public DatabaseManager
{
	public:
		SQLiteManager();
		~SQLiteManager();

		bool load() ;
		void save() ;

		/*
		 * Provides access to the trooper data gathered from the data base.
		 * @param const vector the data structure that holds all of the trooper data.
		 */
		inline vector<Trooper> const trooperData() const { return _trooperData; }

	protected:
		void onLoad() ;
		void onSave();

	private:
		sqlite3* _databaseConnection = nullptr;
		vector<Trooper> _trooperData;
};