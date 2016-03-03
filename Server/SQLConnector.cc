// Filename:    SQLConnector.h
// Author:      Joseph DeVictoria
// Date:        Feb_29_2016
// Purpose:     SQL Connector class to handle SQLite3 queries.

#include "SQLConnector.h"
#include <iostream>
#include <string.h>

using namespace std;

SQLConnector::SQLConnector(){
    sqls = sqlite3_open("db/Oldentide.db", &database);
    if(sqls){
        cout << "Can't open database!" << endl;
    }
    else{
        cout << "Oldentide database opened successfully." << endl;
    }
}

SQLConnector::~SQLConnector(){
    sqlite3_close(database);
}

void SQLConnector::execute(string cmd){
    sqls = sqlite3_exec(database, cmd.c_str(), 0, 0, NULL);
    if (sqls != SQLITE_OK){
        cout << "Could not execute SQL query!" << endl;
    }
    else {
        cout << sqls;
    }
}
