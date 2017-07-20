#ifndef SAVE_H
#define SAVE_H

#include <string>
#include "SQLite\sqlite3.h"

class Universe;

using std::string;

class Save {
public:
	Save();

private:
	string sqlStr;

	sqlite3 *database;
	sqlite3_stmt *statement;

};
#endif
