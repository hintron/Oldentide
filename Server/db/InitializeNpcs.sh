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
delete from npcs;
.headers on
.mode csv
.import Npcs.init npcs
.quit
EOF
echo "NPCs Populated."

# Delete temp file.
rm "Npcs.init"
