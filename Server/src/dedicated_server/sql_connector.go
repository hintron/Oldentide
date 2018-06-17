// Filename:    sql_connector.go
// Author:      Joseph DeVictoria
// Date:        June_16_2018
// Purpose:     Database / sql abstraction for Oldentide dedicated server.

package main

/*import (
    _ "github.com/mattn/go-sqlite3"
)*/

// Check if the account name is already taken in the database.
func accountExists(a string) bool {
    rows, err := db.Query("SELECT * FROM accounts WHERE accountname=" + a)
    ifErrPrintErr(err)
    if rows == nil {
        return false
    } else {
        return true
    }
}

// Check if this email already has an account associated with it in the database.
func emailExists(e string) bool {
    rows, err := db.Query("SELECT * FROM accounts WHERE email=" + e)
    ifErrPrintErr(err)
    if rows == nil {
        return false
    } else {
        return true
    }
}

func createAccount(accountname string, email string, verify_key string, hashed_key string, salt_key string) {
    // Prepare insert statement.
    ins, err := db.Prepare("INSERT INTO accounts(valid, accountname, email, gamesession, playing, verify, hash, salt) values(?, ?, ?, ?, ?, ?, ?, ?)")
    checkErr(err)
    // Try to populate and execute an SQL statment.
    _, err = ins.Exec("0", accountname, email, "0", "0", verify_key, hashed_key, salt_key)
    checkErr(err)
}

func getAccountnameFromVerifyKey(k string) string {
    rows, err := db.Query("SELECT accountname FROM accounts WHERE verify=\"" + k + "\"")
    ifErrPrintErr(err)
    var accountname string = ""
    if rows != nil {
        for rows.Next() {
            rows.Scan(&accountname)
            rows.Close()
        }
    }
    return accountname
}

func activateAccount(a string) bool {
    update, err := db.Prepare("UPDATE accounts SET valid=? WHERE accountname=?")
    _, err = update.Exec("1", a)
    if err == nil {
        return true
    } else {
        return false
    }
}

// Queries the db to make sure that we are generating a truly unique verify key.
func generateUniqueVerify(n int) string {
    findKey := true
    for findKey {
        verify_key := generateRandomLetters(n)
        rows, err := db.Query("SELECT accountname FROM accounts WHERE verify=" + verify_key)
        ifErrPrintErr(err)
        if rows == nil {
            return verify_key
        }
    }
    return ""
}

// Queries the db to make sure that we are generating a truly unique salt.
func generateUniqueSalt(n int) string {
    findKey := true
    for findKey {
        salt_key := generateRandomLetters(n)
        rows, err := db.Query("SELECT accountname FROM accounts WHERE salt=" + salt_key)
        ifErrPrintErr(err)
        if rows == nil {
            return salt_key
        }
    }
    return ""
}
