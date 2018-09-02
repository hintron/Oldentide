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

func pullNpcs() []npc {
	rows, err := db.Query("Select * FROM npcs")
	defer rows.Close()
	var npcs []npc
	for rows.Next() {
		var npc npc
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

func pushNpcs([]npc) {
	fmt.Println("Not yet implemented")
}

func getRemainingPlayerSlots(account_name string, max_player_slots int) int {
	rows, err := db.Query("Select * FROM players INNER JOIN accounts ON players.account_id=accounts.id WHERE accountname=?", account_name)
    checkErr(err)
	defer rows.Close()
	num_players := max_player_slots
	for rows.Next() {
		num_players--
	}
	return num_players
}

func playerFirstNameTaken(player_firstname string) bool {
	rows, err := db.Query("Select * FROM players WHERE firstname=?", player_firstname)
	checkErr(err)
	return foundInRows(rows, err)
}

func addNewPlayer(player pc) {
	// Need to add this...
	ins, err := db.Prepare("INSERT INTO players(account_id, firstname, lastname, guild, race, gender, face, skin, profession, alive, plevel, dp, hp, maxhp, bp, maxbp, mp, maxmp, ep, maxep, strength, constitution, intelligence, dexterity, axe, dagger, unarmed, hammer, polearm, spear, staff, sword, archery, crossbow, sling, thrown, armor, dualweapon, shield, bardic, conjuring, druidic, illusion, necromancy, sorcery, shamanic, spellcraft, summoning, focus, armorsmithing, tailoring, fletching, weaponsmithing, alchemy, lapidary, calligraphy, enchanting, herbalism, hunting, mining, bargaining, camping, firstaid, lore, picklocks, scouting, search, stealth, traps, aeolandis, hieroform, highgundis, oldpraxic, praxic, runic, head, chest, arms, hands, legs, feet, cloak, necklace, ringone, ringtwo, righthand, lefthand, zone, x, y, z, direction) values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)")
	checkErr(err)
	// Try to populate and execute an SQL statment.
	_, err = ins.Exec(
		player.Accountid,
		player.Firstname,
		player.Lastname,
		player.Guild,
		player.Race,
		player.Gender,
		player.Face,
		player.Skin,
		player.Profession,
		player.Alive,
		player.Plevel,
		player.Dp,
		player.Hp,
		player.Maxhp,
		player.Bp,
		player.Maxbp,
		player.Mp,
		player.Maxmp,
		player.Ep,
		player.Maxep,
		player.Strength,
		player.Constitution,
		player.Intelligence,
		player.Dexterity,
		player.Axe,
		player.Dagger,
		player.Unarmed,
		player.Hammer,
		player.Polearm,
		player.Spear,
		player.Staff,
		player.Sword,
		player.Archery,
		player.Crossbow,
		player.Sling,
		player.Thrown,
		player.Armor,
		player.Dualweapon,
		player.Shield,
		player.Bardic,
		player.Conjuring,
		player.Druidic,
		player.Illusion,
		player.Necromancy,
		player.Sorcery,
		player.Shamanic,
		player.Spellcraft,
		player.Summoning,
		player.Focus,
		player.Armorsmithing,
		player.Tailoring,
		player.Fletching,
		player.Weaponsmithing,
		player.Alchemy,
		player.Lapidary,
		player.Calligraphy,
		player.Enchanting,
		player.Herbalism,
		player.Hunting,
		player.Mining,
		player.Bargaining,
		player.Camping,
		player.Firstaid,
		player.Lore,
		player.Picklocks,
		player.Scouting,
		player.Search,
		player.Stealth,
		player.Traps,
		player.Aeolandis,
		player.Hieroform,
		player.Highgundis,
		player.Oldpraxic,
		player.Praxic,
		player.Runic,
		player.Head,
		player.Chest,
		player.Arms,
		player.Hands,
		player.Legs,
		player.Feet,
		player.Cloak,
		player.Necklace,
		player.Ringone,
		player.Ringtwo,
		player.Righthand,
		player.Lefthand,
		player.Zone,
		player.X,
		player.Y,
		player.Z,
		player.Direction,
	)
	checkErr(err)
}
