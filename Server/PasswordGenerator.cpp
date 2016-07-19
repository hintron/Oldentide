// Compile this file with the following command
// g++ PasswordGenerator.cpp -lcrypto -o passwordgen.o

// NOTE: OpenSSL 1.0.2h needs to be installed on the system! It is the LTS solution and will be supported until Dec 2019

#include <stdio.h>
#include <openssl/evp.h>
#include <string.h>
#include <openssl/bn.h>
// // TODO: Use uint8_t in place of unsigned char from stdtype?
// // #include <stdtype.h>
// // #include <assert.h>

// Terminology:
// message = plaintext
// message digest function = hash function
// message digest (MD) = digest = fingerprint = output of a hash function

// Create a program that will take an input password,
// generate a random salt, stretch the password for n iterations,
// save the salted password and salt in the sqlite db, and 
// time the process to see how long it took, sending an error if too quick (< 200ms)

#define MAX_PASSWORD_LENGTH 64
#define MIN_PASSWORD_LENGTH 8
#define SALT_BIT_SIZE 512

main(int argc, char *argv[]) {
    EVP_MD_CTX *md_context;
    const EVP_MD *md_function;
    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned char md_value_temp[EVP_MAX_MD_SIZE];
    unsigned int md_len, i;

    if(!argv[1]) {
        printf("Usage: ./passwordgen.o password-to-salt\n");
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

    printf("Using SHA-512\n");
    md_function = EVP_sha512();

    printf("Salting and stretching password \"%s\"\n", password);

    // TODO: Have a second param that is the salt, so that the key can be regenerated if the salt is known
    // If I can consistently regenerate the key from the password and salt, then it works
    
    // Generate at least a 256-bit salt
    BIGNUM * salt = BN_new();
    // Create the random number (openssl should auto-seed from /dev/urandom)
    BN_rand(salt, SALT_BIT_SIZE, -1, 0);
   
    int salt_bytes = BN_num_bytes(salt);
    int salt_bits = BN_num_bits(salt);
    unsigned char salt_string_bin[salt_bytes];
    // Convert the salt to other formats 
    //unsigned char * salt_string_bin;
    int salt_length = BN_bn2bin(salt, salt_string_bin);
    char * salt_string_hex = BN_bn2hex(salt);
    
    printf("Salt length - bytes - bits:\n%d - %d - %d\n", salt_length, salt_bytes, salt_bits);
    printf("Salt(hex):\n%s\n", salt_string_hex);

    // Run through the stretching algorithm

    /*
    // Pseudocode for salting and stretching a password
    // See pg 304 of Cryptography Engineering (21.2.1 - Salting and Stretching)
    
    x = 0
    // The salt is simply a random number that is stored alongside the key. Use at least a 256bit salt.
    // Each user needs a different salt, so an attacker would always have to recalculate the key per user,
    // even if the attacker guesses the same password (e.g. "password") for each user.
    salt = rand256()
    
    for (int i = 0; i < ITERATIONS; ++i) {
        // (note: || means append)
        x = hash512(x || password || salt);
    }
    
    key = x
    // Store the salt and the key in the db. The salt can be public.
    */



     /* Implementation */
    
    // md_temp_value needs to be initialized to all zeros, since it's on the stack
    for(int i = 0; i < EVP_MAX_MD_SIZE; ++i){
        md_value_temp[i] = 0;
    } 

    // Iterations should be calibrated so the whole process takes 200-1000 ms
    #define EXTRA_BITS_OF_SECURITY 20
    long long ITERATIONS = 1 << EXTRA_BITS_OF_SECURITY; // i.e. 2^20
    //long long ITERATIONS = 5;
    for (long long i = 0; i < ITERATIONS; ++i) {
        //printf("%dth iteration: \n", i);
        md_context = EVP_MD_CTX_create();
        EVP_DigestInit(md_context, md_function);
        // Append the previous hash, pasword, and salt together in this order: 
        //x = hash512(x || password || salt);
        EVP_DigestUpdate(md_context, md_value_temp, EVP_MAX_MD_SIZE);
        EVP_DigestUpdate(md_context, password, strlen(password));
        EVP_DigestUpdate(md_context, salt_string_bin, salt_bytes);
        // Execute the hash and store it in md_value
        EVP_DigestFinal_ex(md_context, md_value, &md_len);
        // clean up md_context
        EVP_MD_CTX_destroy(md_context);
        // NOTE: EVP_DigestFinal() should == EVP_DigestFinal_ex() + EVP_MD_CTX_destroy()

        if(i == 0){
            printf("Hash of 0th iteration: \n");
            for(int j = 0; j < md_len; j++){
                printf("%02x", md_value[j]);
            }
            printf("\n");
        }

        // Copy md_value to md_value_temp, since md_value is supposed to be a const char *
        for(int i=0; i < EVP_MAX_MD_SIZE; ++i){
            md_value_temp[i] = md_value[i];
        }

    }
    // End loop

    printf("Final salted and stretched password is: \n");
    for(i = 0; i < md_len; i++){
        printf("%02x", md_value[i]);
    }
    printf("\n");


    // TODO: Save the salt and the generated key (salted password) in the sqlite db

    //
    //// Free up memory allocations
    //

    // Free the salt hex string
    // NOTE: This function doesn't show up in the 
    // 1.0.2 docs (shows up in master), but it works
    OPENSSL_free(salt_string_hex);
    // Clear the allocated BIGNUM pointer
    BN_clear_free(salt);

    // NOTE: clear_free variants are for sensitive info, opposed to just free.
    // The salts aren't sensitive, but the password and key are.
    // So just use clear_free for everything I can





    exit(0);
}



