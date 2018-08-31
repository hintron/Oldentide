// Filename:    sql_connector.go
// Author:      Joseph DeVictoria
// Date:        June_16_2018
// Purpose:     Database / sql abstraction for Oldentide dedicated server.

package main

import "database/sql"
import "fmt"
import "log"

// Check if the account name is already taken in the database.
func accountExists(a string) bool {
	rows, err := db.Query("SELECT accountname FROM accounts WHERE accountname='" + a + "'")
	return foundInRows(rows, err)
}

// Check if this email already has an account associated with it in the database.
func emailExists(e string) bool {
	rows, err := db.Query("SELECT accountname FROM accounts WHERE email='" + e + "'")
	return foundInRows(rows, err)
}

func createAccount(accountname string, email string, verify_key string, hashed_key string, salt_key string) bool {
	// Prepare insert statement.
	ins, err := db.Prepare("INSERT INTO accounts(valid, banned, accountname, email, gamesession, playing, verify, hash, salt) values(?, ?, ?, ?, ?, ?, ?, ?, ?)")
	checkErr(err)
	// Try to populate and execute an SQL statment.
	_, err = ins.Exec("0", "0", accountname, email, "0", "0", verify_key, hashed_key, salt_key)
	if err == nil {
		return true
	} else {
		return false
	}
}

func getAccountnameFromVerifyKey(k string) string {
	rows, _ := db.Query("SELECT accountname FROM accounts WHERE verify='" + k + "'")
	//ifErrPrintErr(err)
	var accountname string = ""
	if rows != nil {
		for rows.Next() {
			rows.Scan(&accountname)
		}
	}
	rows.Close()
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

func banAccount(a string) bool {
	ban, err := db.Prepare("UPDATE accounts SET banned=? WHERE accountname=?")
	_, err = ban.Exec("1", a)
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
		rows, err := db.Query("SELECT accountname FROM accounts WHERE verify='" + verify_key + "'")
		//ifErrPrintErr(err)
		if !foundInRows(rows, err) {
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
		rows, err := db.Query("SELECT accountname FROM accounts WHERE salt='" + salt_key + "'")
		if !foundInRows(rows, err) {
			return salt_key
		}
	}
	return ""
}

func foundInRows(rows *sql.Rows, err error) bool {
	found := false
	if err == sql.ErrNoRows {
		found = false
	} else if err != nil {
		log.Fatal(err)
	} else if rows.Next() {
		found = true
	}
	rows.Close()
	return found
}

func pullNpcs() []Npc {
	rows, err := db.Query("Select * FROM npcs")
	defer rows.Close()
	var npcs []Npc
	for rows.Next() {
		var npc Npc
		err = rows.Scan(
			&npc.Id,
			&npc.Firstname,
			&npc.Lastname,
			&npc.Guild,
			&npc.Race,
			&npc.Gender,
			&npc.Face,
			&npc.Skin,
			&npc.Profession,
			&npc.Alive,
			&npc.Nlevel,
			&npc.Hp,
			&npc.Maxhp,
			&npc.Bp,
			&npc.Maxbp,
			&npc.Mp,
			&npc.Maxmp,
			&npc.Ep,
			&npc.Maxep,
			&npc.Strength,
			&npc.Constitution,
			&npc.Intelligence,
			&npc.Dexterity,
			&npc.Head,
			&npc.Chest,
			&npc.Arms,
			&npc.Hands,
			&npc.Legs,
			&npc.Feet,
			&npc.Cloak,
			&npc.Righthand,
			&npc.Lefthand,
			&npc.Zone,
			&npc.X,
			&npc.Y,
			&npc.Z,
			&npc.Direction,
		)
		checkErr(err)
		npcs = append(npcs, npc)
	}
	return npcs
}

func pushNpcs([]Npc) {
	fmt.Println("Not yet implemented")
}
