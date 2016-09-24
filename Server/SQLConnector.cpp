// Filename:    SQLConnector.cpp
// Author:      Joseph DeVictoria
// Date:        Feb_29_2016
// Purpose:     SQL Connector class to handle SQLite3 queries.

#include "SQLConnector.h"
#include "Utils.h"
#include <iostream>
#include <string.h>
#include <sstream>

SQLConnector::SQLConnector() {
    sqls = sqlite3_open("db/Oldentide.db", &database);
    if (sqls) {
        std::cout << "Can't open database!" << std::endl;
        // Is this needed?
        sqlite3_close(database);
    }
    else {
        std::cout << "Oldentide database opened successfully." << std::endl;
    }
}

SQLConnector::~SQLConnector() {
    sqlite3_close(database);
}

// Executes a static SQL statement
int SQLConnector::Execute(std::string cmd) {
    char *errorMessage = NULL;
    sqls = sqlite3_exec(database, cmd.c_str(), &ExecuteCallback, 0, &errorMessage);
    if (sqls != SQLITE_OK) {
        std::cout << "Could not Execute SQL query! Return Code:" << sqls << std::endl;
    }
    if (errorMessage) {
        // Print out the error message if any
        std::cout << "SQL ERROR MESSAGE: " << errorMessage << std::endl;
        // Free the error message, since it was alloced in exec()
        sqlite3_free(errorMessage);
    }
    return 0;
}

// Insert a new account record.
bool SQLConnector::InsertAccount(char *accountName, char *key, char *salt) {
    std::stringstream query;
    // Sanitize key, salt, and account name
    if (!utils::SanitizeAccountName(accountName)) {
        std::cout << "Account Name is invalid! Cannot insert account record" << std::endl;
        return false;
    }
    if (!utils::SanitizeHexString(key)) {
        std::cout << "Key is invalid! Cannot insert account record" << std::endl;
        return false;
    }
    if (!utils::SanitizeHexString(salt)) {
        std::cout << "Salt is invalid! Cannot insert account record" << std::endl;
        return false;
    }
    query << "insert into accounts (accountname, key, salt) values (";
    query << "\"" << accountName << "\",";
    query << "\"" << key << "\",";
    query << "\"" << salt << "\")";
    Execute(query.str());
    if (sqls == SQLITE_OK) {
        return true;
    }
    else {
        return false;
    }
}

// Lists all the accounts
void SQLConnector::ListAccounts() {
    std::stringstream query;
    query << "select * from accounts ORDER BY accountname";
    Execute(query.str());
}

// Return the salt for the passed account
bool SQLConnector::GetAccountSalt(char *accountName, char *saltStringHex) {
    // Sanitize the account name before preceeding
    if (!utils::SanitizeAccountName(accountName)) {
        return false;
    }
    char *errorMessage = NULL;
    std::stringstream query;
    query << "select salt from accounts where accountname = \"" << accountName << "\"";
    // The fourth param is passed to the callback function as a void pointer to the first param
    sqls = sqlite3_exec(database, query.str().c_str(), &ReturnStringCallback, saltStringHex, &errorMessage);
    if (sqls != SQLITE_OK) {
        std::cout << "Could not Execute SQL query! Return Code:" << sqls << std::endl;
    }
    if (errorMessage) {
        // Print out the error message if any
        std::cout << "SQL ERROR MESSAGE: " << errorMessage << std::endl;
        // Free the error message, since it was alloced in exec()
        sqlite3_free(errorMessage);
        return false;
    }
    // Check to see if the salt was retrieved
    if (utils::SanitizeHexString(saltStringHex)) {
        return true;
    }
    else {
        return false;
    }

}

// Returns the key to the passed account
int SQLConnector::GetAccountKey(char *accountName, char *keyStringHex) {
    // Sanitize the account name before preceeding
    if (!utils::SanitizeAccountName(accountName)) {
        return 0;
    }
    char *errorMessage = NULL;
    std::stringstream query;
    query << "select key from accounts where accountname = \"" << accountName << "\"";
    //std::cout << query.str() << std::endl;
    // The fourth param is passed to the callback function as a void pointer to the first param
    sqls = sqlite3_exec(database, query.str().c_str(), &ReturnStringCallback, keyStringHex, &errorMessage);
    if (sqls != SQLITE_OK) {
        std::cout << "Could not Execute SQL query! Return Code:" << sqls << std::endl;
    }
    if (errorMessage) {
        // Print out the error message if any
        std::cout << "SQL ERROR MESSAGE: " << errorMessage << std::endl;
        // Free the error message, since it was alloced in exec()
        sqlite3_free(errorMessage);
    }
    return 1;
}

// A generic callback function to sqlite3_exec() that copies a c string in the first column
// of the returned row into stringToReturn. This function assumes that only one record will be
// in the result set, or else the return value will be the value in the last row processed.
static int ReturnStringCallback(void *stringToReturn, int argc, char **argv, char **azColName) {
    strcpy((char *)stringToReturn, argv[0]);
    return 0;
}

// This is a generic callback that simply prints to screen all the values
// of the returned row after a query. Callback adapted from https://www.sqlite.org/quickstart.html
static int ExecuteCallback(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    for(i = 0; i < argc; i++) {
        std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL");
        std::cout << " | ";
    }
    std::cout << std::endl;
    return 0;
}
