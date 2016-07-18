// Compile this file with the following command
// g++ PasswordGenerator.cpp -lcrypto -o passwordgen.o

// NOTE: OpenSSL 1.0.2h needs to be installed on the system! It is the LTS solution and will be supported until Dec 2019

#include <stdio.h>
#include <openssl/evp.h>
#include <string.h>

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
main(int argc, char *argv[]) {
    EVP_MD_CTX *md_context;
    const EVP_MD *md_function;
    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned int md_len, i;

    if(!argv[1]) {
        printf("Usage: ./passwordgen.o password-to-salt\n");
        exit(1);
    }

    printf("Using SHA-512\n");
    md_function = EVP_sha512();

    printf("Salting and stretching password \"%s\"\n", argv[1]);
    
    // TODO: get the password
    // TODO: Check to make sure password is at least 8 chars and that it is not longer than 64 chars

    // TODO: Generate at least a 256-bit salt


    md_context = EVP_MD_CTX_create();
    EVP_DigestInit(md_context, md_function);
    // Set the password to be hashed
    EVP_DigestUpdate(md_context, argv[1], strlen(argv[1]));
    // You can add multiple strings to the message before executing the final digest
    //EVP_DigestUpdate(md_context, mess2, strlen(mess2));
    // Execute the hash and clean up md_context
    EVP_DigestFinal_ex(md_context, md_value, &md_len);
    EVP_MD_CTX_destroy(md_context);
    // NOTE: EVP_DigestFinal() == EVP_DigestFinal_ex() + EVP_MD_CTX_free()





  
    printf("Digest is: \n");
    for(i = 0; i < md_len; i++)
        printf("%02x", md_value[i]);
    printf("\n");



// /*
// // Pseudocode for salting and stretching a password
// // See pg 304 of Cryptography Engineering (21.2.1 - Salting and Stretching)

// x = 0
// // The salt is simply a random number that is stored alongside the key. Use at least a 256bit salt.
// // Each user needs a different salt, so an attacker would always have to recalculate the key per user,
// // even if the attacker guesses the same password (e.g. "password") for each user.
// salt = rand256()

// for (int i = 0; i < ITERATIONS; ++i) {
//     // (note: || means append)
//     x = hash512(x || password || salt);
// }

// key = x
// // Store the salt and the key in the db. The salt can be public.
// */


    // /* Implementation */
    
//    #define EXTRA_BITS_OF_SECURITY 20
//    // Iterations should be calibrated so the whole process takes 200-1000 ms
//    #define ITERATIONS 1 << EXTRA_BITS_OF_SECURITY
//    
//    // TODO: How to hold 256 bits or 512 bits of data? C Array?
//    // For 512 bits, thats 512/8 = 64 bytes
//    // Create an array to hold 512 bits (64 bytes - 64 chars) of information
//    unsigned char x[64];
//    // Password can be up to 32 characters (backfill with zeros)
//    unsigned char password[32];
//    for (int i = 0; i < ITERATIONS; ++i) {
//        const EVP_MD *EVP_sha512(void);
//    
//        x = hash512(x || password || salt);
//    }




    exit(0);
}



