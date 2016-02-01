// File:     Character.h
// Created:  April 19, 2015
// Author:   Joseph DeVictoria
// Purpose:  Child class representing any living object in Oldentide.
//        :  Inherits from "Object" class.

#ifndef OLDENTIDE_CHARACTER_H_
#define OLDENTIDE_CHARACTER_H_

#include "Object.h"
#include <string>

#pragma once

using namespace std;

class Character : public Object {

    protected:

    string name;
    string race;
    string gender;
    string profession;
    int level;
    int hp;
    int bp;
    int mp;
    int ep;
    int strength;
    int constitution;
    int intelligence;
    int dexterity;
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

    Character(string name, string race, string gender, string profession, int weight, int x, int y, int z);
    Character(string name, string race, string gender, string profession);
    //~Character();

    // Getter Functions
    string getName();
    string getRace();
    string getGender();
    string getProfession();
    int getLevel();
    int getHP();
    int getBP();
    int getMP();
    int getEP();
    int getStrength();
    int getConstitution();
    int getIntelligence();
    int getDexterity();
    int getAxe();
    int getDagger();
    int getUnarmed();
    int getHammer();
    int getPolearm();
    int getSpear();
    int getStaff();
    int getSword();
    int getArchery();
    int getCrossbow();
    int getSling();
    int getThrown();
    int getArmor();
    int getDualWeapon();
    int getShield();
    int getBardic();
    int getConjuring();
    int getDruidic();
    int getIllusion();
    int getNecromancy();
    int getSorcery();
    int getShamanic();
    int getSummoning();
    int getSpellcraft();
    int getFocus();
    int getArmorsmithing();
    int getTailoring();
    int getFletching();
    int getWeaponsmith();
    int getAlchemy();
    int getLapidary();
    int getCalligraphy();
    int getEnchanting();
    int getHerbalism();
    int getHunting();
    int getMining();
    int getBargaining();
    int getCamping();
    int getFirstAid();
    int getLore();
    int getPickLocks();
    int getScouting();
    int getSearch();
    int getStealth();
    int getTraps();
    int getAeolandis();
    int getHieroform();
    int getHighGundis();
    int getOldPraxic();
    int getPraxic();
    int getRunic();

    // Setter Functions
    void setName(string profession);
    void setRace(string profession);
    void setGender(string profession);
    void setProfession(string profession);
    void setLevel(int level);
    void setHP(int hp);
    void setBP(int bp);
    void setMP(int mp);
    void setEP(int ep);
    void setStrength(int strength);
    void setConstitution(int constitution);
    void setIntelligence(int intelligence);
    void setDexterity(int dexterity);
    void setAxe(int axe);
    void setDagger(int dagger);
    void setUnarmed(int unarmed);
    void setHammer(int hammer);
    void setPolearm(int polearm);
    void setSpear(int spear);
    void setStaff(int staff);
    void setSword(int sword);
    void setArchery(int archery);
    void setCrossbow(int crossbow);
    void setSling(int sling);
    void setThrown(int thrown);
    void setArmor(int armor);
    void setDualWeapon(int dualWeapon);
    void setShield(int shield);
    void setBardic(int bardic);
    void setConjuring(int conjuring);
    void setDruidic(int druidic);
    void setIllusion(int illusion);
    void setNecromancy(int necromancy);
    void setSorcery(int sorcery);
    void setShamanic(int shamanic);
    void setSummoning(int summoning);
    void setSpellcraft(int spellcraft);
    void setFocus(int focus);
    void setArmorsmithing(int armorsmithing);
    void setTailoring(int tailoring);
    void setFletching(int fletching);
    void setWeaponsmith(int weaponsmithing);
    void setAlchemy(int alchemy);
    void setLapidary(int lapidary);
    void setCalligraphy(int calligraphy);
    void setEnchanting(int enchanting);
    void setHerbalism(int herbalism);
    void setHunting(int hunting);
    void setMining(int mining);
    void setBargaining(int bargaining);
    void setCamping(int camping);
    void setFirstAid(int firstAid);
    void setLore(int lore);
    void setPickLocks(int pickLocks);
    void setScouting(int scouting);
    void setSearch(int search);
    void setStealth(int stealth);
    void setTraps(int traps);
    void setAeolandis(int aeolandis);
    void setHieroform(int hieroform);
    void setHighGundis(int highGundis);
    void setOldPraxic(int oldPraxic);
    void setPraxic(int praxic);
    void setRunic(int runic);

    // Class Functions

};

#endif
