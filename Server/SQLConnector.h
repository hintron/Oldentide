// Filename:    SQLConnector.h
// Author:      Joseph DeVictoria
// Date:        Feb_29_2016
// Purpose:     Header for SQL Connector class.

#ifndef OLDENTIDE_SQLCONNECTOR_H
#define OLDENTIDE_SQLCONNECTOR_H

#include "SQLiteCpp/SQLiteCpp.h"
#include "Character.h"
#include "Player.h"
#include "Npc.h"
#include <string>
#include <vector>
#include <set>

class SQLConnector{
    public:
        SQLConnector();
        ~SQLConnector();
        bool Execute(std::string cmd, bool quiet = false);
        bool ExecuteSqlFile(std::string filename);
        bool InsertAccount(std::string, std::string, std::string, std::string);
        bool InsertPlayer(Player newPlayer);
        void ListAccounts();
        std::vector<std::string> GetPlayerList(std::string account);
        std::set<Npc> PopulateNpcList();
        bool GetAccountSalt(char *, char *);
        int GetAccountKey(char *, char *);
    private:
        SQLite::Database db;
        int sqls;
};

// // This can't be a private method, because it needs to be passed as a pointer to sqlite3_exec()
// // and methods of a c++ class have a hidden function pointer to the class instance
// // See http://stackoverflow.com/a/8045331
// static int ExecuteCallback(void *, int, char **, char **);
// static int ReturnStringCallback(void *, int, char **, char **);
// static int ParsePlayerList(void *, int, char **, char **);
// static int ParseNpcs(void *, int, char **, char **);

#endif // OLDENTIDE_SQLCONNECTOR_H
