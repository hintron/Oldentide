// Filename:    SQLConnector.cpp
// Author:      Joseph DeVictoria
// Date:        Feb_29_2016
// Purpose:     SQL Connector class to handle SQLite3 queries.

#include "SQLConnector.h"
#include "SQLiteCpp/SQLiteCpp.h"
#include "Utils.h"
#include <iostream>
#include <string.h>
#include <sstream>
#include <fstream>

// TODO: Make all strings references to reduce copying

// For how to use sqlitecpp, see https://github.com/SRombauts/SQLiteCpp/blob/master/examples/example1/main.cpp

// Note: In c++, you can't just instantiate a class inside the constructor - it needs to be in the initialization list
// This tries to open the database file when instantiated, and set it to write
SQLConnector::SQLConnector() : db("db/Oldentide.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE){
    std::cout << "Oldentide database opened successfully." << std::endl;
}

// TODO: There is no need to free the db, right? Should be automatic?
SQLConnector::~SQLConnector() {}


bool SQLConnector::ExecuteSqlFile(std::string filename) {
    // Extract the contents of the sql file into a stringstream
    std::ifstream file(filename);
    std::stringstream buffer;
    buffer << file.rdbuf();
    // Execute the sql file
    try {
        db.exec(buffer.str());
        return true;
    }
    catch (std::exception& e) {
        std::cout << "Exception: could not execute sql file:" << std::endl;
        std::cout << e.what() << std::endl;
        return false;
    }
}



// Executes a static SQL statement, and prints out the result
// Returns true if successful, false otherwise
bool SQLConnector::Execute(std::string cmd, bool quiet) {
    try {
        SQLite::Statement query(db, cmd);
        if(!quiet){
            std::cout << "Attempting to execute the following query:" << std::endl;
            std::cout << query.getQuery() << std::endl;
        }
        int i = 0;
        bool printed_columns = false;
        while (query.executeStep()) {
            if(quiet){
                i++;
                continue;
            }
            int col_count = query.getColumnCount();
            if(!printed_columns){
                printed_columns = true;
                std::cout << "Columns: ";
                for (int k = 0; k < col_count; ++k) {
                    // To enable getColumnOriginName(), make sure SQLITE_ENABLE_COLUMN_METADATA is defined during compilation
                    std::cout << std::setw(10) << query.getColumnOriginName(k) << " | ";
                }
                std::cout << std::endl;
            }
            std::cout << "Row " << std::setw(3) << i << ": ";
            for (int j = 0; j < col_count; ++j){
                std::cout << std::setw(10) << query.getColumn(j) << " | ";
            }
            std::cout << std::endl;
            i++;
        }
        return true;
    }
    catch (std::exception& e) {
        std::cout << "Exception: could not execute sql statement:" << std::endl;
        std::cout << e.what() << std::endl;
        return false;
    }
}

// -------------------------------------- Parent Functions ----------------------------------------

// Insert a new account record.
bool SQLConnector::InsertAccount(std::string accountName, std::string email, std::string key, std::string salt) {
    // Sanitize key, salt, and account name
    if (!utils::SanitizeAccountName(accountName)) {
        std::cout << "Account Name is invalid! Cannot insert account record" << std::endl;
        return false;
    }
    // TODO: Sanitize email!
    // if (!utils::SanitizeEmail(email)) {
    //     std::cout << "Email is invalid! Cannot insert account record" << std::endl;
    //     return false;
    // }
    if (!utils::SanitizeHexString(key)) {
        std::cout << "Key is invalid! Cannot insert account record" << std::endl;
        return false;
    }
    if (!utils::SanitizeHexString(salt)) {
        std::cout << "Salt is invalid! Cannot insert account record" << std::endl;
        return false;
    }
    std::string cmd("insert into accounts (accountname, valid, email, playing, key, salt) values (?,?,?,?,?,?)");
    SQLite::Statement query(db, cmd);
    query.bind(1, accountName);
    query.bind(2, true);
    query.bind(3, email);
    query.bind(4, true);
    query.bind(5, key);
    query.bind(6, salt);
    while (query.executeStep()) {
        std::cout << "Executing step for insert account..." << std::endl;
    }

    return true;
}

// Inserts a new player into the database.
bool SQLConnector::InsertPlayer(Player p) {
    std::stringstream query;

    stats_t stats;
    equipment_t equipment;
    location_t location;

    // sockaddr_in client,
    // std::string account,
    // int id,
    // int session,
    // std::string firstname,
    // std::string lastname,
    // std::string guild,
    // std::string race,
    // std::string gender,
    // std::string face,
    // std::string skin,
    // std::string zone,
    // std::string profession,
    // equipment_t equipment,
    // stats_t stats,
    // location_t location


    // try {
    //     // Open a database file
    //     SQLite::Database    db("Oldentide.db");

    //     // Compile a SQL query, containing one parameter (index 1)
    //     SQLite::Statement   query(db, "SELECT * FROM characters");
    //     // query.bind(1, 6);

    //     // Loop to execute the query step by step, to get rows of result
    //     while (query.executeStep()) {
    //         // Demonstrate how to get some typed column value
    //         int         id      = query.getColumn(0);
    //         const char* value   = query.getColumn(1);
    //         int         size    = query.getColumn(2);

    //         std::cout << "row: " << id << ", " << value << ", " << size << std::endl;
    //     }
    // }
    // catch (std::exception& e) {
    //     std::cout << "exception: " << e.what() << std::endl;
    // }



    // // TODO: Return the id of the newly-created record
    // // Multiline string literal!
    // std::string query_string(R"(
    //     INSERT INTO characters (
    //         accountid,
    //         firstname,
    //         lastname,
    //         race,
    //         gender,
    //         face,
    //         skin,
    //         profession,
    //         level,
    //         hp,
    //         maxhp,
    //         bp,
    //         maxbp,
    //         mp,
    //         maxmp,
    //         ep,
    //         maxep,
    //         strength,
    //         constitution,
    //         intelligence,
    //         dexterity,
    //         axe,
    //         dagger,
    //         unarmed,
    //         hammer,
    //         polearm,
    //         spear,
    //         staff,
    //         sword,
    //         archery,
    //         crossbow,
    //         sling,
    //         thrown,
    //         armor,
    //         dualweapon,
    //         shield,
    //         bardic,
    //         conjuring,
    //         druidic,
    //         illusion,
    //         necromancy,
    //         sorcery,
    //         shamanic,
    //         summoning,
    //         spellcraft,
    //         focus,
    //         armorsmithing,
    //         tailoring,
    //         fletching,
    //         weaponsmithing,
    //         alchemy,
    //         lapidary,
    //         calligraphy,
    //         enchanting,
    //         herbalism,
    //         hunting,
    //         mining,
    //         bargaining,
    //         camping,
    //         firstaid,
    //         lore,
    //         picklocks,
    //         scouting,
    //         search,
    //         stealth,
    //         traps,
    //         aeolandis,
    //         hieroform,
    //         highgundis,
    //         oldpraxic,
    //         praxic,
    //         runic,
    //         head,
    //         chest,
    //         arms,
    //         hands,
    //         legs,
    //         feet,
    //         cloak,
    //         necklace,
    //         ringone,
    //         ringtwo,
    //         righthand,
    //         lefthand,
    //         zone,
    //         x,
    //         y,
    //         z,
    //         pitch,
    //         yaw
    //     ) VALUES (";
    // )");
    // query << "'" << p.GetAccount() << "', ";
    // query << "'" << p.GetFirstName() << "', ";
    // query << "'" << p.GetLastname() << "', ";
    // query << "'" << p.GetRace() << "', ";
    // query << "'" << p.GetGender() << "', ";
    // query << "'" << p.GetFace() << "', ";
    // query << "'" << p.GetSkin() << "', ";
    // query << "'" << p.GetProfession() << "', ";
    // query << p.GetLevel() << ", ";
    // query << p.GetHp() << ", ";
    // query << p.GetMaxHp() << ", ";
    // query << p.GetBp() << ", ";
    // query << p.GetMaxBp() << ", ";
    // query << p.GetMp() << ", ";
    // query << p.GetMaxMp() << ", ";
    // query << p.GetEp() << ", ";
    // query << p.GetMaxEp() << ", ";
    // query << p.GetStrength() << ", ";
    // query << p.GetConstitution() << ", ";
    // query << p.GetIntelligence() << ", ";
    // query << p.GetDexterity() << ", ";
    // query << p.GetAxe() << ", ";
    // query << p.GetDagger() << ", ";
    // query << p.GetUnarmed() << ", ";
    // query << p.GetHammer() << ", ";
    // query << p.GetPolearm() << ", ";
    // query << p.GetSpear() << ", ";
    // query << p.GetStaff() << ", ";
    // query << p.GetSword() << ", ";
    // query << p.GetArchery() << ", ";
    // query << p.GetCrossbow() << ", ";
    // query << p.GetSling() << ", ";
    // query << p.GetThrown() << ", ";
    // query << p.GetArmor() << ", ";
    // query << p.GetDualWeapon() << ", ";
    // query << p.GetShield() << ", ";
    // query << p.GetBardic() << ", ";
    // query << p.GetConjuring() << ", ";
    // query << p.GetDruidic() << ", ";
    // query << p.GetIllusion() << ", ";
    // query << p.GetNecromancy() << ", ";
    // query << p.GetSorcery() << ", ";
    // query << p.GetShamanic() << ", ";
    // query << p.GetSummoning() << ", ";
    // query << p.GetSpellcraft() << ", ";
    // query << p.GetFocus() << ", ";
    // query << p.GetArmorsmithing() << ", ";
    // query << p.GetTailoring() << ", ";
    // query << p.GetFletching() << ", ";
    // query << p.GetWeaponsmithing() << ", ";
    // query << p.GetAlchemy() << ", ";
    // query << p.GetLapidary() << ", ";
    // query << p.GetCalligraphy() << ", ";
    // query << p.GetEnchanting() << ", ";
    // query << p.GetHerbalism() << ", ";
    // query << p.GetHunting() << ", ";
    // query << p.GetMining() << ", ";
    // query << p.GetBargaining() << ", ";
    // query << p.GetCamping() << ", ";
    // query << p.GetFirstAid() << ", ";
    // query << p.GetLore() << ", ";
    // query << p.GetPickLocks() << ", ";
    // query << p.GetScouting() << ", ";
    // query << p.GetSearch() << ", ";
    // query << p.GetStealth() << ", ";
    // query << p.GetTraps() << ", ";
    // query << p.GetAeolandis() << ", ";
    // query << p.GetHieroform() << ", ";
    // query << p.GetHighGundis() << ", ";
    // query << p.GetOldPraxic() << ", ";
    // query << p.GetPraxic() << ", ";
    // query << p.GetRunic() << ", ";
    // query << "'" << p.GetHead() << "', ";
    // query << "'" << p.GetChest() << "', ";
    // query << "'" << p.GetArms() << "', ";
    // query << "'" << p.GetHands() << "', ";
    // query << "'" << p.GetLegs() << "', ";
    // query << "'" << p.GetFeet() << "', ";
    // query << "'" << p.GetCloak() << "', ";
    // query << "'" << p.GetNecklace() << "', ";
    // query << "'" << p.GetRingOne() << "', ";
    // query << "'" << p.GetRingTwo() << "', ";
    // query << "'" << p.GetRightHand() << "', ";
    // query << "'" << p.GetLeftHand() << "', ";
    // query << "'" << p.GetZone() << "', ";
    // query << p.GetX() << ", ";
    // query << p.GetY() << ", ";
    // query << p.GetZ() << ", ";
    // query << p.GetPitch() << ", ";
    // query << p.GetYaw() << ")";

    // std::cout << query.str() << std::endl;
    // Execute(query.str());

    // if (sqls == SQLITE_OK) {
        return false;
    // }
    // else {
    //     return false;
    // }
}

// Lists all the accounts
void SQLConnector::ListAccounts() {
    std::string cmd("select * from accounts ORDER BY accountname");
    SQLite::Statement query(db, cmd);
    while (query.executeStep()) {
        std::cout << "Executing step for insert account..." << std::endl;
    }
}

// TODO: Create a view instead of creating a join table right here
std::vector<std::string> SQLConnector::GetPlayerList(std::string accountname) {
    std::vector<std::string> players;

    std::string cmd("select firstname, lastname FROM players JOIN accounts ON players.account_id = accounts.id ORDER BY accountname WHERE accountname = ?");
    SQLite::Statement query(db, cmd);
    query.bind(1, accountname);

    while (query.executeStep()) {
        std::string name = query.getColumn(0);
        std::string lastname = query.getColumn(1);
        name.append(" ").append(lastname);
        players.push_back(name);
    }
    return players;
}

std::set<Npc> SQLConnector::PopulateNpcList() {
    std::set<Npc> npcs;
    std::stringstream query;
    // char *errorMessage = NULL;
    // query << "SELECT * FROM npcs";
    // sqls = sqlite3_exec(database, query.str().c_str(), ParseNpcs, (void*)&npcs, &errorMessage);
    // if (sqls != SQLITE_OK) {
    //     std::cout << "Could not Execute SQL query! Return Code:" << sqls << std::endl;
    // }
    // if (errorMessage) {
    //     std::cout << "SQL ERROR MESSAGE: " << errorMessage << std::endl;
    //     sqlite3_free(errorMessage);
    // }
    return npcs;
}

// Return the salt for the passed account
bool SQLConnector::GetAccountSalt(char *accountName, char *saltStringHex) {
    // Sanitize the account name before preceeding
    if (!utils::SanitizeAccountName(accountName)) {
        return false;
    }
    char *errorMessage = NULL;
    std::stringstream query;
    query << "select salt from accounts where accountname = \"" << accountName << "\"";
    // The fourth param is passed to the callback function as a void pointer to the first param
    // sqls = sqlite3_exec(database, query.str().c_str(), &ReturnStringCallback, saltStringHex, &errorMessage);
    // if (sqls != SQLITE_OK) {
    //     std::cout << "Could not Execute SQL query! Return Code:" << sqls << std::endl;
    // }
    // if (errorMessage) {
    //     // Print out the error message if any
    //     std::cout << "SQL ERROR MESSAGE: " << errorMessage << std::endl;
    //     // Free the error message, since it was alloced in exec()
    //     sqlite3_free(errorMessage);
    //     return false;
    // }
    // Check to see if the salt was retrieved
    if (utils::SanitizeHexString(saltStringHex)) {
        return true;
    }
    else {
        return false;
    }

}

// Returns the key to the passed account
int SQLConnector::GetAccountKey(char *accountName, char *keyStringHex) {
    // // Sanitize the account name before preceeding
    // if (!utils::SanitizeAccountName(accountName)) {
    //     return 0;
    // }
    // char *errorMessage = NULL;
    // std::stringstream query;
    // query << "select key from accounts where accountname = \"" << accountName << "\"";
    // //std::cout << query.str() << std::endl;
    // // The fourth param is passed to the callback function as a void pointer to the first param
    // sqls = sqlite3_exec(database, query.str().c_str(), &ReturnStringCallback, keyStringHex, &errorMessage);
    // if (sqls != SQLITE_OK) {
    //     std::cout << "Could not Execute SQL query! Return Code:" << sqls << std::endl;
    // }
    // if (errorMessage) {
    //     // Print out the error message if any
    //     std::cout << "SQL ERROR MESSAGE: " << errorMessage << std::endl;
    //     // Free the error message, since it was alloced in exec()
    //     sqlite3_free(errorMessage);
    // }
    return 1;
}

// -------------------------------------- Callback Functions ---------------------------------------

// A generic callback function to sqlite3_exec() that copies a c string in the first column
// // of the returned row into stringToReturn. This function assumes that only one record will be
// // in the result set, or else the return value will be the value in the last row processed.
// static int ReturnStringCallback(void *stringToReturn, int argc, char **argv, char **azColName) {
//     strcpy((char *)stringToReturn, argv[0]);
//     return 0;
// }

// static int ParseNpcs(void * npcs, int argc, char ** argv, char ** azColName) {
//     std::set<Npc> * npcset = (std::set<Npc> *)npcs;
//     //npcset->insert(Npc temp(argv));
//     return 0;
// }
