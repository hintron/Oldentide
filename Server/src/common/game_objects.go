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

type race_template struct {
    Id  int32
    Race    string
    Strength_mod
    Constitution_mod
    Intelligence_mod
    Dexterity_mod

}
