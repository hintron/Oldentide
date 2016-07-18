// Compile this file with the following command
// g++ mdtest.cpp -lcrypto -o mdtest.o

// Example usage:
// ./mdtest.o "Hello, World!"
// Output Hash:
// dffd6021bb2bd5b0af676290809ec3a53191dd81c7f70a4b28688a362182986f

// NOTE: OpenSSL 1.0.2h needs to be installed on the system! It is the LTS solution and will be supported until Dec 2019

// Terminology:
// message = plaintext
// message digest function = hash function
// message digest (MD) = digest = fingerprint = output of a hash function

// The following is based off an example from https://www.openssl.org/docs/man1.0.2/crypto/EVP_DigestInit.html
#include <stdio.h>
#include <openssl/evp.h>
#include <string.h>

main(int argc, char *argv[]) {
    EVP_MD_CTX *md_context;
    const EVP_MD *md_function;
    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned int md_len, i;

    // Initialize the lookup table for the function EVP_get_digestbyname() 
    OpenSSL_add_all_digests();

    if(!argv[1]) {
        printf("Usage: ./mdtest.o message-to-hash digestname\n");
        exit(1);
    }

    if(!argv[2]) {
        printf("Using SHA-256 by default...\n");
        md_function = EVP_sha256();
    }
    else {
        md_function = EVP_get_digestbyname(argv[2]);
        if(!md_function) {
            printf("Unknown message digest function %s\n", argv[2]);
            exit(1);
        }
    }

    printf("Getting hash of string \"%s\"\n", argv[1]);

    md_context = EVP_MD_CTX_create();
    EVP_DigestInit_ex(md_context, md_function, NULL);
    EVP_DigestUpdate(md_context, argv[1], strlen(argv[1]));
    // You can add multiple strings to the message before executing the final digest
    //EVP_DigestUpdate(md_context, mess2, strlen(mess2));
    EVP_DigestFinal_ex(md_context, md_value, &md_len);
    EVP_MD_CTX_destroy(md_context);

    printf("Digest is: \n");
    for(i = 0; i < md_len; i++)
        printf("%02x", md_value[i]);
    printf("\n");

    // free the digest lookup table 
    EVP_cleanup();
    exit(0);
}

