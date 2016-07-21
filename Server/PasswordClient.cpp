// Compile this file with the following command:
// g++ PasswordClient.cpp SQLConnector.cpp AccountManager.cpp -lcrypto -lsqlite3 -std=c++11 -o passwordclient.o

#include <iostream>
#include <string.h>
#include "AccountManager.h"

int main(int argc, char *argv[]) {
    std::cout << std::endl << std::endl;
    if(!argv[1] || !argv[2]) {
        std::cout << "Usage: ./password_client.o account_name password [new]" << std::endl;
        exit(1);
    }

    // get the account name and password
    char * account_name = argv[1];
    char * password = argv[2];

    if(!AccountManager::check_password_length(password)){
        exit(1);
    }

    if(!AccountManager::sanitize_account_name(account_name)){
        exit(1);
    }

    if(argv[3]) {
        //
        //// Create a new account
        //
        if(AccountManager::create_new_account(account_name, password)){
            std::cout << "New account \"" << account_name << "\" successfully created!" << std::endl;
        }
        else {
            std::cout << "ERROR: Failed to create account \"" << account_name << "\"." << std::endl;
        }
    }
    else {
        //
        //// Authenticate - perform a key lookup and check
        //
        if(AccountManager::authenticate_account(account_name, password)){
            //std::cout << "Successfully authenticated account \"" << account_name << "\"!" << std::endl;
        }
        else {
            //std::cout << "ERROR: Failed to authenticate account \"" << account_name << "\"." << std::endl;
        }
    }
}

