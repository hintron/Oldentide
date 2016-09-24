// Filename:    AccountManager.cpp
// Author:      Michael Hinton
// Date:        Jul_23_2016
// Purpose:     Account creation and authentication.
// NOTE:        OpenSSL 1.0.2h needs to be installed on the system! It is the LTS solution and will be supported until Dec 2019

#include <stdio.h>
#include <string.h>
#include <openssl/bn.h>
#include "SQLConnector.h"
#include "AccountManager.h"

// Authenticates an account and key
// @param account_name : The account to authenticate with.
// @param candidateKeyString_hex : The user-supplied key to autheticate with.
// @return : 1 if account successfully authenticated; 0 if not.
bool AccountManager::AuthenticateAccount(char *accountName, char *candidateKeyStringHex, 
                                         SQLConnector * sql) {
    // Authenticate - perform a key lookup and check
    bool success = false;
    // Create a container to hold the canonized key string hex
    char canonizedKeyStringHex[129];
    sql->GetAccountKey(accountName, canonizedKeyStringHex);

    // Initialize salt and generated key BIGNUMs
    BIGNUM *candidateKey = BN_new();
    BIGNUM *canonizedKey = BN_new();

    // Convert both keys to openssl bn BIGNUM
    BN_hex2bn(&candidateKey, candidateKeyStringHex);
    BN_hex2bn(&canonizedKey, canonizedKeyStringHex);

    //printf("Candidate Key: \n%s\n", candidateKeyStringHex);
    //printf("Canonized Key: \n%s\n", canonized_key_string_hex);

    // Compare both BIGNUMs to each other.
    // If the same, then return 1 (success)
    // If not, return 0.
    if (BN_cmp(canonizedKey, candidateKey) == 0) {
        //printf("Authentication is a success!!\n");
        success = true;
    }
    // Free the BIGNUMs and malloced strings
    BN_clear_free(canonizedKey);
    BN_clear_free(candidateKey);
    
    // TODO: Overwrite stack sensitive variables with with 0's,
    // since it doesn't get zeroed out once it's off the stack
    //for(int i = 0; i < EVP_MAX_MD_SIZE; ++i) {
    //    generated_key[i] = 0;
    //}
    //for(int i = strlen(); i > 0); --i) {
    //    password[i] = 0;
    //}
    // NOTE: clear_free variants are for sensitive info, opposed to just free.
    // The salts aren't sensitive, but the password and key are.
    // So just use clear_free for everything I can
    return success;
}

