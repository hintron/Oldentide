// Filename:    util.go
// Author:      Joseph DeVictoria
// Date:        June_16_2018
// Purpose:     Utility functions used by Oldentide dedicated server.

package main

import (
	"crypto/sha256"
	"encoding/base64"
	"log"
	"math/rand"
)

// Simple function to check the error status of an operation.
func checkErr(err error) {
	if err != nil {
		log.Fatal(err)
	}
}

func ifErrPrintErr(err error) {
	if err != nil {
		log.Println(err)
	}
}

// Function that takes in a password and salt and hashes them together into a db safe key.
func saltAndHash(password string, salt string) string {
	hasher := sha256.New()
	saltpass := password + salt
	hasher.Write([]byte(saltpass))
	hash := base64.URLEncoding.EncodeToString(hasher.Sum(nil))
	return hash
}

// Util used to generate a string of lower and upper case letters.
func generateRandomLetters(n int) string {
	var letters = []rune("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ")
	key := make([]rune, n)
	for i := range key {
		key[i] = letters[rand.Intn(len(letters))]
	}
	return string(key)
}

// Util used to generate a string of lowe and upper case letters and numbers.
func generateRandomAlnums(n int) string {
	var alnums = []rune("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789")
	key := make([]rune, n)
	for i := range key {
		key[i] = alnums[rand.Intn(len(alnums))]
	}
	return string(key)
}
