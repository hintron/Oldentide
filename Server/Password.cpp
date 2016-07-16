// The following is an example from https://www.openssl.org/docs/manmaster/crypto/EVP_sha512.html
#include <stdio.h>
#include <openssl/evp.h>

main(int argc, char *argv[]) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;
    char mess1[] = "Test Message\n";
    char mess2[] = "Hello World\n";
    unsigned char md_value[EVP_MAX_MD_SIZE];
    int md_len, i;

    if(!argv[1]) {
        printf("Usage: mdtest digestname\n");
        exit(1);
    }

    md = EVP_get_digestbyname(argv[1]);

    if(!md) {
        printf("Unknown message digest %s\n", argv[1]);
        exit(1);
    }

    mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, md, NULL);
    EVP_DigestUpdate(mdctx, mess1, strlen(mess1));
    EVP_DigestUpdate(mdctx, mess2, strlen(mess2));
    EVP_DigestFinal_ex(mdctx, md_value, &md_len);
    EVP_MD_CTX_free(mdctx);

    printf("Digest is: ");
    for(i = 0; i < md_len; i++)
        printf("%02x", md_value[i]);
    printf("\n");

    exit(0);
}




// // #include <openssl/ssl.h>
// #include <openssl/crypto.h>
// // For sha256 hash
// #include <openssl/evp.h>
// // See https://www.openssl.org/docs/manmaster/crypto/EVP_sha512.html

// // Terminology:
// // message = plaintext
// // message digest function = hash function
// // message digest (MD) = digest = fingerprint = output of a hash function

// // TODO: Use uint8_t in place of unsigned char from stdtype?
// // #include <stdtype.h>
// // #include <assert.h>

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


// // TODO: Do this once I understand how to use hashing properly
// /* Implementation */

// #define EXTRA_BITS_OF_SECURITY 20;
// // Iterations should be calibrated so the whole process takes 200-1000 ms
// #define ITERATIONS 1 << EXTRA_BITS_OF_SECURITY;

// // TODO: How to hold 256 bits or 512 bits of data? C Array?
// // For 512 bits, thats 512/8 = 64 bytes
// // Create an array to hold 512 bits (64 bytes - 64 chars) of information
// unsigned char x[64];
// // Password can be up to 32 characters (backfill with zeros)
// unsigned char password[32];
// for (int i = 0; i < ITERATIONS; ++i) {
//     const EVP_MD *EVP_sha512(void);

//     x = hash512(x || password || salt);


// }




// // MD = message digest
// EVP_MD_CTX *context = EVP_MD_CTX_new(void);
// // Create a 512-bit SHA hash function on context
// EVP_DigestInit_ex(context, EVP_sha512(), 0);

// /* Or do this:
// EVP_MD_CTX *context;
// EVP_DigestInit(context, EVP_sha512(), 0);
// */


// // TODO: Build up message
// // Don't forget that there is a null character at the end
// char *message = "password";
// size_t count = 8;


// // Hash count bytes of data at d and store in context
// // int EVP_DigestUpdate(EVP_MD_CTX *ctx, const void *d, size_t cnt);
// EVP_DigestUpdate(context, message, count);



// unsigned int *bytes_written;
// unsigned char *message_digest;
// // Retrieve the digest
// // int EVP_DigestFinal_ex(EVP_MD_CTX *ctx, unsigned char *md,unsigned int *s);
// EVP_DigestFinal_ex(context, message_digest, bytes_written);


// // Free up the message digest context object
// EVP_MD_CTX_free(context);


// // EVP_DigestFinal() == EVP_DigestFinal_ex() + EVP_MD_CTX_free()


