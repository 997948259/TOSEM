#include "SQLiteManager.h"

/*
* Sets up the SQLite manager.
*/
SQLiteManager::SQLiteManager() :
_databaseConnection(nullptr)
{}

/*
* Closes the SQLite database.
*/
SQLiteManager::~SQLiteManager()
{
	sqlite3_close(_databaseConnection);
}

/*
* Loads in the database, establishes a connection to the database.
* @param bool if the database has successfully opened or not.
*/
bool SQLiteManager::load()
{
	int databaseConnectionStatus = sqlite3_open("F:/SQLiteInputFile/project-database.db", &_databaseConnection);

	if (databaseConnectionStatus)
	{
		cout << "Cannot open database." << endl;
		return false;
	}
	else
	{
		cout << "Database opened successfully." << endl;
		onLoad();
		return true;
	}
}

/*
* What happens when we save this database.
*/
void SQLiteManager::save()
{
	cout << "Totally saving." << endl;
}

/*
* What happens when this database has been opened.
*/
void SQLiteManager::onLoad()
{
	cout << "Loaded, now do something with the database." << endl;

	int databaseConnection;
	char* sqlCommand;
	sqlite3_stmt* trooperResults;

	// Select all of the objects in the Units table.
	sqlCommand = "SELECT * from Units";

	// Send the command to the SQLite database and fetch the results to the trooper results variable.
	databaseConnection = sqlite3_prepare_v2(_databaseConnection, sqlCommand, -1, &trooperResults, 0);

	// Loading trooper data!
	while (sqlite3_step(trooperResults) == SQLITE_ROW)
	{
		Trooper trooper;

		// Accessing the trooper data from the SQL database.
		trooper.trooperID(sqlite3_column_int(trooperResults, 0));
		trooper.trooperName(reinterpret_cast<const char*>(sqlite3_column_text(trooperResults, 1)));
		trooper.setRawAttack(static_cast<float>(sqlite3_column_double(trooperResults, 2)));
		trooper.setRawAttackRange(static_cast<float>(sqlite3_column_double(trooperResults, 3)));
		trooper.setBonusAttack(static_cast<float>(sqlite3_column_double(trooperResults, 4)));
		trooper.setBonusAttackRange(static_cast<float>(sqlite3_column_double(trooperResults, 5)));
		trooper.setAttackRange(sqlite3_column_int(trooperResults, 6));
		trooper.setRawDefence(static_cast<float>(sqlite3_column_double(trooperResults, 7)));
		trooper.setCriticalChance(static_cast<float>(sqlite3_column_double(trooperResults, 8)));
		trooper.setCriticalMultiplier(static_cast<float>(sqlite3_column_double(trooperResults, 9)));
		trooper.setEvasion(static_cast<float>(sqlite3_column_double(trooperResults, 10)));
		trooper.setCooldown(static_cast<float>(sqlite3_column_double(trooperResults, 11)));
		trooper.setMaxHealth(static_cast<float>(sqlite3_column_double(trooperResults, 12)));
		trooper.setMovement(sqlite3_column_int(trooperResults, 13));
		trooper.setNumberOfActions(sqlite3_column_int(trooperResults, 14));

		_trooperData.push_back(trooper);
	}
}

/*
* What happens when this database has been saved.
*/
void SQLiteManager::onSave()
{
	cout << "Saved." << endl;
}