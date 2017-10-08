#!/bin/bash
# Filename:    InitializeNpcs.sh
# Author:      Joseph DeVictoria
# Date:        September_2_2017
# Purpose:     Simple script populate the NPC table in the databse with NPC information and nodes.

echo "Populating NPCs..."

# Make sure I am in this directory.
cd $(dirname $0)

# Import to sqlite3
# Import csv data into a temp table, then insert the data into npcs in order to auto-generate the ids
sqlite3 Oldentide.db <<EOF
.mode csv
DROP TABLE IF EXISTS temp_npcs;
.import Npcs.csv temp_npcs
INSERT INTO npcs(
    firstname,
    lastname,
    guild,
    race,
    gender,
    face,
    skin,
    profession,
    level,
    hp,
    maxhp,
    bp,
    maxbp,
    mp,
    maxmp,
    ep,
    maxep,
    strength,
    constitution,
    intelligence,
    dexterity,
    head,
    chest,
    arms,
    hands,
    legs,
    feet,
    cloak,
    necklace,
    ringone,
    ringtwo,
    righthand,
    lefthand,
    zone,
    x,
    y,
    z,
    pitch,
    yaw
) SELECT * FROM temp_npcs;
DROP TABLE temp_npcs;
.quit
EOF
echo "NPCs Populated."


# How to emulate a 'select * into' query in sqlite
# https://stackoverflow.com/a/2027509
# How to import csv without needing to specify the ids
# https://stackoverflow.com/questions/15994231/import-csv-into-sqlite-with-autoincrementing-primary-key/15998236#15998236
# How to get all but a single column
# https://stackoverflow.com/questions/729197/sql-exclude-a-column-using-select-except-columna-from-tablea
# How to do a for loop in sqlite command line using triggers:
# https://stackoverflow.com/a/7373289
# Syntax for sqlite trigger
# https://sqlite.org/lang_createtrigger.html
# SQL and modeling class inheritance
# https://stackoverflow.com/questions/3579079/how-can-you-represent-inheritance-in-a-database
