#!/bin/bash
# Filename:    InitializeNpcs.sh
# Author:      Joseph DeVictoria
# Date:        September_2_2017
# Purpose:     Simple script populate the NPC table in the databse with NPC information and nodes.

echo "Populating NPCs for the first time..."

# Make sure I am in this directory.
cd $(dirname $0)

# Removing the header line from the csv file.
tail -n +2 "Npcs.csv" > "Npcs.init"

# Import to sqlite3
sqlite3 Oldentide.db <<EOF
-- delete all npcs and their corresponding character records
create temp trigger ttrig0 after delete on npcs begin
    DELETE FROM characters WHERE old.character_id = characters.id;
end;
DELETE FROM npcs;
-- Create a trigger that will set each of the new npc-characters as npcs
PRAGMA recursive_triggers = on;
create temp trigger ttrig1 after insert on characters begin
    INSERT INTO npcs (character_id) VALUES (new.id);
end;
.headers on
.mode csv
.import Npcs.init characters
.quit
EOF
echo "NPCs Populated."

# Delete temp file.
rm "Npcs.init"


# How to do a for loop in sqlite command line using triggers:
# https://stackoverflow.com/a/7373289
# Syntax for sqlite trigger
# https://sqlite.org/lang_createtrigger.html
# SQL and modeling class inheritance
# https://stackoverflow.com/questions/3579079/how-can-you-represent-inheritance-in-a-database
