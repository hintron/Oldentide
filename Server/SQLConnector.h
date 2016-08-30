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
        int Execute(std::string cmd);
        int InsertAccount(char *, char *, char *);
        void ListAccounts();
        int GetAccountSalt(char *, char *);
        int GetAccountKey(char *, char *);
    private:
        sqlite3 * database;
        int sqls;
};

// This can't be a private method, because it needs to be passed as a pointer to sqlite3_exec()
// and methods of a c++ class have a hidden function pointer to the class instance
// See http://stackoverflow.com/a/8045331
static int ExecuteCallback(void *, int, char **, char **);
static int ReturnStringCallback(void *, int, char **, char **);

#endif // OLDENTIDE_SQLCONNECTOR_H
