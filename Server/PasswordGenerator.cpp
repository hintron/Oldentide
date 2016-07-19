// Compile this file with the following command
// g++ PasswordGenerator.cpp -lcrypto -o passwordgen.o

// NOTE: OpenSSL 1.0.2h needs to be installed on the system! It is the LTS solution and will be supported until Dec 2019

#include <stdio.h>
#include <openssl/evp.h>
#include <string.h>
#include <openssl/bn.h>

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

#define MIN_PASSWORD_LENGTH 8
#define MAX_PASSWORD_LENGTH 64
#define SALT_BIT_SIZE 512
// Iterations should be calibrated so the whole process takes 200-1000 ms
// If it is any quicker, it defeats the point of salting and stretching!
// 2^20 iterations will effectively add 20 bits to the password
const long long ITERATIONS = 1 << 20;
// NOTE: The generated key depends on the number of iterations.

//
//// TESTING:
//
// Run this: 
//      ./passwordgen.o [password]
// This will generate a key using a randomly-created salt and the password.
// Copy the 512-bit salt hex string and paste it into this command using the same password:
//      ./passwordgen.o [password] [paste_salt_here]
// If the output keys for both commands are the same, then it worked properly!


// TODO: Modularize code for reuse, so creating a new key uses same code for return visits
// TODO: Time code and print that to output
main(int argc, char *argv[]) {
    EVP_MD_CTX *md_context;
    const EVP_MD *md_function;
    // TODO: I don't think I need a temp string. Need to test
    // NOTE: EVP_MAX_MD_SIZE is 64 (512 bits)
    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned int md_len, i;

    if(!argv[1]) {
        printf("Usage: ./passwordgen.o [password_to_salt] [salt_in_hex]\n");
        exit(1);
    }

    // get the password
    char * password = argv[1];
    // Check to make sure password is at least 8 chars and that it is not longer than 64 chars
    if(strlen(password) > MAX_PASSWORD_LENGTH){
        printf("Password is too large to process!\n");
        exit(0); 
    }
    else if(strlen(password) < MIN_PASSWORD_LENGTH){
        printf("Password is too small to process!\n" );
        exit(0); 
    }
    else {
        // Password is of a good length
    }
    

    printf("\n\nSalting and stretching the password...\n");

    printf("Hash Function: SHA-512\n");
    md_function = EVP_sha512();

    printf("Password: \"%s\"\n", password);

    BIGNUM * salt = BN_new();
    if(!argv[2]) {
        // Since argument was not supplied, generate a random salt
        // Create the random number (openssl should auto-seed from /dev/urandom)
        BN_rand(salt, SALT_BIT_SIZE, -1, 0);
    }
    else {
        // Have the second param be the salt (in hex), so that the key
        // can be manually regenerated if the salt is known
        // convert salt argument from hex to bn
        BN_hex2bn(&salt, argv[2]);     
    }

    int salt_bytes = BN_num_bytes(salt);
    int salt_bits = BN_num_bits(salt);
    unsigned char salt_string_bin[salt_bytes];
    int salt_length = BN_bn2bin(salt, salt_string_bin);
    
    printf("Salt (hex):\n");
    for(int i = 0; i < salt_length; i++){
        printf("%02x", salt_string_bin[i]);
    }
    printf("\n");
    printf("Salt length : bytes : bits\n%d : %d : %d\n", salt_length, salt_bytes, salt_bits);
    // Run through the stretching algorithm
    
    // md_temp_value needs to be initialized to all zeros, since it's on the stack
    for(int i = 0; i < EVP_MAX_MD_SIZE; ++i){
        md_value[i] = 0;
    } 

    printf("Iterations: %d\n", ITERATIONS);
    for (long long i = 0; i < ITERATIONS; ++i) {
        //printf("%dth iteration: \n", i);
        md_context = EVP_MD_CTX_create();
        EVP_DigestInit(md_context, md_function);
        // Append the previous hash, pasword, and salt together in this order: 
        //x = hash512(x || password || salt);
        EVP_DigestUpdate(md_context, md_value, EVP_MAX_MD_SIZE);
        EVP_DigestUpdate(md_context, password, strlen(password));
        EVP_DigestUpdate(md_context, salt_string_bin, salt_bytes);
        // Execute the hash and store it in md_value
        EVP_DigestFinal_ex(md_context, md_value, &md_len);
        // clean up md_context
        EVP_MD_CTX_destroy(md_context);
        // NOTE: EVP_DigestFinal() should == EVP_DigestFinal_ex() + EVP_MD_CTX_destroy()
    }
    // End loop

    printf("Final salted and stretched password/key is: \n");
    for(int i = 0; i < md_len; i++){
        printf("%02x", md_value[i]);
    }
    printf("\n");


    // TODO: Save the salt and the generated key (salted password) in the sqlite db
    // Make sure when storing the salt and key, that any leading zeros or zero bits are preserved!
    // TODO: Save the number of iterations used to generate the key in the db 

    //
    //// Free up memory allocations
    //

    // Clear the allocated BIGNUM pointer
    BN_clear_free(salt);

    // NOTE: clear_free variants are for sensitive info, opposed to just free.
    // The salts aren't sensitive, but the password and key are.
    // So just use clear_free for everything I can

    exit(0);
}


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
