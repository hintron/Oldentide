// Filename:    game_objects.go
// Author:      Joseph DeVictoria
// Date:        Aug_30_2018

package common

type Pc struct {
	Id             int32
	Accountid      int32
	Firstname      string
	Lastname       string
	Guild          string
	Race           string
	Gender         string
	Face           string
	Skin           string
	Profession     string
	Alive          bool
	Plevel         int32
	Dp             int32
	Hp             int32
	Maxhp          int32
	Bp             int32
	Maxbp          int32
	Mp             int32
	Maxmp          int32
	Ep             int32
	Maxep          int32
	Strength       int32
	Constitution   int32
	Intelligence   int32
	Dexterity      int32
	Axe            int32
	Dagger         int32
	Hammer         int32
	Polearm        int32
	Spear          int32
	Staff          int32
	Sword          int32
	Unarmed        int32
	Archery        int32
	Crossbow       int32
	Sling          int32
	Thrown         int32
	Armor          int32
	Dualweapon     int32
	Shield         int32
	Bardic         int32
	Conjuring      int32
	Druidic        int32
	Illusion       int32
	Necromancy     int32
	Shamanic       int32
	Sorcery        int32
	Summoning      int32
	Spellcraft     int32
	Focus          int32
	Alchemy        int32
	Armorsmithing  int32
	Calligraphy    int32
	Enchanting     int32
	Fletching      int32
	Lapidary       int32
	Tailoring      int32
	Weaponsmithing int32
	Herbalism      int32
	Hunting        int32
	Mining         int32
	Bargaining     int32
	Camping        int32
	Firstaid       int32
	Lore           int32
	Picklocks      int32
	Scouting       int32
	Search         int32
	Stealth        int32
	Traps          int32
	Aeolandis      int32
	Hieroform      int32
	Highgundis     int32
	Oldpraxic      int32
	Praxic         int32
	Runic          int32
	Head           string
	Chest          string
	Arms           string
	Hands          string
	Legs           string
	Feet           string
	Cloak          string
	Necklace       string
	Ringone        string
	Ringtwo        string
	Righthand      string
	Lefthand       string
	Zone           string
	X              float32
	Y              float32
	Z              float32
	Direction      float32
}

type Skillupdate struct {
	Playername     string
	Predp          int32
	Spenddp        int32
	Strength       int32
	Constitution   int32
	Intelligence   int32
	Dexterity      int32
	Axe            int32
	Dagger         int32
	Hammer         int32
	Polearm        int32
	Spear          int32
	Staff          int32
	Sword          int32
	Unarmed        int32
	Archery        int32
	Crossbow       int32
	Sling          int32
	Thrown         int32
	Armor          int32
	Dualweapon     int32
	Shield         int32
	Bardic         int32
	Conjuring      int32
	Druidic        int32
	Illusion       int32
	Necromancy     int32
	Shamanic       int32
	Sorcery        int32
	Summoning      int32
	Spellcraft     int32
	Focus          int32
	Alchemy        int32
	Armorsmithing  int32
	Calligraphy    int32
	Enchanting     int32
	Lapidary       int32
	Tailoring      int32
	Fletching      int32
	Weaponsmithing int32
	Herbalism      int32
	Hunting        int32
	Mining         int32
	Bargaining     int32
	Camping        int32
	Firstaid       int32
	Lore           int32
	Picklocks      int32
	Scouting       int32
	Search         int32
	Stealth        int32
	Traps          int32
	Aeolandis      int32
	Hieroform      int32
	Highgundis     int32
	Oldpraxic      int32
	Praxic         int32
	Runic          int32
}

type Npc struct {
	Id           int32
	Firstname    string
	Lastname     string
	Guild        string
	Race         string
	Gender       string
	Face         string
	Skin         string
	Profession   string
	Alive        bool
	Nlevel       int32
	Hp           int32
	Maxhp        int32
	Bp           int32
	Maxbp        int32
	Mp           int32
	Maxmp        int32
	Ep           int32
	Maxep        int32
	Strength     int32
	Constitution int32
	Intelligence int32
	Dexterity    int32
	Head         string
	Chest        string
	Arms         string
	Hands        string
	Legs         string
	Feet         string
	Cloak        string
	Righthand    string
	Lefthand     string
	Zone         string
	X            float32
	Y            float32
	Z            float32
	Direction    float32
}

type Item_template struct {
	Id                       int32
	Name                     string
	True_name                string
	Lore_level               int32
	Item_type                string
	Slot                     string
	Icon                     string
	Weight                   float32
	Encumbrance              float32
	Dyeable                  bool
	Stackable                bool
	Stack_size               int32
	Usable                   bool
	Equipable                bool
	Base_price               int32
	Strength_requirement     int32
	Constitution_requirement int32
	Intelligence_requirement int32
	Dexterity_requirement    int32
	Skill_type_0             string
	Skill_requirement_0      int32
	Skill_type_1             string
	Skill_requirement_1      int32
	Skill_type_2             string
	Skill_requirement_2      int32
	Skill_type_3             string
	Skill_requirement_3      int32
	Skill_type_4             string
	Skill_requirement_4      int32
}

type Race_template struct {
    Id int
    Race string
    Strength_mod float32
    Constitution_mod float32
    Intelligence_mod float32
    Dexterity_mod float32
    Axe_mod float32
    Dagger_mod float32
    Unarmed_mod float32
    Hammer_mod float32
    Polearm_mod float32
    Spear_mod float32
    Staff_mod float32
    Sword_mod float32
    Archery_mod float32
    Crossbow_mod float32
    Sling_mod float32
    Thrown_mod float32
    Armor_mod float32
    Dualweapon_mod float32
    Shield_mod float32
    Bardic_mod float32
    Conjuring_mod float32
    Druidic_mod float32
    Illusion_mod float32
    Necromancy_mod float32
    Sorcery_mod float32
    Shamanic_mod float32
    Spellcraft_mod float32
    Summoning_mod float32
    Focus_mod float32
    Armorsmithing_mod float32
    Tailoring_mod float32
    Fletching_mod float32
    Weaponsmithing_mod float32
    Alchemy_mod float32
    Lapidary_mod float32
    Calligraphy_mod float32
    Enchanting_mod float32
    Herbalism_mod float32
    Hunting_mod float32
    Mining_mod float32
    Bargaining_mod float32
    Camping_mod float32
    Firstaid_mod float32
    Lore_mod float32
    Picklocks_mod float32
    Scouting_mod float32
    Search_mod float32
    Stealth_mod float32
    Traps_mod float32
    Aeolandis_mod float32
    Hieroform_mod float32
    Highgundis_mod float32
    Oldpraxic_mod float32
    Praxic_mod float32
    Runic_mod float32
    Description string
}

type Profession_template struct {
    Id int
    Profession string
    Strength_mod float32
    Constitution_mod float32
    Intelligence_mod float32
    Dexterity_mod float32
    Axe_mod float32
    Dagger_mod float32
    Unarmed_mod float32
    Hammer_mod float32
    Polearm_mod float32
    Spear_mod float32
    Staff_mod float32
    Sword_mod float32
    Archery_mod float32
    Crossbow_mod float32
    Sling_mod float32
    Thrown_mod float32
    Armor_mod float32
    Dualweapon_mod float32
    Shield_mod float32
    Bardic_mod float32
    Conjuring_mod float32
    Druidic_mod float32
    Illusion_mod float32
    Necromancy_mod float32
    Sorcery_mod float32
    Shamanic_mod float32
    Spellcraft_mod float32
    Summoning_mod float32
    Focus_mod float32
    Armorsmithing_mod float32
    Tailoring_mod float32
    Fletching_mod float32
    Weaponsmithing_mod float32
    Alchemy_mod float32
    Lapidary_mod float32
    Calligraphy_mod float32
    Enchanting_mod float32
    Herbalism_mod float32
    Hunting_mod float32
    Mining_mod float32
    Bargaining_mod float32
    Camping_mod float32
    Firstaid_mod float32
    Lore_mod float32
    Picklocks_mod float32
    Scouting_mod float32
    Search_mod float32
    Stealth_mod float32
    Traps_mod float32
    Aeolandis_mod float32
    Hieroform_mod float32
    Highgundis_mod float32
    Oldpraxic_mod float32
    Praxic_mod float32
    Runic_mod float32
    Skill_1_multi bool
    Skill_1_names string
    Skill_1_value float32
    Skill_2_multi bool
    Skill_2_names string
    Skill_2_value float32
    Skill_3_multi bool
    Skill_3_names string
    Skill_3_value float32
    Skill_4_multi bool
    Skill_4_names string
    Skill_4_value float32
    Skill_5_multi bool
    Skill_5_names string
    Skill_5_value float32
    Description string
}