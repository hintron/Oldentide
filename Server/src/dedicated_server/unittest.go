// Filename:    unittest.go
// Author:      Joseph DeVictoria
// Date:        June_18_2018
// Purpose:     Unit tests for all files in the dedicated_server for Oldentide.
// Usage:       go test

package main

import "testing"

func TestGenerateRandomLetters(t *testing.T) {
    key := generateRandomLetters(10)
    if len(key) != 10 {
        t.Error("Length didn't match expected (10).")
    }
    key = generateRandomLetters(20)
    if len(key) != 20 {
        t.Error("Length didn't match expected (20).")
    }
}

func TestGenerateRandomLettersAndNumbers(t *testing.T) {

}
