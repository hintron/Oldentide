// NOTE: OpenSSL 1.0.2h needs to be installed on the system! It is the LTS solution and will be supported until Dec 2019

#include <stdio.h>
//#include <openssl/evp.h>
#include <string.h>
#include <openssl/bn.h>
#include "SQLConnector.h"
#include "AccountManager.h"


/**
    CLIENT.

    @param account_name : The account_name of the new account to create.
    @param password : The password that will be used to generate the key 
                    for the new account to create. It will NOT be stored.

    @return : Returns 1 if account was successfully created, 0 otherwise.
**/
//int AccountManager::create_new_account(char *account_name, char *salt_string_hex, char *generated_key_string_hex){
//    // Save the salt and the generated key (salted password) in the sqlite db
//    // Save the number of iterations used to generate the key in the db
//    SQLConnector *sql = new SQLConnector();
//    printf("Creating new account and saving account_name, salt, key, and iterations\n");
//    int success = 0;
//    //if(sql->insert_account(account_name, generated_key_string_hex, salt_string_hex, iterations)){
//    //    success = 1;
//    //}
//    //else {
//    //    printf("Unable to insert account record into database...\n");
//    //}
//    //printf("Listing all created accounts...\n");
//    //sql->list_accounts();
//
//    //
//    //// Free up memory allocations
//    //
//    delete sql;
//    // TODO: Use clear_free() version - might need crypto.h though
//
//    // TODO: Overwrite stack sensitive variables with with 0's,
//    // since it doesn't get zeroed out once it's off the stack
//    //for(int i = 0; i < EVP_MAX_MD_SIZE; ++i){
//    //    generated_key[i] = 0;
//    //}
//    //for(int i = strlen(); i > 0); --i){
//    //    password[i] = 0;
//    //}
//    // NOTE: clear_free variants are for sensitive info, opposed to just free.
//    // The salts aren't sensitive, but the password and key are.
//    // So just use clear_free for everything I can
//    return success;
//}

/**
    Authenticates an account and key
    
    @param account_name : The account to authenticate with.
    @param candidate_key_string_hex : The user-supplied key to autheticate with.

    @return : 1 if account successfully authenticated; 0 if not.
**/
int AccountManager::authenticate_account(char *account_name, char *candidate_key_string_hex){
    //
    //// Authenticate - perform a key lookup and check
    //
    int success = 0;
    SQLConnector *sql = new SQLConnector();
    // Create a container to hold the canonized key string hex
    char canonized_key_string_hex[129];
    sql->get_account_key(account_name, canonized_key_string_hex);

    // Initialize salt and generated key BIGNUMs
    BIGNUM *candidate_key = BN_new();
    BIGNUM *canonized_key = BN_new();

    // Convert both keys to openssl bn BIGNUM
    BN_hex2bn(&candidate_key, candidate_key_string_hex);
    BN_hex2bn(&canonized_key, canonized_key_string_hex);

    printf("Candidate Key: \n%s\n", candidate_key_string_hex);
    printf("Canonized Key: \n%s\n", canonized_key_string_hex);

    // Compare both BIGNUMs to each other.
    // If the same, then return 1 (success)
    // If not, return 0.
    if(BN_cmp(canonized_key, candidate_key) == 0){
        printf("Authentication is a success!!\n");
        success = 1;
    }
    // Free the BIGNUMs and malloced strings
    BN_clear_free(canonized_key);
    BN_clear_free(candidate_key);
    
    //
    //// Free up memory allocations
    //

    delete sql;
    // TODO: Overwrite stack sensitive variables with with 0's,
    // since it doesn't get zeroed out once it's off the stack
    //for(int i = 0; i < EVP_MAX_MD_SIZE; ++i){
    //    generated_key[i] = 0;
    //}
    //for(int i = strlen(); i > 0); --i){
    //    password[i] = 0;
    //}
    // NOTE: clear_free variants are for sensitive info, opposed to just free.
    // The salts aren't sensitive, but the password and key are.
    // So just use clear_free for everything I can
    return success;
}

//
//// Terminology:
//
// message = plaintext
// message digest function = hash function
// message digest (MD) = digest = fingerprint = output of a hash function

//
//// Task:
//
// Create a program that will take an input password,
// generate a random salt, stretch the password for n iterations,
// save the salted password and salt in the sqlite db, and
// time the process to see how long it took, sending an error if too quick (< 200ms)

/*
// Pseudocode for salting and stretching a password
// See pg 304 of Cryptography Engineering (21.2.1 - Salting and Stretching)

x = 0
// The salt is simply a random number that is stored alongside the key. Use at least a 256bit salt.
// Each user needs a different salt, so an attacker would always have to recalculate the key per user,
// even if the attacker guesses the same password (e.g. "password") for each user.
salt = rand256()

for (i = 0; i < ITERATIONS; ++i) {
    // (note: || means append)
    x = hash512(x || password || salt)
}

key = x
// Store the salt and the key in the db. The salt can be public.
*/
