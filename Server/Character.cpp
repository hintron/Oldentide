// File:     Character.cpp
// Created:  April 19, 2015
// Author:   Joseph DeVictoria
// Purpose:  Child class representing any living object in Oldentide.
//        :  Inherits from "Object" class.

#include "Character.h"

using namespace std;

//------------------------------------------------------------------------------//
//----------                     Class Constructors                   ----------//
//------------------------------------------------------------------------------//

Character :: Character(string name, string lastname, string race, string gender,
                       string profession, int weight, int x, int y, int z,
                       float direction)
           : Object(weight, x, y, z, direction) {
    setName(name);
    setLastname(lastname);
    setRace(race);
    setGender(gender);
    setProfession(profession);
}

Character :: Character(string name, string lastname, string race, string gender,
                       string profession) 
           : Object(0, 0, 0, 0, 0.0) {
    setName(name);
    setLastname(lastname);
    setRace(race);
    setGender(gender);
    setProfession(profession);
}

//------------------------------------------------------------------------------//
//----------                      Getter Functions                    ----------//
//------------------------------------------------------------------------------//

string Character :: getName() {
    return name;
}

string Character :: getLastname() {
    return lastname;
}

string Character :: getRace() {
    return race;
}

string Character :: getGender() {
    return gender;
}

string Character :: getProfession() {
    return profession;
}

int Character :: getLevel() {
    return level;
}

int Character :: getHP() {
    return hp;
}

int Character :: getBP() {
    return bp;
}

int Character :: getMP() {
    return mp;
}

int Character :: getEP() {
    return ep;
}

int Character :: getStrength() {
    return strength;
}

int Character :: getConstitution() {
    return constitution;
}

int Character :: getIntelligence() {
    return intelligence;
}

int Character :: getDexterity() {
    return dexterity;
}

int Character :: getAxe() {
    return axe;
}

int Character :: getDagger() {
    return dagger;
}

int Character :: getUnarmed() {
    return unarmed;
}

int Character :: getHammer() {
    return hammer;
}

int Character :: getPolearm() {
    return polearm;
}

int Character :: getSpear() {
    return spear;
}

int Character :: getStaff() {
    return staff;
}

int Character :: getSword() {
    return sword;
}

int Character :: getArchery() {
    return archery;
}

int Character :: getCrossbow() {
    return crossbow;
}

int Character :: getSling() {
    return sling;
}

int Character :: getThrown() {
    return thrown;
}

int Character :: getArmor() {
    return armor;
}

int Character :: getDualWeapon() {
    return dualWeapon;
}

int Character :: getShield() {
    return shield;
}

int Character :: getBardic() {
    return bardic;
}

int Character :: getConjuring() {
    return conjuring;
}

int Character :: getDruidic() {
    return druidic;
}

int Character :: getIllusion() {
    return illusion;
}

int Character :: getNecromancy() {
    return necromancy;
}

int Character :: getSorcery() {
    return sorcery;
}

int Character :: getShamanic() {
    return shamanic;
}

int Character :: getSummoning() {
    return summoning;
}

int Character :: getSpellcraft() {
    return spellcraft;
}

int Character :: getFocus() {
    return focus;
}

int Character :: getArmorsmithing() {
    return armorsmithing;
}

int Character :: getTailoring() {
    return tailoring;
}

int Character :: getFletching() {
    return fletching;
}

int Character :: getWeaponsmith() {
    return weaponsmithing;
}

int Character :: getAlchemy() {
    return alchemy;
}

int Character :: getLapidary() {
    return lapidary;
}

int Character :: getCalligraphy() {
    return calligraphy;
}

int Character :: getEnchanting() {
    return enchanting;
}

int Character :: getHerbalism() {
    return herbalism;
}

int Character :: getHunting() {
    return hunting;
}

int Character :: getMining() {
    return mining;
}

int Character :: getBargaining() {
    return bargaining;
}

int Character :: getCamping() {
    return camping;
}

int Character :: getFirstAid() {
    return firstAid;
}

int Character :: getLore() {
    return lore;
}

int Character :: getPickLocks() {
    return pickLocks;
}

int Character :: getScouting() {
    return scouting;
}

int Character :: getSearch() {
    return search;
}

int Character :: getStealth() {
    return stealth;
}

int Character :: getTraps() {
    return traps;
}

int Character :: getAeolandis() {
    return aeolandis;
}

int Character :: getHieroform() {
    return hieroform;
}

int Character :: getHighGundis() {
    return highGundis;
}

int Character :: getOldPraxic() {
    return oldPraxic;
}

int Character :: getPraxic() {
    return praxic;
}

int Character :: getRunic() {
    return runic;
}

//------------------------------------------------------------------------------//
//----------                      Setter Functions                    ----------//
//------------------------------------------------------------------------------//

void Character :: setName(string name) {
    this->name = name;
}

void Character :: setLastname(string lastname) {
    this->lastname = lastname;
}
void Character :: setRace(string race) {
    this->race = race;
}

void Character :: setGender(string gender) {
    this->gender = gender;
}

void Character :: setProfession(string profession) {
    this->profession = profession;
}

void Character :: setLevel(int level) {
    this->level = level;
}

void Character :: setHP(int hp) {
    this->hp = hp;
}

void Character :: setBP(int bp) {
    this->bp = bp;
}

void Character :: setMP(int mp) {
    this->mp = mp;
}

void Character :: setEP(int ep) {
    this->ep = ep;
}

void Character :: setStrength(int strength) {
    this->strength = strength;
}

void Character :: setConstitution(int constitution) {
    this->constitution = constitution;
}

void Character :: setIntelligence(int intelligence) {
    this->intelligence = intelligence;
}

void Character :: setDexterity(int dexterity) {
    this->dexterity = dexterity;
}

void Character :: setAxe(int axe) {
    this->axe = axe;
}

void Character :: setDagger(int dagger) {
    this->dagger = dagger;
}

void Character :: setUnarmed(int unarmed) {
    this->unarmed = unarmed;
}

void Character :: setHammer(int hammer) {
    this->hammer = hammer;
}

void Character :: setPolearm(int polearm) {
    this->polearm = polearm;
}

void Character :: setSpear(int spear) {
    this->spear = spear;
}

void Character :: setStaff(int staff) {
    this->staff = staff;
}

void Character :: setSword(int sword) {
    this->sword = sword;
}

void Character :: setArchery(int archery) {
    this->archery = archery;
}

void Character :: setCrossbow(int crossbow) {
    this->crossbow = crossbow;
}

void Character :: setSling(int sling) {
    this->sling = sling;
}

void Character :: setThrown(int thrown) {
    this->thrown = thrown;
}

void Character :: setArmor(int armor) {
    this->armor = armor;
}

void Character :: setDualWeapon(int dualWeapon) {
    this->dualWeapon = dualWeapon;
}

void Character :: setShield(int shield) {
    this->shield = shield;
}

void Character :: setBardic(int bardic) {
    this->bardic = bardic;
}

void Character :: setConjuring(int conjuring) {
    this->conjuring = conjuring;
}

void Character :: setDruidic(int druidic) {
    this->druidic = druidic;
}

void Character :: setIllusion(int illusion) {
    this->illusion = illusion;
}

void Character :: setNecromancy(int necromancy) {
    this->necromancy = necromancy;
}

void Character :: setSorcery(int sorcery) {
    this->sorcery = sorcery;
}

void Character :: setShamanic(int shamanic) {
    this->shamanic = shamanic;
}

void Character :: setSummoning(int summoning) {
    this->summoning = summoning;
}

void Character :: setSpellcraft(int spellcraft) {
    this->spellcraft = spellcraft;
}

void Character :: setFocus(int focus) {
    this->focus = focus;
}

void Character :: setArmorsmithing(int armorsmithing) {
    this->armorsmithing = armorsmithing;
}

void Character :: setTailoring(int tailoring) {
    this->tailoring = tailoring;
}

void Character :: setFletching(int fletching) {
    this->fletching = fletching;
}

void Character :: setWeaponsmith(int weaponsmithing) {
    this->weaponsmithing = weaponsmithing;
}

void Character :: setAlchemy(int alchemy) {
    this->alchemy = alchemy;
}

void Character :: setLapidary(int lapidary) {
    this->lapidary = lapidary;
}

void Character :: setCalligraphy(int calligraphy) {
    this->calligraphy = calligraphy;
}

void Character :: setEnchanting(int enchanting) {
    this->enchanting = enchanting;
}

void Character :: setHerbalism(int herbalism) {
    this->herbalism = herbalism;
}

void Character :: setHunting(int hunting) {
    this->hunting = hunting;
}

void Character :: setMining(int mining) {
    this->mining = mining;
}

void Character :: setBargaining(int bargaining) {
    this->bargaining = bargaining;
}

void Character :: setCamping(int camping) {
    this->camping = camping;
}

void Character :: setFirstAid(int firstAid) {
    this->firstAid = firstAid;
}

void Character :: setLore(int lore) {
    this->lore = lore;
}

void Character :: setPickLocks(int pickLocks) {
    this->pickLocks = pickLocks;
}

void Character :: setScouting(int scouting) {
    this->scouting = scouting;
}

void Character :: setSearch(int search) {
    this->search = search;
}

void Character :: setStealth(int stealth) {
    this->stealth = stealth;
}

void Character :: setTraps(int traps) {
    this->traps = traps;
}

void Character :: setAeolandis(int aeolandis) {
    this->aeolandis = aeolandis;
}

void Character :: setHieroform(int hieroform) {
    this->hieroform = hieroform;
}

void Character :: setHighGundis(int highGundis) {
    this->highGundis = highGundis;
}

void Character :: setOldPraxic(int oldPraxic) {
    this->oldPraxic = oldPraxic;
}

void Character :: setPraxic(int praxic) {
    this->praxic = praxic;
}

void Character :: setRunic(int runic) {
    this->runic = runic;
}

//------------------------------------------------------------------------------//
//----------                      Class Functions                     ----------//
//------------------------------------------------------------------------------//

