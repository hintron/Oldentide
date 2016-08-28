// File:     Player.cpp
// Created:  April 19, 2015
// Author:   Joseph DeVictoria
// Purpose:  Child class representing any player in Oldentide.
//        :  Inherits from "Character" class.

#include "Player.h"
#include "Utils.h"

//------------------------------------------------------------------------------------------------//
//-------------------                     Class Constructors                   -------------------//
//------------------------------------------------------------------------------------------------//

Player::Player(std::string account, std::string profession, int id, int session, float weight, 
               int axe, int dagger, int unarmed, int hammer, int polearm, int spear, int staff, 
               int sword, int archery, int crossbow, int sling, int thrown, int armor, 
               int dualWeapon, int shield, int bardic, int conjuring, int druidic, int illusion, 
               int necromancy, int sorcery, int shamanic, int spellcraft, int summoning, int focus, 
               int armorsmithing, int tailoring, int fletching, int weaponsmithing, int alchemy, 
               int lapidary, int calligraphy, int enchanting, int herbalism, int hunting, 
               int mining, int bargaining, int camping, int firstAid, int lore, int pickLocks, 
               int scouting, int search, int stealth, int traps, int aeolandis, int hieroform, 
               int highGundis, int oldPraxic, int praxic, int runic, std::string name, 
               std::string lastname, std::string race, std::string gender, std::string face, 
               std::string skin, std::string zone, int level, int hp, int maxHp, int bp, int maxBp, 
               int mp, int maxMp, int ep, int maxEp, int strength, int constitution, 
               int intelligence, int dexterity, float x, float y, float z, float pitch, float yaw)
       :Character(name, lastname, race, gender, face, skin, zone, level, hp, maxHp, bp, maxBp, mp, 
                  maxMp, ep, maxEp, strength, constitution, intelligence, dexterity, x, y, z, 
                  pitch, yaw){
    setAccount(account);
    setProfession(profession);
    setId(id);
    setSession(session);
    setWeight(weight);
    setAxe(axe);
    setDagger(dagger);
    setUnarmed(unarmed);
    setHammer(hammer);
    setPolearm(polearm);
    setSpear(spear);
    setStaff(staff);
    setSword(sword);
    setArchery(archery);
    setCrossbow(crossbow);
    setSling(sling);
    setThrown(thrown);
    setArmor(armor);
    setDualWeapon(dualWeapon);
    setShield(shield);
    setBardic(bardic);
    setConjuring(conjuring);
    setDruidic(druidic);
    setIllusion(illusion);
    setNecromancy(necromancy);
    setSorcery(sorcery);
    setShamanic(shamanic);
    setSummoning(summoning);
    setSpellcraft(spellcraft);
    setFocus(focus);
    setArmorsmithing(armorsmithing);
    setTailoring(tailoring);
    setFletching(fletching);
    setWeaponsmith(weaponsmithing);
    setAlchemy(alchemy);
    setLapidary(lapidary);
    setCalligraphy(calligraphy);
    setEnchanting(enchanting);
    setHerbalism(herbalism);
    setHunting(hunting);
    setMining(mining);
    setBargaining(bargaining);
    setCamping(camping);
    setFirstAid(firstAid);
    setLore(lore);
    setPickLocks(pickLocks);
    setScouting(scouting);
    setSearch(search);
    setStealth(stealth);
    setTraps(traps);
    setAeolandis(aeolandis);
    setHieroform(hieroform);
    setHighGundis(highGundis);
    setOldPraxic(oldPraxic);
    setPraxic(praxic);
    setRunic(runic);
}

// Deserialization Constuctor.
Player::Player(std::string fromString)
       :Character(fromString){
    std::vector<std::string> tokens = Utils::tokenfy(fromString, '|');
    if (tokens[0] != "PLAYER_OBJECT")
        return;
    setAccount(tokens[1]);
    setProfession(tokens[2]);
    setId(std::stoi(tokens[3]));
    setSession(std::stoi(tokens[4]));
    setWeight(std::stoi(tokens[5]));
    setAxe(std::stoi(tokens[6]));
    setDagger(std::stoi(tokens[7]));
    setUnarmed(std::stoi(tokens[8]));
    setHammer(std::stoi(tokens[9]));
    setPolearm(std::stoi(tokens[10]));
    setSpear(std::stoi(tokens[11]));
    setStaff(std::stoi(tokens[12]));
    setSword(std::stoi(tokens[13]));
    setArchery(std::stoi(tokens[14]));
    setCrossbow(std::stoi(tokens[15]));
    setSling(std::stoi(tokens[16]));
    setThrown(std::stoi(tokens[17]));
    setArmor(std::stoi(tokens[18]));
    setDualWeapon(std::stoi(tokens[19]));
    setShield(std::stoi(tokens[20]));
    setBardic(std::stoi(tokens[21]));
    setConjuring(std::stoi(tokens[22]));
    setDruidic(std::stoi(tokens[23]));
    setIllusion(std::stoi(tokens[24]));
    setNecromancy(std::stoi(tokens[25]));
    setSorcery(std::stoi(tokens[26]));
    setShamanic(std::stoi(tokens[27]));
    setSummoning(std::stoi(tokens[28]));
    setSpellcraft(std::stoi(tokens[29]));
    setFocus(std::stoi(tokens[30]));
    setArmorsmithing(std::stoi(tokens[31]));
    setTailoring(std::stoi(tokens[32]));
    setFletching(std::stoi(tokens[33]));
    setWeaponsmith(std::stoi(tokens[34]));
    setAlchemy(std::stoi(tokens[35]));
    setLapidary(std::stoi(tokens[36]));
    setCalligraphy(std::stoi(tokens[37]));
    setEnchanting(std::stoi(tokens[38]));
    setHerbalism(std::stoi(tokens[39]));
    setHunting(std::stoi(tokens[40]));
    setMining(std::stoi(tokens[41]));
    setBargaining(std::stoi(tokens[42]));
    setCamping(std::stoi(tokens[43]));
    setFirstAid(std::stoi(tokens[44]));
    setLore(std::stoi(tokens[45]));
    setPickLocks(std::stoi(tokens[46]));
    setScouting(std::stoi(tokens[47]));
    setSearch(std::stoi(tokens[48]));
    setStealth(std::stoi(tokens[49]));
    setTraps(std::stoi(tokens[50]));
    setAeolandis(std::stoi(tokens[51]));
    setHieroform(std::stoi(tokens[52]));
    setHighGundis(std::stoi(tokens[53]));
    setOldPraxic(std::stoi(tokens[54]));
    setPraxic(std::stoi(tokens[55]));
    setRunic(std::stoi(tokens[56]));
}

//------------------------------------------------------------------------------------------------//
//-------------------                      Getter Functions                    -------------------//
//------------------------------------------------------------------------------------------------//

std::string Player::getAccount(){
    return account;
}

std::string Player::getProfession(){
    return profession;
}

int Player::getId(){
    return id;
}

int Player::getSession(){
    return session;
}

float Player::getWeight(){
    return weight;
}

int Player::getAxe(){
    return axe;
}

int Player::getDagger(){
    return dagger;
}

int Player::getUnarmed(){
    return unarmed;
}

int Player::getHammer(){
    return hammer;
}

int Player::getPolearm(){
    return polearm;
}

int Player::getSpear(){
    return spear;
}

int Player::getStaff(){
    return staff;
}

int Player::getSword(){
    return sword;
}

int Player::getArchery(){
    return archery;
}

int Player::getCrossbow(){
    return crossbow;
}

int Player::getSling(){
    return sling;
}

int Player::getThrown(){
    return thrown;
}

int Player::getArmor(){
    return armor;
}

int Player::getDualWeapon(){
    return dualWeapon;
}

int Player::getShield(){
    return shield;
}

int Player::getBardic(){
    return bardic;
}

int Player::getConjuring(){
    return conjuring;
}

int Player::getDruidic(){
    return druidic;
}

int Player::getIllusion(){
    return illusion;
}

int Player::getNecromancy(){
    return necromancy;
}

int Player::getSorcery(){
    return sorcery;
}

int Player::getShamanic(){
    return shamanic;
}

int Player::getSummoning(){
    return summoning;
}

int Player::getSpellcraft(){
    return spellcraft;
}

int Player::getFocus(){
    return focus;
}

int Player::getArmorsmithing(){
    return armorsmithing;
}

int Player::getTailoring(){
    return tailoring;
}

int Player::getFletching(){
    return fletching;
}

int Player::getWeaponsmith(){
    return weaponsmithing;
}

int Player::getAlchemy(){
    return alchemy;
}

int Player::getLapidary(){
    return lapidary;
}

int Player::getCalligraphy(){
    return calligraphy;
}

int Player::getEnchanting(){
    return enchanting;
}

int Player::getHerbalism(){
    return herbalism;
}

int Player::getHunting(){
    return hunting;
}

int Player::getMining(){
    return mining;
}

int Player::getBargaining(){
    return bargaining;
}

int Player::getCamping(){
    return camping;
}

int Player::getFirstAid(){
    return firstAid;
}

int Player::getLore(){
    return lore;
}

int Player::getPickLocks(){
    return pickLocks;
}

int Player::getScouting(){
    return scouting;
}

int Player::getSearch(){
    return search;
}

int Player::getStealth(){
    return stealth;
}

int Player::getTraps(){
    return traps;
}

int Player::getAeolandis(){
    return aeolandis;
}

int Player::getHieroform(){
    return hieroform;
}

int Player::getHighGundis(){
    return highGundis;
}

int Player::getOldPraxic(){
    return oldPraxic;
}

int Player::getPraxic(){
    return praxic;
}

int Player::getRunic(){
    return runic;
}

//------------------------------------------------------------------------------------------------//
//-------------------                      Setter Functions                    -------------------//
//------------------------------------------------------------------------------------------------//

void Player::setAccount(std::string account){
    this->account = account;
}

void Player::setProfession(std::string profession){
    this->profession = profession;
}

void Player::setId(int id){
    this->id = id;
}

void Player::setSession(int session){
    this->session = session;
}

void Player::setWeight(float weight){
    this->weight = weight;
}

void Player::setAxe(int axe){
    this->axe = axe;
}

void Player::setDagger(int dagger){
    this->dagger = dagger;
}

void Player::setUnarmed(int unarmed){
    this->unarmed = unarmed;
}

void Player::setHammer(int hammer){
    this->hammer = hammer;
}

void Player::setPolearm(int polearm){
    this->polearm = polearm;
}

void Player::setSpear(int spear){
    this->spear = spear;
}

void Player::setStaff(int staff){
    this->staff = staff;
}

void Player::setSword(int sword){
    this->sword = sword;
}

void Player::setArchery(int archery){
    this->archery = archery;
}

void Player::setCrossbow(int crossbow){
    this->crossbow = crossbow;
}

void Player::setSling(int sling){
    this->sling = sling;
}

void Player::setThrown(int thrown){
    this->thrown = thrown;
}

void Player::setArmor(int armor){
    this->armor = armor;
}

void Player::setDualWeapon(int dualWeapon){
    this->dualWeapon = dualWeapon;
}

void Player::setShield(int shield){
    this->shield = shield;
}

void Player::setBardic(int bardic){
    this->bardic = bardic;
}

void Player::setConjuring(int conjuring){
    this->conjuring = conjuring;
}

void Player::setDruidic(int druidic){
    this->druidic = druidic;
}

void Player::setIllusion(int illusion){
    this->illusion = illusion;
}

void Player::setNecromancy(int necromancy){
    this->necromancy = necromancy;
}

void Player::setSorcery(int sorcery){
    this->sorcery = sorcery;
}

void Player::setShamanic(int shamanic){
    this->shamanic = shamanic;
}

void Player::setSummoning(int summoning){
    this->summoning = summoning;
}

void Player::setSpellcraft(int spellcraft){
    this->spellcraft = spellcraft;
}

void Player::setFocus(int focus){
    this->focus = focus;
}

void Player::setArmorsmithing(int armorsmithing){
    this->armorsmithing = armorsmithing;
}

void Player::setTailoring(int tailoring){
    this->tailoring = tailoring;
}

void Player::setFletching(int fletching){
    this->fletching = fletching;
}

void Player::setWeaponsmith(int weaponsmithing){
    this->weaponsmithing = weaponsmithing;
}

void Player::setAlchemy(int alchemy){
    this->alchemy = alchemy;
}

void Player::setLapidary(int lapidary){
    this->lapidary = lapidary;
}

void Player::setCalligraphy(int calligraphy){
    this->calligraphy = calligraphy;
}

void Player::setEnchanting(int enchanting){
    this->enchanting = enchanting;
}

void Player::setHerbalism(int herbalism){
    this->herbalism = herbalism;
}

void Player::setHunting(int hunting){
    this->hunting = hunting;
}

void Player::setMining(int mining){
    this->mining = mining;
}

void Player::setBargaining(int bargaining){
    this->bargaining = bargaining;
}

void Player::setCamping(int camping){
    this->camping = camping;
}

void Player::setFirstAid(int firstAid){
    this->firstAid = firstAid;
}

void Player::setLore(int lore){
    this->lore = lore;
}

void Player::setPickLocks(int pickLocks){
    this->pickLocks = pickLocks;
}

void Player::setScouting(int scouting){
    this->scouting = scouting;
}

void Player::setSearch(int search){
    this->search = search;
}

void Player::setStealth(int stealth){
    this->stealth = stealth;
}

void Player::setTraps(int traps){
    this->traps = traps;
}

void Player::setAeolandis(int aeolandis){
    this->aeolandis = aeolandis;
}

void Player::setHieroform(int hieroform){
    this->hieroform = hieroform;
}

void Player::setHighGundis(int highGundis){
    this->highGundis = highGundis;
}

void Player::setOldPraxic(int oldPraxic){
    this->oldPraxic = oldPraxic;
}

void Player::setPraxic(int praxic){
    this->praxic = praxic;
}

void Player::setRunic(int runic){
    this->runic = runic;
}


//------------------------------------------------------------------------------------------------//
//-------------------                      Class Functions                     -------------------//
//------------------------------------------------------------------------------------------------//

std::string Player::toString(){
    std::string serial;
    serial.append("PLAYER_OBJECT|");
    serial.append(account);
    serial.append("|");
    serial.append(profession);
    serial.append("|");
    serial.append(std::to_string(id));
    serial.append("|");
    serial.append(std::to_string(session));
    serial.append("|");
    serial.append(std::to_string(weight));
    serial.append("|");
    serial.append(std::to_string(axe));
    serial.append("|");
    serial.append(std::to_string(dagger)); 
    serial.append("|");
    serial.append(std::to_string(unarmed));
    serial.append("|");
    serial.append(std::to_string(hammer));
    serial.append("|");
    serial.append(std::to_string(polearm));
    serial.append("|");
    serial.append(std::to_string(spear));
    serial.append("|");
    serial.append(std::to_string(staff));
    serial.append("|");
    serial.append(std::to_string(sword));
    serial.append("|");
    serial.append(std::to_string(archery));
    serial.append("|");
    serial.append(std::to_string(crossbow));
    serial.append("|");
    serial.append(std::to_string(sling));
    serial.append("|");
    serial.append(std::to_string(thrown));
    serial.append("|");
    serial.append(std::to_string(armor));
    serial.append("|");
    serial.append(std::to_string(dualWeapon));
    serial.append("|");
    serial.append(std::to_string(shield));
    serial.append("|");
    serial.append(std::to_string(bardic));
    serial.append("|");
    serial.append(std::to_string(conjuring));
    serial.append("|");
    serial.append(std::to_string(druidic));
    serial.append("|");
    serial.append(std::to_string(illusion));
    serial.append("|");
    serial.append(std::to_string(necromancy));
    serial.append("|");
    serial.append(std::to_string(sorcery));
    serial.append("|");
    serial.append(std::to_string(shamanic));
    serial.append("|");
    serial.append(std::to_string(spellcraft));
    serial.append("|");
    serial.append(std::to_string(summoning));
    serial.append("|");
    serial.append(std::to_string(focus));
    serial.append("|");
    serial.append(std::to_string(armorsmithing));
    serial.append("|");
    serial.append(std::to_string(tailoring));
    serial.append("|");
    serial.append(std::to_string(fletching));
    serial.append("|");
    serial.append(std::to_string(weaponsmithing));
    serial.append("|");
    serial.append(std::to_string(alchemy));
    serial.append("|");
    serial.append(std::to_string(lapidary));
    serial.append("|");
    serial.append(std::to_string(calligraphy));
    serial.append("|");
    serial.append(std::to_string(enchanting));
    serial.append("|");
    serial.append(std::to_string(herbalism));
    serial.append("|");
    serial.append(std::to_string(hunting));
    serial.append("|");
    serial.append(std::to_string(mining));
    serial.append("|");
    serial.append(std::to_string(bargaining));
    serial.append("|");
    serial.append(std::to_string(camping));
    serial.append("|");
    serial.append(std::to_string(firstAid));
    serial.append("|");
    serial.append(std::to_string(lore));
    serial.append("|");
    serial.append(std::to_string(pickLocks));
    serial.append("|");
    serial.append(std::to_string(scouting));
    serial.append("|");
    serial.append(std::to_string(search));
    serial.append("|");
    serial.append(std::to_string(stealth));
    serial.append("|");
    serial.append(std::to_string(traps));
    serial.append("|");
    serial.append(std::to_string(aeolandis));
    serial.append("|");
    serial.append(std::to_string(hieroform));
    serial.append("|");
    serial.append(std::to_string(highGundis));
    serial.append("|");
    serial.append(std::to_string(oldPraxic));
    serial.append("|");
    serial.append(std::to_string(praxic));
    serial.append("|");
    serial.append(std::to_string(runic));
    serial.append("|");
    serial.append(name);
    serial.append("|");
    serial.append(lastname);
    serial.append("|");
    serial.append(race);
    serial.append("|");
    serial.append(gender);
    serial.append("|");
    serial.append(face);
    serial.append("|");
    serial.append(skin);
    serial.append("|");
    serial.append(zone);
    serial.append("|");
    serial.append(std::to_string(level));
    serial.append("|");
    serial.append(std::to_string(hp));
    serial.append("|");
    serial.append(std::to_string(maxHp));
    serial.append("|");
    serial.append(std::to_string(bp));
    serial.append("|");
    serial.append(std::to_string(maxBp));
    serial.append("|");
    serial.append(std::to_string(mp));
    serial.append("|");
    serial.append(std::to_string(maxMp));
    serial.append("|");
    serial.append(std::to_string(ep));
    serial.append("|");
    serial.append(std::to_string(maxEp));
    serial.append("|");
    serial.append(std::to_string(strength));
    serial.append("|");
    serial.append(std::to_string(constitution));
    serial.append("|");
    serial.append(std::to_string(intelligence));
    serial.append("|");
    serial.append(std::to_string(dexterity));
    serial.append("|");
    serial.append(std::to_string(x));
    serial.append("|");
    serial.append(std::to_string(y));
    serial.append("|");
    serial.append(std::to_string(z));
    serial.append("|");
    serial.append(std::to_string(pitch));
    serial.append("|");
    serial.append(std::to_string(yaw));
    return serial;
}
