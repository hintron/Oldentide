// Filename:    SQLConnector.h
// Author:      Joseph DeVictoria
// Date:        Feb_29_2016
// Purpose:     SQL Connector class to handle SQLite3 queries.

#include "SQLConnector.h"
#include <iostream>
#include <string.h>

using namespace std;

SQLConnector::SQLConnector(){
    sqls = sqlite3_open("db/Oldentide.db", &database);
    if(sqls){
        cout << "Can't open database!" << endl;
    }
    else{
        cout << "Oldentide database opened successfully." << endl;
    }
}

SQLConnector::~SQLConnector(){
    sqlite3_close(database);
}

void SQLConnector::execute(string cmd){
    cout << cmd << endl;
    sqls = sqlite3_exec(database, cmd.c_str(), 0, 0, NULL);
    if (sqls != SQLITE_OK){
        cout << "Could not execute SQL query!" << endl;
    }
    else {
        cout << sqls;
    }
}

void SQLConnector::initDb(){
    string cmd;
    cmd =   "DROP TABLE IF EXISTS players;";
    execute(cmd);
    cmd =   "DROP TABLE IF EXISTS accounts;";
    execute(cmd);
    cmd =   "CREATE TABLE players" 
            "("
            "    id integer not null primary key autoincrement,"
            "    account text not null,"
            "    session integer not null,"
            "    firstname text not null,"
            "    lastname text not null,"
            "    race text not null,"
            "    gender text not null,"
            "    profession text not null,"
            "    level integer not null,"
            "    hp integer not null,"
            "    bp integer not null,"
            "    mp integer not null,"
            "    ep integer not null,"
            "    strength integer not null,"
            "    constitution integer not null,"
            "    intelligence integer not null,"
            "    dexterity integer not null,"
            "    axe integer not null,"
            "    dagger integer not null,"
            "    unarmed integer not null,"
            "    hammer integer not null,"
            "    polearm integer not null,"
            "    spear integer not null,"
            "    staff integer not null,"
            "    sword integer not null,"
            "    archery integer not null,"
            "    crossbow integer not null,"
            "    sling integer not null,"
            "    thrown integer not null,"
            "    armor integer not null,"
            "    dualWeapon integer not null,"
            "    shield integer not null,"
            "    bardic integer not null,"
            "    conjuring integer not null,"
            "    druidic integer not null,"
            "    illusion integer not null,"
            "    necromancy integer not null,"
            "    sorcery integer not null,"
            "    shamanic integer not null,"
            "    spellcraft integer not null,"
            "    summoning integer not null,"
            "    focus integer not null,"
            "    armorsmithing integer not null,"
            "    tailoring integer not null,"
            "    fletching integer not null,"
            "    weaponsmithing integer not null,"
            "    alchemy integer not null,"
            "    lapidary integer not null,"
            "    calligraphy integer not null,"
            "    enchanting integer not null,"
            "    herbalism integer not null,"
            "    hunting integer not null,"
            "    mining integer not null,"
            "    bargaining integer not null,"
            "    camping integer not null,"
            "    firstAid integer not null,"
            "    lore integer not null,"
            "    pickLocks integer not null,"
            "    scouting integer not null,"
            "    search integer not null,"
            "    stealth integer not null,"
            "    traps integer not null,"
            "    aeolandis integer not null,"
            "    hieroform integer not null,"
            "    highGundis integer not null,"
            "    oldPraxic integer not null,"
            "    praxic integer not null,"
            "    runic integer not null,"
            "    weight integer not null,"
            "    x integer not null,"
            "    y integer not null,"
            "    z integer not null,"
            "    direction real not null"
            ")";
    execute(cmd);
}
