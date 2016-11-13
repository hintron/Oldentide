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
                  pitch, yaw) {
    SetAccount(account);
    SetProfession(profession);
    SetId(id);
    SetSession(session);
    SetWeight(weight);
    SetAxe(axe);
    SetDagger(dagger);
    SetUnarmed(unarmed);
    SetHammer(hammer);
    SetPolearm(polearm);
    SetSpear(spear);
    SetStaff(staff);
    SetSword(sword);
    SetArchery(archery);
    SetCrossbow(crossbow);
    SetSling(sling);
    SetThrown(thrown);
    SetArmor(armor);
    SetDualWeapon(dualWeapon);
    SetShield(shield);
    SetBardic(bardic);
    SetConjuring(conjuring);
    SetDruidic(druidic);
    SetIllusion(illusion);
    SetNecromancy(necromancy);
    SetSorcery(sorcery);
    SetShamanic(shamanic);
    SetSummoning(summoning);
    SetSpellcraft(spellcraft);
    SetFocus(focus);
    SetArmorsmithing(armorsmithing);
    SetTailoring(tailoring);
    SetFletching(fletching);
    SetWeaponsmith(weaponsmithing);
    SetAlchemy(alchemy);
    SetLapidary(lapidary);
    SetCalligraphy(calligraphy);
    SetEnchanting(enchanting);
    SetHerbalism(herbalism);
    SetHunting(hunting);
    SetMining(mining);
    SetBargaining(bargaining);
    SetCamping(camping);
    SetFirstAid(firstAid);
    SetLore(lore);
    SetPickLocks(pickLocks);
    SetScouting(scouting);
    SetSearch(search);
    SetStealth(stealth);
    SetTraps(traps);
    SetAeolandis(aeolandis);
    SetHieroform(hieroform);
    SetHighGundis(highGundis);
    SetOldPraxic(oldPraxic);
    SetPraxic(praxic);
    SetRunic(runic);
}

// Deserialization Constuctor.
Player::Player(std::string fromString)
       :Character(fromString) {
    std::vector<std::string> tokens = utils::Tokenfy(fromString, '|');
    if (tokens[0] != "PLAYER_OBJECT")
        return;
    SetAccount(tokens[1]);
    SetProfession(tokens[2]);
    SetId(std::stoi(tokens[3]));
    SetSession(std::stoi(tokens[4]));
    SetWeight(std::stoi(tokens[5]));
    SetAxe(std::stoi(tokens[6]));
    SetDagger(std::stoi(tokens[7]));
    SetUnarmed(std::stoi(tokens[8]));
    SetHammer(std::stoi(tokens[9]));
    SetPolearm(std::stoi(tokens[10]));
    SetSpear(std::stoi(tokens[11]));
    SetStaff(std::stoi(tokens[12]));
    SetSword(std::stoi(tokens[13]));
    SetArchery(std::stoi(tokens[14]));
    SetCrossbow(std::stoi(tokens[15]));
    SetSling(std::stoi(tokens[16]));
    SetThrown(std::stoi(tokens[17]));
    SetArmor(std::stoi(tokens[18]));
    SetDualWeapon(std::stoi(tokens[19]));
    SetShield(std::stoi(tokens[20]));
    SetBardic(std::stoi(tokens[21]));
    SetConjuring(std::stoi(tokens[22]));
    SetDruidic(std::stoi(tokens[23]));
    SetIllusion(std::stoi(tokens[24]));
    SetNecromancy(std::stoi(tokens[25]));
    SetSorcery(std::stoi(tokens[26]));
    SetShamanic(std::stoi(tokens[27]));
    SetSummoning(std::stoi(tokens[28]));
    SetSpellcraft(std::stoi(tokens[29]));
    SetFocus(std::stoi(tokens[30]));
    SetArmorsmithing(std::stoi(tokens[31]));
    SetTailoring(std::stoi(tokens[32]));
    SetFletching(std::stoi(tokens[33]));
    SetWeaponsmith(std::stoi(tokens[34]));
    SetAlchemy(std::stoi(tokens[35]));
    SetLapidary(std::stoi(tokens[36]));
    SetCalligraphy(std::stoi(tokens[37]));
    SetEnchanting(std::stoi(tokens[38]));
    SetHerbalism(std::stoi(tokens[39]));
    SetHunting(std::stoi(tokens[40]));
    SetMining(std::stoi(tokens[41]));
    SetBargaining(std::stoi(tokens[42]));
    SetCamping(std::stoi(tokens[43]));
    SetFirstAid(std::stoi(tokens[44]));
    SetLore(std::stoi(tokens[45]));
    SetPickLocks(std::stoi(tokens[46]));
    SetScouting(std::stoi(tokens[47]));
    SetSearch(std::stoi(tokens[48]));
    SetStealth(std::stoi(tokens[49]));
    SetTraps(std::stoi(tokens[50]));
    SetAeolandis(std::stoi(tokens[51]));
    SetHieroform(std::stoi(tokens[52]));
    SetHighGundis(std::stoi(tokens[53]));
    SetOldPraxic(std::stoi(tokens[54]));
    SetPraxic(std::stoi(tokens[55]));
    SetRunic(std::stoi(tokens[56]));
}

//------------------------------------------------------------------------------------------------//
//-------------------                      Getter Functions                    -------------------//
//------------------------------------------------------------------------------------------------//

std::string Player::GetAccount() {
    return account;
}

std::string Player::GetProfession() {
    return profession;
}

int Player::GetId() {
    return id;
}

int Player::GetSession() {
    return session;
}

float Player::GetWeight() {
    return weight;
}

int Player::GetAxe() {
    return axe;
}

int Player::GetDagger() {
    return dagger;
}

int Player::GetUnarmed() {
    return unarmed;
}

int Player::GetHammer() {
    return hammer;
}

int Player::GetPolearm() {
    return polearm;
}

int Player::GetSpear() {
    return spear;
}

int Player::GetStaff() {
    return staff;
}

int Player::GetSword() {
    return sword;
}

int Player::GetArchery() {
    return archery;
}

int Player::GetCrossbow() {
    return crossbow;
}

int Player::GetSling() {
    return sling;
}

int Player::GetThrown() {
    return thrown;
}

int Player::GetArmor() {
    return armor;
}

int Player::GetDualWeapon() {
    return dualWeapon;
}

int Player::GetShield() {
    return shield;
}

int Player::GetBardic() {
    return bardic;
}

int Player::GetConjuring() {
    return conjuring;
}

int Player::GetDruidic() {
    return druidic;
}

int Player::GetIllusion() {
    return illusion;
}

int Player::GetNecromancy() {
    return necromancy;
}

int Player::GetSorcery() {
    return sorcery;
}

int Player::GetShamanic() {
    return shamanic;
}

int Player::GetSummoning() {
    return summoning;
}

int Player::GetSpellcraft() {
    return spellcraft;
}

int Player::GetFocus() {
    return focus;
}

int Player::GetArmorsmithing() {
    return armorsmithing;
}

int Player::GetTailoring() {
    return tailoring;
}

int Player::GetFletching() {
    return fletching;
}

int Player::GetWeaponsmithing() {
    return weaponsmithing;
}

int Player::GetAlchemy() {
    return alchemy;
}

int Player::GetLapidary() {
    return lapidary;
}

int Player::GetCalligraphy() {
    return calligraphy;
}

int Player::GetEnchanting() {
    return enchanting;
}

int Player::GetHerbalism() {
    return herbalism;
}

int Player::GetHunting() {
    return hunting;
}

int Player::GetMining() {
    return mining;
}

int Player::GetBargaining() {
    return bargaining;
}

int Player::GetCamping() {
    return camping;
}

int Player::GetFirstAid() {
    return firstAid;
}

int Player::GetLore() {
    return lore;
}

int Player::GetPickLocks() {
    return pickLocks;
}

int Player::GetScouting() {
    return scouting;
}

int Player::GetSearch() {
    return search;
}

int Player::GetStealth() {
    return stealth;
}

int Player::GetTraps() {
    return traps;
}

int Player::GetAeolandis() {
    return aeolandis;
}

int Player::GetHieroform() {
    return hieroform;
}

int Player::GetHighGundis() {
    return highGundis;
}

int Player::GetOldPraxic() {
    return oldPraxic;
}

int Player::GetPraxic() {
    return praxic;
}

int Player::GetRunic() {
    return runic;
}

//------------------------------------------------------------------------------------------------//
//-------------------                      Setter Functions                    -------------------//
//------------------------------------------------------------------------------------------------//

void Player::SetAccount(std::string account) {
    this->account = account;
}

void Player::SetProfession(std::string profession) {
    this->profession = profession;
}

void Player::SetId(int id) {
    this->id = id;
}

void Player::SetSession(int session) {
    this->session = session;
}

void Player::SetWeight(float weight) {
    this->weight = weight;
}

void Player::SetAxe(int axe) {
    this->axe = axe;
}

void Player::SetDagger(int dagger) {
    this->dagger = dagger;
}

void Player::SetUnarmed(int unarmed) {
    this->unarmed = unarmed;
}

void Player::SetHammer(int hammer) {
    this->hammer = hammer;
}

void Player::SetPolearm(int polearm) {
    this->polearm = polearm;
}

void Player::SetSpear(int spear) {
    this->spear = spear;
}

void Player::SetStaff(int staff) {
    this->staff = staff;
}

void Player::SetSword(int sword) {
    this->sword = sword;
}

void Player::SetArchery(int archery) {
    this->archery = archery;
}

void Player::SetCrossbow(int crossbow) {
    this->crossbow = crossbow;
}

void Player::SetSling(int sling) {
    this->sling = sling;
}

void Player::SetThrown(int thrown) {
    this->thrown = thrown;
}

void Player::SetArmor(int armor) {
    this->armor = armor;
}

void Player::SetDualWeapon(int dualWeapon) {
    this->dualWeapon = dualWeapon;
}

void Player::SetShield(int shield) {
    this->shield = shield;
}

void Player::SetBardic(int bardic) {
    this->bardic = bardic;
}

void Player::SetConjuring(int conjuring) {
    this->conjuring = conjuring;
}

void Player::SetDruidic(int druidic) {
    this->druidic = druidic;
}

void Player::SetIllusion(int illusion) {
    this->illusion = illusion;
}

void Player::SetNecromancy(int necromancy) {
    this->necromancy = necromancy;
}

void Player::SetSorcery(int sorcery) {
    this->sorcery = sorcery;
}

void Player::SetShamanic(int shamanic) {
    this->shamanic = shamanic;
}

void Player::SetSummoning(int summoning) {
    this->summoning = summoning;
}

void Player::SetSpellcraft(int spellcraft) {
    this->spellcraft = spellcraft;
}

void Player::SetFocus(int focus) {
    this->focus = focus;
}

void Player::SetArmorsmithing(int armorsmithing) {
    this->armorsmithing = armorsmithing;
}

void Player::SetTailoring(int tailoring) {
    this->tailoring = tailoring;
}

void Player::SetFletching(int fletching) {
    this->fletching = fletching;
}

void Player::SetWeaponsmith(int weaponsmithing) {
    this->weaponsmithing = weaponsmithing;
}

void Player::SetAlchemy(int alchemy) {
    this->alchemy = alchemy;
}

void Player::SetLapidary(int lapidary) {
    this->lapidary = lapidary;
}

void Player::SetCalligraphy(int calligraphy) {
    this->calligraphy = calligraphy;
}

void Player::SetEnchanting(int enchanting) {
    this->enchanting = enchanting;
}

void Player::SetHerbalism(int herbalism) {
    this->herbalism = herbalism;
}

void Player::SetHunting(int hunting) {
    this->hunting = hunting;
}

void Player::SetMining(int mining) {
    this->mining = mining;
}

void Player::SetBargaining(int bargaining) {
    this->bargaining = bargaining;
}

void Player::SetCamping(int camping) {
    this->camping = camping;
}

void Player::SetFirstAid(int firstAid) {
    this->firstAid = firstAid;
}

void Player::SetLore(int lore) {
    this->lore = lore;
}

void Player::SetPickLocks(int pickLocks) {
    this->pickLocks = pickLocks;
}

void Player::SetScouting(int scouting) {
    this->scouting = scouting;
}

void Player::SetSearch(int search) {
    this->search = search;
}

void Player::SetStealth(int stealth) {
    this->stealth = stealth;
}

void Player::SetTraps(int traps) {
    this->traps = traps;
}

void Player::SetAeolandis(int aeolandis) {
    this->aeolandis = aeolandis;
}

void Player::SetHieroform(int hieroform) {
    this->hieroform = hieroform;
}

void Player::SetHighGundis(int highGundis) {
    this->highGundis = highGundis;
}

void Player::SetOldPraxic(int oldPraxic) {
    this->oldPraxic = oldPraxic;
}

void Player::SetPraxic(int praxic) {
    this->praxic = praxic;
}

void Player::SetRunic(int runic) {
    this->runic = runic;
}


//------------------------------------------------------------------------------------------------//
//-------------------                      Class Functions                     -------------------//
//------------------------------------------------------------------------------------------------//

std::string Player::ToString() {
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
