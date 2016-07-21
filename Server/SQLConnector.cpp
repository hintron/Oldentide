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

/**
    Executes a static SQL statement

    NOTE: Make sure there is no way for a user to inject arbitrary SQL into the passed statement!
    Either sanitize the input thoroughly or don't use this command. You might need to use a
    parameterized query instead, which this command doesn't support.
**/
void SQLConnector::execute(string cmd){
    char *error_message = NULL;

    sqls = sqlite3_exec(database, cmd.c_str(), &execute_callback, 0, &error_message);
    if (sqls != SQLITE_OK){
        cout << "Could not execute SQL query! Return Code:" << sqls << endl;
    }
    else {
        cout << "Executed Successfully. Return Code:" << sqls << endl;
    }

    if(error_message){
        // Print out the error message if any
        cout << "SQL ERROR MESSAGE: " << error_message << endl;
        // Free the error message, since it was alloced in exec()
        // TODO: Is this needed?
        sqlite3_free(error_message);
    }
}

// TODO: Sanitize Key, salt, and iterations as well?
/**
    Created a new account record.

    @param account_name: IN. A c string that has already been sanitized to make sure it only has characters
                            a-z,A-Z,0-9,_ If not sanitized, could lead to SQL Injection!
    @param key: IN. A c string of the key for the account, already generated. Will be a string of hex.
    @param salt: IN. A c string of the salt used to generate the key. Will be a string of hex.
    @param iterations: IN. The number of iterations the key_generator algorithm used.
**/
void SQLConnector::create_account(char *account_name, char *key, char *salt, long long iterations){
    std::stringstream query;
    query << "insert into accounts (account_name, key, salt, salt_iterations) values (";
    query << "trim(\"" << account_name << "\"),";
    query << "\"" << key << "\",";
    query << "\"" << salt << "\",";
    query << iterations << ")";
    execute(query.str()); 
}

// TODO: Create a paging mechanism - save a page variable and use LIMIT and OFFSET
/**
    Lists all the accounts
**/
void SQLConnector::list_accounts(){
    std::stringstream query;
    query << "select * from accounts";
    execute(query.str()); 
}

// Whew... paramaterization makes it so I can't use sqlite3_exec, which makes things way more verbose
/**
    @param account_name: IN. A c string on the account_name to look the salt up. It should be screened
                                 so it is ONLY an alphanumeric string to prevent SQL injection attacks
    @param salt_string_hex: OUT. An empty c string allocated to 129 bytes. This is where the salt will
                             be stored.
    @return : Returns 1 if salt was found, 0 otherwise (not found, failure, etc)
**/
int SQLConnector::get_account_salt(char *account_name, const unsigned char *salt_string_hex){
    std::stringstream query;
    // Trim whitespace from account name with trim function
    // TODO: Use the quote() function to quote out " and ' - is it needed with parameterization?
    query << "select * from accounts where account_name = trim(?)";
    sqlite3_stmt *statement; 
    sqlite3_prepare_v2(database, query.str().c_str(), -1, &statement, NULL);
    // Negative number makes it read from account_name until it hits nul character
    // SQLITE_STATIC indicates that account_name doesn't need a destructor function
    sqlite3_bind_text(statement, 1, account_name, -1, SQLITE_STATIC);
    // NOTE: Column 3 should be the salt column! Don't change db definition!
    // TODO: Do a for loop until I find the clumn index that matches "salt" using sqlite3_column_name?
    // use strcmp to compare returned column name with "salt" to see if it is accurate
    // TODO: Do this in the constructor once? SELECT * FROM accounts LIMIT 1
    int column_salt = 3;
    int rc = sqlite3_step(statement);
    int return_value = 0;
    if(rc == SQLITE_ROW){
        // Process just the first row, since there should only be one record
        //int salt_bytes = sqlite3_column_bytes(statement, column_salt); 
        //cout << "Account found! The salt is " << salt_bytes << "+1 bytes!" << endl;
        // Get the salt text
        const unsigned char * salt_string_hex_temp = sqlite3_column_text(statement, column_salt);
        // sqlite3_column_text returns a string pointer that sqlite will autodeestroy soon
        // So, we need to copy it to a place that won't get destroyed after returning from this function 
        strcpy((char *)salt_string_hex, (char *)salt_string_hex_temp);        
        cout << "Salt hex from db: " <<  salt_string_hex << endl;
        return_value = 1;
    }
    else if(rc == SQLITE_DONE){
        // User account wasn't found
        cout << "Account wasn't found..." << endl;
    }
    else{
        cout << "An SQL error occurred. Return code: " << rc << endl;
    }
    sqlite3_finalize(statement);
    return return_value;
}

/**
    Returns the account key

    @param account_name : IN. The name of the account to authenticate. Needs to be sanitized!
    @param key : IN. The key generated by the user to authenticate. Needs to be sanitized!
    @return : 1 on successful authentication, 0 if authentication failed.
**/
//int get_account_key(char *account_name, char * key_candidate){
    // Get the record for the passed account name, if it exists

    // Return the actual key from the record

//}

// TODO: Move this to password manager's authenticate_account function
// Convert both keys to openssl bn BIGNUM
// Compare both BIGNUMs to each other.
// If the same, then return 1 (success)
// If not, return 0.


// Callback adapted from https://www.sqlite.org/quickstart.html
// This can't be a method, since it is being passed as a c function pointer
// TODO: Should this be here? Or inside the execute method? Is that even possible?
// NOTE: This callback is invoked for each returned ROW
// This will NOT be called after create, update, or delete calls 
// argc is number of columns in the row
// argv stores the column values of the row
// azColName stores the column names in alphabetical order
static int execute_callback(void *NotUsed, int argc, char **argv, char **azColName){
    int i;
    for(i = 0; i < argc; i++){
        cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL");
        cout << " | ";
    }
    cout << endl;
    return 0;
}



