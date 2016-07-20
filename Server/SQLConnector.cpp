// Filename:    SQLConnector.cpp
// Author:      Joseph DeVictoria
// Date:        Feb_29_2016
// Purpose:     SQL Connector class to handle SQLite3 queries.

#include "SQLConnector.h"
#include <iostream>
#include <string.h>
#include <sstream>

using namespace std;

SQLConnector::SQLConnector(){
    sqls = sqlite3_open("db/Oldentide.db", &database);
    if(sqls){
        cout << "Can't open database!" << endl;
        sqlite3_close(database);
    }
    else{
        cout << "Oldentide database opened successfully." << endl;
    }
}

SQLConnector::~SQLConnector(){
    sqlite3_close(database);
}

void SQLConnector::execute(string cmd){
    char *error_message = 0;

    sqls = sqlite3_exec(database, cmd.c_str(), &execute_callback, 0, &error_message);
    if (sqls != SQLITE_OK){
        cout << "Could not execute SQL query! Return Code:" << sqls << endl;
        //switch(sqls){
        //    case SQLITE_IOERR:
        //        cout << "Some kind of I/O error happened. Do you have permission(sudo)?" << endl;
        //        break;
        //    default:
        //        break;        
        //}
        //cout << "error code: " << sqls;
    }
    else {
        cout << "Executed Successfully. Return Code:" << sqls << endl;
    }

    if(error_message){
        // Print out the error message if any
        cout << "SQL ERROR MESSAGE: " << error_message << endl;
        // Free the error message, since it was alloced in exec()
        sqlite3_free(error_message);
    }
}

void SQLConnector::create_account(){
    std::stringstream query;
    query << "insert into accounts (account_name, key, salt, salt_iterations) values (\"Hintron\",\"key\",\"salty\",10)";
    execute(query.str()); 
}

void SQLConnector::list_accounts(){
    std::stringstream query;
    query << "select * from accounts";
    execute(query.str()); 
}

// Callback adapted from https://www.sqlite.org/quickstart.html
// This can't be a method, since it is being passed as a c function pointer
static int execute_callback(void *NotUsed, int argc, char **argv, char **azColName){
    int i;
    for(i = 0; i < argc; i++){
        cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL");
        cout << " | ";
    }
    cout << endl;
    return 0;
}



