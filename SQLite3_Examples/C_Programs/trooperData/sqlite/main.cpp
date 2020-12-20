#include "SQLiteManager.h"

/*
* Entry point for the application.
*/
int main()
{
	// Setting up the sqlite database.
	SQLiteManager sqliteManager;
	sqliteManager.load();

	if (!sqliteManager.trooperData().empty())
	{
		// Looping through the trooper data setup in SQLite Studio.
		for (size_t i = 0; i < sqliteManager.trooperData().size(); ++i)
		{
			// Displaying trooper information.
			Trooper trooper = sqliteManager.trooperData()[i];
			string messagePrefix = trooper.trooperName() + " ";
			cout << messagePrefix << "Raw Attack = " << trooper.rawAttack() << endl;
		}
	}

	return 0;
}