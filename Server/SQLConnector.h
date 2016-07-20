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
        void create_account(char *, char *, char *, long long);
        void list_accounts();
    private:
        sqlite3 * database;
        int sqls;
};

// This can't be a private method, because it needs to be passed as a pointer to sqlite3_exec()
// and methods of a c++ class have a hidden function pointer to the class instance
// See http://stackoverflow.com/a/8045331  
static int execute_callback(void *, int, char **, char **);

#endif // OLDENTIDE_SQLCONNECTOR_H
