// File:     Character.cpp
// Created:  April 19, 2015
// Author:   Joseph DeVictoria
// Purpose:  Child class representing any living object in Oldentide.
//        :  Inherits from "Object" class.

using namespace std;

//------------------------------------------------------------------------------//
//----------                     Class Constructors                   ----------//
//------------------------------------------------------------------------------//

Character :: Character(string name, string race, string gender, string profession,
                       int weight, int x, int y)
           : Object(weight, x, y) {
    setName(name);
    setRace(race);
    setGender(gender);
    setProfession(profession);
}

Character :: Character(string name, string race, string gender, string profession) 
           : Object(0, 0, 0) {
    setName(name);
    setRace(race);
    setGender(gender);
    setProfession(profession);
}

//------------------------------------------------------------------------------//
//----------                      Getter Functions                    ----------//
//------------------------------------------------------------------------------//

string getName() {
    return name;
}

string getRace() {
    return race;
}

string getGender() {
    return gender;
}

string getProfession() {
    return profession;
}

int getLevel() {
    return level;
}

int getHP() {
    return hp;
}

int getBP() {
    return bp;
}

int getMP() {
    return mp;
}

int getEP() {
    return ep;
}

int getStrength() {
    return strength;
}

int getConstitution() {
    return constitution;
}

int getIntelligence() {
    return intelligence;
}

int getDexterity() {
    return dexterity;
}

int getAxe() {
    return axe;
}

int getDagger() {
    return dagger;
}

int getUnarmed() {
    return unarmed;
}

int getHammer() {
    return hammer;
}

int getPolearm() {
    return polearm;
}

int getSpear() {
    return spear;
}

int getStaff() {
    return staff;
}

int getSword() {
    return sword;
}

int getArchery() {
    return archery;
}

int getCrossbow() {
    return crossbow;
}

int getSling() {
    return sling;
}

int getThrown() {
    return thrown;
}

int getArmor() {
    return armor;
}

int getDualWeapon() {
    return dualWeapons;
}

int getShield() {
    return shield;
}

int getBardic() {
    return bardic;
}

int getConjuring() {
    return conjuring;
}

int getDruidic() {
    return druidic;
}

int getIllusion() {
    return illusion;
}

int getNecromancy() {
    return necromancy;
}

int getSorcery() {
    return sorcery;
}

int getShamanic() {
    return shamanic;
}

int getSummoning() {
    return summoning;
}

int getSpellcraft() {
    return spellcraft;
}

int getFocus() {
    return focus;
}

int getArmorsmithing() {
    return armorsmithing;
}

int getTailoring() {
    return tailoring;
}

int getFletching() {
    return fletching;
}

int getWeaponsmith() {
    return weaponsmithing;
}

int getAlchemy() {
    return alchemy;
}

int getLapidary() {
    return lapidary;
}

int getCalligraphy() {
    return calligraphy;
}

int getEnchanting() {
    return enchanting;
}

int getHerbalism() {
    return herbalism;
}

int getHunting() {
    return hunting;
}

int getMining() {
    return mining;
}

int getBargaining() {
    return bargaining;
}

int getCamping() {
    return camping;
}

int getFirstAid() {
    return firstAid;
}

int getLore() {
    return lore;
}

int getPickLocks() {
    return pickLocks;
}

int getScouting() {
    return scouting;
}

int getSearch() {
    return search;
}

int getStealth() {
    return stealth;
}

int getTraps() {
    return traps;
}

int getAeolandis() {
    return aeolandis;
}

int getHieroform() {
    return hieroform;
}

int getHighGundis() {
    return highGundis;
}

int getOldPraxic() {
    return oldPraxic;
}

int getPraxic() {
    return praxic;
}

int getRunic() {
    return runic;
}

//------------------------------------------------------------------------------//
//----------                      Setter Functions                    ----------//
//------------------------------------------------------------------------------//

void setName(string name) {
    this.name = name;
}

void setRace(string race) {
    this.race = race;
}

void setGender(string gender) {
    this.gender = gender;
}

void setProfession(string profession) {
    this.profession = profession;
}

void setLevel(int level) {
    this.level = level;
}

void setHP(int hp) {
    this.hp = hp;
}

void setBP(int bp) {
    this.bp = bp;
}

void setMP(int mp) {
    this.mp = mp;
}

void setEP(int ep) {
    this.ep = ep;
}

void setStrength(int strength) {
    this.strength = strength;
}

void setConstitution(int constitution) {
    this.constitution = constitution;
}

void setIntelligence(int intelligence) {
    this.intelligence = intelligence;
}

void setDexterity(int dexterity) {
    this.dexterity = dexterity;
}

void setAxe(int axe) {
    this.axe = axe;
}

void setDagger(int dagger) {
    this.dagger = dagger;
}

void setUnarmed(int unarmed) {
    this.unarmer = unarmed;
}

void setHammer(int hammer) {
    this.hammer = hammer;
}

void setPolearm(int polearm) {
    this.polearm = polearm;
}

void setSpear(int spear) {
    this.spear = spear;
}

void setStaff(int staff) {
    this.staff = staff;
}

void setSword(int sword) {
    this.sword = sword;
}

void setArchery(int archery) {
    this.archery = archery;
}

void setCrossbow(int crossbow) {
    this.crossbow = crossbow;
}

void setSling(int sling) {
    this.sling = sling;
}

void setThrown(int thrown) {
    this.thrown = thrown;
}

void setArmor(int armor) {
    this.armor = armor;
}

void setDualWeapon(int dualWeapon) {
    this.dualWeapon = dualWeapon;
}

void setShield(int shield) {
    this.shield = shield;
}

void setBardic(int bardic) {
    this.bardic = bardic;
}

void setConjuring(int conjuring) {
    this.conjuring = conjuring;
}

void setDruidic(int druidic) {
    this.druidic = druidic;
}

void setIllusion(int illusion) {
    this.illusion = illusion;
}

void setNecromancy(int necromancy) {
    this.necromancy = necromancy;
}

void setSorcery(int sorcery) {
    this.sorcery = sorcery;
}

void setShamanic(int shamanic) {
    this.shamanic = shamanic;
}

void setSummoning(int summoning) {
    this.summoning = summoning;
}

void setSpellcraft(int spellcraft) {
    this.spellcraft = spellcraft;
}

void setFocus(int focus) {
    this.focus = focus;
}

void setArmorsmithing(int armorsmithing) {
    this.armorsmithing = armorsmithing;
}

void setTailoring(int tailoring) {
    this.tailoring = tailoring;
}

void setFletching(int fletching) {
    this.fletching = fletching;
}

void setWeaponsmith(int weaponsmithing) {
    this.weaponsmithing = weaponsmithing;
}

void setAlchemy(int alchemy) {
    this.alchemy = alchemy;
}

void setLapidary(int lapidary) {
    this.lapidary = lapidary;
}

void setCalligraphy(int calligraphy) {
    this.calligraphy = calligraphy;
}

void setEnchanting(int enchanting) {
    this.enchanting = enchanting;
}

void setHerbalism(int herbalism) {
    this.herbalism = herbalism;
}

void setHunting(int hunting) {
    this.hunting = hunting;
}

void setMining(int mining) {
    this.mining = mining;
}

void setBargaining(int bargaining) {
    this.bargaining = bargaining;
}

void setCamping(int camping) {
    this.camping = camping;
}

void setFirstAid(int firstAid) {
    this.firstAid = firstAid;
}

void setLore(int lore) {
    this.lore = lore;
}

void setPickLocks(int pickLocks) {
    this.pickLocks = pickLocks;
}

void setScouting(int scouting) {
    this.scouting = scouting;
}

void setSearch(int search) {
    this.search = search;
}

void setStealth(int stealth) {
    this.stealth = stealth;
}

void setTraps(int traps) {
    this.traps = traps;
}

void setAeolandis(int aeolandis) {
    this.aeolandis = aeolandis;
}

void setHieroform(int hieroform) {
    this.hieroform = hieroform;
}

void setHighGundis(int highGundis) {
    this.highGundis = highGundis;
}

void setOldPraxic(int oldPraxic) {
    this.oldPraxic = oldPraxic;
}

void setPraxic(int praxic) {
    this.praxic = praxic;
}

void setRunic(int runic) {
    this.runic = runic;
}

//------------------------------------------------------------------------------//
//----------                      Class Functions                     ----------//
//------------------------------------------------------------------------------//

