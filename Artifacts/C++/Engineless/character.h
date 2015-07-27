/* header file for Character class.  This is the basic character in the game. 2/9/13 */

#ifndef character_h
#define character_h

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <cctype>
using namespace std;

class character
{
    private:
        string account;
        string name;
        string race;
        string gender;
        string profession;
        int strength;
        int constitution;
        int intelligence;
        int dexterity;
        int level;
        int hppl;
        int mppl;
        int currentHP;
        int maxHP;
        int currentBP;
        int maxBP;
        int currentMP;
        int maxMP;
        int currentEP;
        int maxEP;
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
        int dual_weapon;
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
        int first_aid;
        int lore;
        int pick_locks;
        int scouting;
        int search;
        int stealth;
        int traps;
        int aeolandis;
        int heiroform;
        int high_gundis;
        int old_praxic;
        int praxic;
        int runic;

    public:
        character(string a, string n, string r, string g, string p);
        ~character();
        void calcMaxCond();
        void calcMaxHP();
        void calcMaxBP();
        void calcMaxMP();
        void calcMaxEP();
        pair<int, int> retHP();
        pair<int, int> retBP();
        pair<int, int> retMP();
        pair<int, int> retEP();
        void calcStartAttributes();
        void calcProfAttributes();
        void calcProfSkills();
        string pickSchool();
        string pickCraft();
        void setSchool(string, int);
        void setCraft(string, int);
        int* retCond();
        string retName();
        string retRace();
        string retGender();
        string retProf();
        int retStr();
        int retCon();
        int retInt();
        int retDex();
        int retLevel();
};

character* goLogin();

void createCharacter(string a);

int calcStatInt();

#endif
