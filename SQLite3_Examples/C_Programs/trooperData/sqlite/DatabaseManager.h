#pragma once

/*
 * Provides a standard base for any database manager.
 */
class DatabaseManager
{
	public:
		explicit DatabaseManager() {}
		virtual ~DatabaseManager() {}
		virtual bool load() { return false; }
		virtual void save() {}

	protected:
		virtual void onLoad() {}
		virtual void onSave() {}
};

