// File:     Player.h
// Created:  April 19, 2015
// Author:   Joseph DeVictoria
// Purpose:  Child class representing any player in Oldentide.
//        :  Inherits from "Character" class.

#ifndef OLDENTIDE_PLAYER_H_
#define OLDENTIDE_PLAYER_H_

#include "Character.h"
#include <string>

class Player : public Character {
    
    protected:

    std::string account;
    std::string profession;
    int id;
    int session; 
    float weight;
    int axe;
    int dagger;
    int unarmed;
    int hammer;
    int polearm;
    int spear;
    int staff;
    int sword;
    int archery;
    int crossbow;
    int sling;
    int thrown;
    int armor;
    int dualWeapon;
    int shield;
    int bardic;
    int conjuring;
    int druidic;
    int illusion;
    int necromancy;
    int sorcery;
    int shamanic;
    int spellcraft;
    int summoning;
    int focus;
    int armorsmithing;
    int tailoring;
    int fletching;
    int weaponsmithing;
    int alchemy;
    int lapidary;
    int calligraphy;
    int enchanting;
    int herbalism;
    int hunting;
    int mining;
    int bargaining;
    int camping;
    int firstAid;
    int lore;
    int pickLocks;
    int scouting;
    int search;
    int stealth;
    int traps;
    int aeolandis;
    int hieroform;
    int highGundis;
    int oldPraxic;
    int praxic;
    int runic;

    public:

    // Constructors.
    Player(std::string account, std::string profession, int id, int session, float weight, int axe,
           int dagger, int unarmed, int hammer, int polearm, int spear, int staff, int sword, 
           int archery, int crossbow, int sling, int thrown, int armor, int dualWeapon, int shield,
           int bardic, int conjuring, int druidic, int illusion, int necromancy, int sorcery, 
           int shamanic, int spellcraft, int summoning, int focus, int armorsmithing, 
           int tailoring, int fletching, int weaponsmithing, int alchemy, int lapidary, 
           int calligraphy, int enchanting, int herbalism, int hunting, int mining, int bargaining,
           int camping, int firstAid, int lore, int pickLocks, int scouting, int search, 
           int stealth, int traps, int aeolandis, int hieroform, int highGundis, int oldPraxic,
           int praxic, int runic, std::string name, std::string lastname, std::string race, 
           std::string gender, std::string face, std::string skin, std::string zone, int level, 
           int hp, int maxHp, int bp, int maxBp, int mp, int maxMp, int ep, int maxEp, int strength, 
           int constitution, int intelligence, int dexterity, float x, float y, float z, 
           float pitch, float yaw);
           
    Player(std::string fromString);

    //~Player();

    // Getter Functions.
    
    std::string GetAccount();
    std::string GetProfession();
    int GetId();
    int GetSession();
    float GetWeight();
    int GetAxe();
    int GetDagger();
    int GetUnarmed();
    int GetHammer();
    int GetPolearm();
    int GetSpear();
    int GetStaff();
    int GetSword();
    int GetArchery();
    int GetCrossbow();
    int GetSling();
    int GetThrown();
    int GetArmor();
    int GetDualWeapon();
    int GetShield();
    int GetBardic();
    int GetConjuring();
    int GetDruidic();
    int GetIllusion();
    int GetNecromancy();
    int GetSorcery();
    int GetShamanic();
    int GetSummoning();
    int GetSpellcraft();
    int GetFocus();
    int GetArmorsmithing();
    int GetTailoring();
    int GetFletching();
    int GetWeaponsmithing();
    int GetAlchemy();
    int GetLapidary();
    int GetCalligraphy();
    int GetEnchanting();
    int GetHerbalism();
    int GetHunting();
    int GetMining();
    int GetBargaining();
    int GetCamping();
    int GetFirstAid();
    int GetLore();
    int GetPickLocks();
    int GetScouting();
    int GetSearch();
    int GetStealth();
    int GetTraps();
    int GetAeolandis();
    int GetHieroform();
    int GetHighGundis();
    int GetOldPraxic();
    int GetPraxic();
    int GetRunic();

    // Setter Functions.
    
    void SetAccount(std::string account);
    void SetProfession(std::string profession);
    void SetId(int id);
    void SetSession(int session);
    void SetWeight(float weight);
    void SetAxe(int axe);
    void SetDagger(int dagger);
    void SetUnarmed(int unarmed);
    void SetHammer(int hammer);
    void SetPolearm(int polearm);
    void SetSpear(int spear);
    void SetStaff(int staff);
    void SetSword(int sword);
    void SetArchery(int archery);
    void SetCrossbow(int crossbow);
    void SetSling(int sling);
    void SetThrown(int thrown);
    void SetArmor(int armor);
    void SetDualWeapon(int dualWeapon);
    void SetShield(int shield);
    void SetBardic(int bardic);
    void SetConjuring(int conjuring);
    void SetDruidic(int druidic);
    void SetIllusion(int illusion);
    void SetNecromancy(int necromancy);
    void SetSorcery(int sorcery);
    void SetShamanic(int shamanic);
    void SetSummoning(int summoning);
    void SetSpellcraft(int spellcraft);
    void SetFocus(int focus);
    void SetArmorsmithing(int armorsmithing);
    void SetTailoring(int tailoring);
    void SetFletching(int fletching);
    void SetWeaponsmith(int weaponsmithing);
    void SetAlchemy(int alchemy);
    void SetLapidary(int lapidary);
    void SetCalligraphy(int calligraphy);
    void SetEnchanting(int enchanting);
    void SetHerbalism(int herbalism);
    void SetHunting(int hunting);
    void SetMining(int mining);
    void SetBargaining(int bargaining);
    void SetCamping(int camping);
    void SetFirstAid(int firstAid);
    void SetLore(int lore);
    void SetPickLocks(int pickLocks);
    void SetScouting(int scouting);
    void SetSearch(int search);
    void SetStealth(int stealth);
    void SetTraps(int traps);
    void SetAeolandis(int aeolandis);
    void SetHieroform(int hieroform);
    void SetHighGundis(int highGundis);
    void SetOldPraxic(int oldPraxic);
    void SetPraxic(int praxic);
    void SetRunic(int runic);

    // Class Functions.
    std::string ToString();
};

#endif //OLDENTIDE_PLAYER_H_
