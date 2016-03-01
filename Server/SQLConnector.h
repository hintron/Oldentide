// Filename:    SQLConnector.h
// Author:      Joseph DeVictoria
// Date:        Feb_29_2016
// Purpose:     Header for SQL Connector class.

#ifndef OLDENTIDE_SQLCONNECTOR_H
#define OLDENTIDE_SQLCONNECTOR_H

#include <string>
#include <sqlite3.h>

class SQLConnector{
    public:
        SQLConnector();
        ~SQLConnector();
        void execute(std::string cmd);
        void initDb();
    private:
        sqlite3 * database;
        int sqls;
};

#endif // OLDENTIDE_SQLCONNECTOR_H
