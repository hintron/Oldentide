#!/bin/bash
# Filename:    init_race_templates.sh
# Author:      Joseph DeVictoria
# Date:        March_18_2019
# Purpose:     Simple script populate the race templates table in the databse with race information.

echo "Populating Race Templates..."

# Make sure I am in this directory.
cd $(dirname $0)

# Import to sqlite3
# Import csv data into a temp table, then insert the data into npcs in order to auto-generate the ids
sqlite3 Oldentide.db <<EOF
.mode csv
DROP TABLE IF EXISTS temp_race_templates;
.import race_modifiers.csv temp_race_templates
INSERT INTO race_templates(
    name,
    true_name,
    lore_level,
    type,
    slot,
    icon,
    weight,
    encumbrance,
    dyeable,
    stackable,
    stack_size,
    usable,
    equipable,
    base_price,
    strength_requirement,
    constitution_requirement,
    intelligence_requirement,
    dexterity_requirement,
    skill_type_0,
    skill_requirement_0,
    skill_type_1,
    skill_requirement_1,
    skill_type_2,
    skill_requirement_2,
    skill_type_3,
    skill_requirement_3,
    skill_type_4,
    skill_requirement_4,
    description,
    true_description
) 
SELECT * FROM temp_item_templates;
