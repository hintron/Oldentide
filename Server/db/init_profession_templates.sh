#!/bin/bash
# Filename:    init_profession_templates.sh
# Author:      Joseph DeVictoria
# Date:        March_18_2019
# Purpose:     Simple script populate the profession templates table in the databse with profession information.

echo "Populating Profession Templates..."

# Make sure I am in this directory.
cd $(dirname $0)

# Import to sqlite3
# Import csv data into a temp table, then insert the data into profession templates in order to auto-generate the ids
sqlite3 Oldentide.db <<EOF
.mode csv
DROP TABLE IF EXISTS temp_profession_templates;
.import profession_modifiers.csv temp_profession_modifiers
INSERT INTO profession_templates(
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
SELECT * FROM temp_profession_templates;
