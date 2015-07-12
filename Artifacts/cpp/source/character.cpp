/* Basically this is the character class with all of its functions. 2/9/13 */

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <cctype>
#include "character.h"
#include "oldentide.h"
#define SORRYCRAFT "Sorry that is not a valid option, please choose a crafting school from the above list:"
#define SORRYSPELL "Sorry that is not a valid option, please choose a spell school from the above list:"
#define ARTSKILLS "As an Artificer, you will choose one primary spell school and one primary crafting skill. "
#define CHOOSENAME "Please choose a name that is at least three letters long, but no longer than twelve"
#define ANOTHERRACE "Sorry that is not a valid option, please choose a race from the above list:"
#define PROFLIST "Please choose your profession from the list above: "
#define CVPROF "Sorry that is not a valid option, please choose a profession from the above list:"
using namespace std;

character::character(string a, string n, string r, string g, string p){
    account = a;
    name = n;
    race = r;
    gender = g;
    profession = p;
    strength = 40;
    constitution = 40;
    intelligence = 40;
    dexterity = 40;
    level = 1;
    axe = 0;
    dagger = 0;
    unarmed = 0;
    hammer = 0;
    polearm = 0;
    spear = 0;
    staff = 0;
    sword = 0;
    archery = 0;
    crossbow = 0;
    sling = 0;
    thrown = 0;
    armor = 0;
    dual_weapon = 0;
    shield = 0;
    bardic = 0;
    conjuring = 0;
    druidic = 0;
    illusion = 0;
    necromancy = 0;
    sorcery = 0;
    shamanic = 0;
    spellcraft = 0;
    summoning = 0;
    focus = 0;
    armorsmithing = 0;
    tailoring = 0;
    fletching = 0;
    weaponsmithing = 0;
    alchemy = 0;
    lapidary = 0;
    calligraphy = 0;
    enchanting = 0;
    herbalism = 0;
    hunting = 0;
    mining = 0;
    bargaining = 0;
    camping = 0;
    first_aid = 0;
    lore = 0;
    pick_locks = 0;
    scouting = 0;
    search = 0;
    stealth = 0;
    traps = 0;
    aeolandis = 0;
    heiroform = 0;
    high_gundis = 0;
    old_praxic = 0;
    praxic = 0;
    runic = 0;
    this->calcStartAttributes();
    this->calcProfAttributes();
}

int calcStatInt(int a, int b, int c){
    double ad = a;
    double bd = b;
    double cd = c;
    double dd = ad*(bd/cd);
    int ret = dd;
    return ret;
}

void character::calcMaxCond(){
    maxHP = (constitution * 10);
    maxBP = (constitution * 6);
    maxMP = (intelligence * 10);
    maxEP = (intelligence * 6);
}

void character::calcMaxHP(){
    maxHP = (constitution * 10);
}

void character::calcMaxBP(){
    maxBP = (constitution * 6);
}

void character::calcMaxMP(){
    maxMP = (intelligence * 10);
}

void character::calcMaxEP(){
    maxEP = (intelligence * 6);
}

pair<int, int> character::retHP(){
    pair<int, int> hpPair;
    hpPair.first = currentHP;
    hpPair.second = maxHP;
    return hpPair;
}

pair<int, int> character::retBP(){
    pair<int, int> bpPair;
    bpPair.first = currentBP;
    bpPair.second = maxBP;
    return bpPair;
}

pair<int, int> character::retMP(){
    pair<int, int> mpPair;
    mpPair.first = currentMP;
    mpPair.second = maxMP;
    return mpPair;
}

pair<int, int> character::retEP(){
    pair<int, int> epPair;
    epPair.first = currentEP;
    epPair.second = maxEP;
    return epPair;
}

void character::calcStartAttributes(){
    if (race == "Human"){}
    if (race == "Dwarf"){
        strength = calcStatInt(strength, 9, 8); 
        constitution = calcStatInt(constitution, 11, 8); 
        intelligence = calcStatInt(intelligence, 7, 8); 
        dexterity = calcStatInt(dexterity, 5, 8);
    }
    if (race == "Elf"){
        strength = calcStatInt(strength, 6, 8); 
        constitution = calcStatInt(constitution, 5, 8); 
        intelligence = calcStatInt(intelligence, 9, 8); 
        dexterity = calcStatInt(dexterity, 11, 8);
    }
    if (race == "Orc"){
        strength = calcStatInt(strength, 9, 8); 
        intelligence = calcStatInt(constitution, 6, 8);
        dexterity = calcStatInt(dexterity, 9, 8);
    }
    if (race == "Gnome"){
        strength = calcStatInt(strength, 6, 8); 
        constitution = calcStatInt(constitution, 6, 8); 
        intelligence = calcStatInt(intelligence, 10, 8); 
        dexterity = calcStatInt(dexterity, 10, 8);
    }
    if (race == "Ogre"){
        strength = calcStatInt(strength, 12, 8); 
        constitution = calcStatInt(constitution, 9, 8); 
        intelligence = calcStatInt(intelligence, 5, 8); 
        dexterity = calcStatInt(dexterity, 6, 8);
    }
    if (race == "Thresh"){
        strength = calcStatInt(strength, 5, 8); 
        constitution = calcStatInt(constitution, 7, 8); 
        intelligence = calcStatInt(intelligence, 12, 8);
    }
}

void character::calcProfAttributes(){
    if (profession == "Adventurer"){
        hppl = 5; 
        mppl = 5;
    }
    if (profession == "Alchemist"){
        hppl = 5; 
        mppl = 5;
    }
    if (profession == "Archer"){
        intelligence = intelligence-5; 
        dexterity = dexterity+5;
        hppl = 6; 
        mppl = 4;
    }
    if (profession == "Armorsmith"){
        strength = strength+5; 
        dexterity = dexterity-5;
        hppl = 5; 
        mppl = 5;
    }
    if (profession == "Armsman"){
        strength = strength+5; 
        intelligence = intelligence-5;
        hppl = 7; 
        mppl = 3;
    }
    if (profession == "Artificer"){
        strength = strength-10; 
        intelligence = intelligence+10;
        hppl = 3; 
        mppl = 7;
    }
    if (profession == "Assassin"){
        intelligence = intelligence-5; 
        dexterity = dexterity+5;
        hppl = 7; 
        mppl = 3;
    }
    if (profession == "Axeman"){
        strength = strength+5; 
        intelligence = intelligence-5;
        hppl = 7; 
        mppl = 3;
    }
    if (profession == "Bandit"){
        hppl = 6; 
        mppl = 4;
    }
    if (profession == "Barbarian"){
        strength = strength+5; 
        intelligence = intelligence-10; 
        dexterity = dexterity-5; 
        constitution = constitution+10;
        hppl = 6; 
        mppl = 4;
    }
    if (profession == "Barber"){
        hppl = 5; 
        mppl = 5;
    }
    if (profession == "Bard"){
        strength = strength-5; 
        intelligence = intelligence+5; 
        dexterity = dexterity+5; 
        constitution = constitution-5;
        hppl = 3; 
        mppl = 7;
    }
    if (profession == "Berserker"){
        strength = strength+10; 
        intelligence = intelligence-10; 
        dexterity = dexterity-5; 
        constitution = constitution+5;
        hppl = 8; 
        mppl = 2;
    }
    if (profession == "Bombadier"){
        intelligence = intelligence-5; 
        dexterity = dexterity+5;
        hppl = 7; 
        mppl = 3;
    }
    if (profession == "Blacksmith"){
        strength = strength+5; 
        dexterity = dexterity-5;
        hppl = 6; 
        mppl = 4;
    }
    if (profession == "Bowyer"){
        strength = strength-5; 
        dexterity = dexterity+5;
        hppl = 5; 
        mppl = 5;
    }
    if (profession == "Brawler"){
        strength = strength+5; 
        intelligence = intelligence-10; 
        dexterity = dexterity-5; 
        constitution = constitution+10;
        hppl = 8; 
        mppl = 2;
    }
    if (profession == "Brewer"){
        hppl = 5; 
        mppl = 5;
    }
    if (profession == "Cabalist"){
        strength = strength-5; 
        intelligence = intelligence+10;
        constitution = constitution-5;
        hppl = 3; 
        mppl = 7;
    }
    if (profession == "Calligrapher"){
        hppl = 3; 
        mppl = 7;
    }
    if (profession == "Cavalier"){
        strength = strength+5; 
        intelligence = intelligence-5;
        hppl = 7; 
        mppl = 3;
    }
    if (profession == "Cleric"){
        intelligence = intelligence+5; 
        dexterity = dexterity-5;
        hppl = 4; 
        mppl = 6;
    }
    if (profession == "Commoner"){
        hppl = 5; 
        mppl = 5;
    }
    if (profession == "Conjurer"){
        intelligence = intelligence+5; 
        dexterity = dexterity-5;
        hppl = 4; 
        mppl = 6;
    }
    if (profession == "Crafter"){
        strength = strength-5; 
        intelligence = intelligence+5;
        hppl = 5; 
        mppl = 5;
    }
    if (profession == "Crossbowman"){
        intelligence = intelligence-5; 
        dexterity = dexterity+5;
        hppl = 6; 
        mppl = 4;
    }
    if (profession == "Dark Paladin"){
        strength = strength+5; 
        dexterity = dexterity-5;
        hppl = 6; 
        mppl = 4;
    }
    if (profession == "Demiurge"){
        strength = strength+5; 
        dexterity = dexterity-5;
        hppl = 6; 
        mppl = 4;
    }
    if (profession == "Diabolist"){
        strength = strength+5; 
        dexterity = dexterity-5;
        hppl = 6; 
        mppl = 4;
    }
    if (profession == "Druid"){
        strength = strength-5; 
        intelligence = intelligence+5;
        hppl = 4; 
        mppl = 6;
    }
    if (profession == "Duelist"){
        intelligence = intelligence-5; 
        dexterity = dexterity+5;
        hppl = 6; 
        mppl = 4;
    }
    if (profession == "Empyreal"){
        strength = strength-10; 
        intelligence = intelligence+15;
        constitution = constitution-5;
        hppl = 2; 
        mppl = 8;
    }
    if (profession == "Enchanter"){
        strength = strength-10; 
        intelligence = intelligence+10;
        hppl = 3; 
        mppl = 7;
    }
    if (profession == "Engineer"){
        hppl = 5; 
        mppl = 5;
    }
    if (profession == "Etherialist"){
        strength = strength-10; 
        intelligence = intelligence+15;
        constitution = constitution-5;
        hppl = 2; 
        mppl = 8;
    }
    if (profession == "Explorer"){
        hppl = 5; 
        mppl = 5;
    }
    if (profession == "Fletcher"){
        strength = strength-5; 
        dexterity = dexterity+5;
        hppl = 5; 
        mppl = 5;
    }
    if (profession == "Friar"){
        hppl = 4; 
        mppl = 6;
    }
    if (profession == "Geomancer"){
        strength = strength-10; 
        intelligence = intelligence+10;
        dexterity = dexterity-5; 
        constitution = constitution+5;
        hppl = 2; 
        mppl = 8;
    }
    if (profession == "Gladiator"){
        strength = strength+5; 
        intelligence = intelligence-10;
        dexterity = dexterity+5;
        hppl = 8; 
        mppl = 2;
    }
    if (profession == "Healer"){
        strength = strength-5; 
        intelligence = intelligence+5;
        hppl = 3; 
        mppl = 7;
    }
    if (profession == "Herbalist"){
        strength = strength-5; 
        intelligence = intelligence+5;
        hppl = 5; 
        mppl = 5;
    }
    if (profession == "Highlander"){
        strength = strength+5; 
        intelligence = intelligence-10;
        dexterity = dexterity-5; 
        constitution = constitution+10;
        hppl = 7; 
        mppl = 3;
    }
    if (profession == "Hunter"){
        intelligence = intelligence-5; 
        dexterity = dexterity+5;
        hppl = 7; 
        mppl = 3;
    }
    if (profession == "Huntress"){
        intelligence = intelligence-5; 
        dexterity = dexterity+5;
        hppl = 7; 
        mppl = 3;
    }
    if (profession == "Huntsman"){
        hppl = 6; 
        mppl = 4;
    }
    if (profession == "Illusionist"){
        strength = strength-5; 
        intelligence = intelligence+5;
        hppl = 3; 
        mppl = 7;
    }
    if (profession == "Infernalist"){
        strength = strength-10; 
        intelligence = intelligence+15;
        constitution = constitution-5;
        hppl = 2; 
        mppl = 8;
    }
    if (profession == "Jeweler"){
        hppl = 4; 
        mppl = 6;
    }
    if (profession == "Linguist"){
        strength = strength-10; 
        intelligence = intelligence+10;
        hppl = 5; 
        mppl = 5;
    }
    if (profession == "Lumberjack"){
        strength = strength+10; 
        intelligence = intelligence-5;
        dexterity = dexterity-5;
        hppl = 7; 
        mppl = 3;
    }
    if (profession == "Mage"){
        strength = strength-5; 
        intelligence = intelligence+5;
        hppl = 3; 
        mppl = 7;
    }
    if (profession == "Magician"){
        strength = strength-5; 
        intelligence = intelligence+5;
        dexterity = dexterity+5; 
        constitution = constitution-5;
        hppl = 3; 
        mppl = 7;
    }
    if (profession == "Marksman"){
        strength = strength-5; 
        intelligence = intelligence-5;
        dexterity = dexterity+10;
        hppl = 7; 
        mppl = 3;
    }
    if (profession == "Mercenary"){
        strength = strength+5; 
        intelligence = intelligence-5;
        hppl = 7; 
        mppl = 3;
    }
    if (profession == "Merchant"){
        strength = strength-5; 
        intelligence = intelligence+5;
        hppl = 5; 
        mppl = 5;
    }
    if (profession == "Miner"){
        strength = strength+5; 
        intelligence = intelligence-5;
        hppl = 6; 
        mppl = 4;
    }
    if (profession == "Minstrel"){
        strength = strength-5; 
        intelligence = intelligence+5;
        hppl = 5; 
        mppl = 5;
    }
    if (profession == "Monk"){
        intelligence = intelligence-5; 
        dexterity = dexterity+5;
        hppl = 6; 
        mppl = 4;
    }
    if (profession == "Muse"){
        strength = strength-5; 
        intelligence = intelligence+10;
        constitution = constitution-5;
        hppl = 4; 
        mppl = 6;
    }
    if (profession == "Mystic"){
        strength = strength-10; 
        intelligence = intelligence+10;
        hppl = 3; 
        mppl = 7;
    }
    if (profession == "Necromancer"){
        intelligence = intelligence+5; 
        constitution = constitution-5;
        hppl = 2; 
        mppl = 8;
    }
    if (profession == "Outlaw"){
        intelligence = intelligence-5; 
        dexterity = dexterity+5;
        hppl = 7; 
        mppl = 3;
    }
    if (profession == "Paladin"){
        strength = strength+5; 
        dexterity = dexterity-5;
        hppl = 6; 
        mppl = 4;
    }
    if (profession == "Peasant"){
        hppl = 5; 
        mppl = 5;
    }
    if (profession == "Performer"){
        dexterity = dexterity+5; 
        constitution = constitution-5;
        hppl = 6; 
        mppl = 4;
    }
    if (profession == "Philisopher"){
        strength = strength-10; 
        intelligence = intelligence+10;
        hppl = 4; 
        mppl = 6;
    }
    if (profession == "Pikeman"){
        strength = strength+5; 
        intelligence = intelligence-5;
        hppl = 7; 
        mppl = 3;
    }
    if (profession == "Poet"){
        strength = strength-10; 
        intelligence = intelligence+10;
        hppl = 4; 
        mppl = 6;
    }
    if (profession == "Prestidigitator"){
        strength = strength-5; 
        intelligence = intelligence+5;
        dexterity = dexterity+5; 
        constitution = constitution-5;
        hppl = 4; 
        mppl = 6;
    }
    if (profession == "Pugilist"){
        intelligence = intelligence-5; 
        dexterity = dexterity+5;
        hppl = 7; 
        mppl = 3;
    }
    if (profession == "Ranger"){
        hppl = 6; 
        mppl = 4;
    }
    if (profession == "Rogue"){
        strength = strength-5; 
        dexterity = dexterity+10;
        constitution = constitution-5;
        hppl = 6; 
        mppl = 4;
    }
    if (profession == "Sage"){
        strength = strength-10; 
        intelligence = intelligence+10;
        hppl = 4; 
        mppl = 6;
    }
    if (profession == "Scholar"){
        strength = strength-10; 
        intelligence = intelligence+15;
        constitution = constitution-5;
        hppl = 2; 
        mppl = 8;
    }
    if (profession == "Scoundrel"){
        strength = strength-5; 
        dexterity = dexterity+10;
        constitution = constitution-5;
        hppl = 5; 
        mppl = 5;
    }
    if (profession == "Scribe"){
        strength = strength-5; 
        intelligence = intelligence+10;
        constitution = constitution-5;
        hppl = 3; 
        mppl = 7;
    }
    if (profession == "Seer"){
        strength = strength-5; 
        intelligence = intelligence+10;
        constitution = constitution-5;
        hppl = 3; 
        mppl = 7;
    }
    if (profession == "Shaman"){
        strength = strength-5; 
        intelligence = intelligence+5;
        hppl = 4; 
        mppl = 6;
    }
    if (profession == "Skald"){
        strength = strength+5; 
        dexterity = dexterity-5;
        hppl = 6; 
        mppl = 4;
    }
    if (profession == "Slinger"){
        intelligence = intelligence-5; 
        dexterity = dexterity+5;
        hppl = 6; 
        mppl = 4;
    }
    if (profession == "Soldier"){
        strength = strength+5; 
        intelligence = intelligence-5;
        hppl = 8; 
        mppl = 2;
    }
    if (profession == "Sorcerer"){
        strength = strength-5; 
        intelligence = intelligence+5;
        hppl = 2; 
        mppl = 8;
    }
    if (profession == "Squire"){
        strength = strength+5; 
        intelligence = intelligence-5;
        hppl = 7; 
        mppl = 3;
    }
    if (profession == "Summoner"){
        intelligence = intelligence+5; 
        constitution = constitution-5;
        hppl = 3; 
        mppl = 7;
    }
    if (profession == "Swashbuckler"){
        intelligence = intelligence-5; 
        dexterity = dexterity+5;
        hppl = 6; 
        mppl = 4;
    }
    if (profession == "Sycophant"){
        strength = strength-5; 
        intelligence = intelligence+10;
        constitution = constitution-5;
        hppl = 4; 
        mppl = 6;
    }
    if (profession == "Tailor"){
        hppl = 4; 
        mppl = 6;
    }
    if (profession == "Templar"){
        strength = strength+5; 
        dexterity = dexterity-5;
        hppl = 6; 
        mppl = 4;
    }
    if (profession == "Thaumaturgist"){
        strength = strength-5; 
        intelligence = intelligence+10;
        constitution = constitution-5;
        hppl = 3; 
        mppl = 7;
    }
    if (profession == "Theurge"){
        strength = strength+5; 
        dexterity = dexterity-5;
        hppl = 6; 
        mppl = 4;
    }
    if (profession == "Thief"){
        strength = strength-5; 
        dexterity = dexterity+10;
        constitution = constitution-5;
        hppl = 6; 
        mppl = 4;
    }
    if (profession == "Tinker"){
        strength = strength-5; 
        intelligence = intelligence+5;
        dexterity = dexterity=5; 
        constitution = constitution-5;
        hppl = 4; 
        mppl = 6;
    }
    if (profession == "Troubador"){
        strength = strength-5; 
        intelligence = intelligence+5;
        hppl = 5; 
        mppl = 5;
    }
    if (profession == "Viking"){
        strength = strength+10; 
        intelligence = intelligence-10;
        hppl = 8; 
        mppl = 2;
    }
    if (profession == "Vinter"){
        hppl = 5; 
        mppl = 5;
    }
    if (profession == "Warden"){
        hppl = 7; 
        mppl = 3;
    }
    if (profession == "Warrior"){
        strength = strength+5; 
        intelligence = intelligence-10;
        constitution = constitution+5;
        hppl = 8; 
        mppl = 2;
    }
    if (profession == "Weaponsmith"){
        strength = strength+5; 
        dexterity = dexterity-5;
        hppl = 5; 
        mppl = 5;
    }
    if (profession == "Wizard"){
        strength = strength-5; 
        intelligence = intelligence+10;
        constitution = constitution-5;
        hppl = 3; 
        mppl = 7;
    }
    if (profession == "Woodsman"){
        hppl = 7; 
        mppl = 3;
    }
    if (profession == "Zealot"){
        hppl = 4; 
        mppl = 6;
    }
}


void character::calcProfSkills(){
    //This function will take in data for all of the starting skills
    if (profession == "Adventurer"){
    
    }
    if (profession == "Alchemist"){
        alchemy = 30;
        herbalism = 10;
    }
    if (profession == "Archer"){
        archery = 30;
        fletching = 10;
    }
    if (profession == "Armorsmith"){
        armorsmithing = 30;
        hammer = 5;
        mining = 5;
    }
    if (profession == "Armsman"){
        polearm = 30;
        armor = 20;
    }
    if (profession == "Artificer"){
        spellcraft = 20;
        lore =15;
        cout << ARTSKILLS << endl;
        string school1 = pickSchool();
        setSchool(school1, 10);
        string craft1 = pickCraft();
        setCraft(craft1, 10);    
    }
    if (profession == "Assassin"){
    
    }
    if (profession == "Axeman"){
    
    }
    if (profession == "Bandit"){
    
    }
    if (profession == "Barbarian"){
    
    }
    if (profession == "Barber"){
    
    }
    if (profession == "Bard"){
    
    }
    if (profession == "Berserker"){
    
    }
    if (profession == "Bombadier"){
    
    }
    if (profession == "Blacksmith"){
    
    }
    if (profession == "Bowyer"){
    
    }
    if (profession == "Brawler"){
    
    }
    if (profession == "Brewer"){
    
    }
    if (profession == "Cabalist"){
    
    }
    if (profession == "Calligrapher"){
    
    }
    if (profession == "Cavalier"){
    
    }
    if (profession == "Cleric"){
    
    }
    if (profession == "Commoner"){
      
    }
    if (profession == "Conjurer"){
      
    }
    if (profession == "Crafter"){
    
    }
    if (profession == "Crossbowman"){
      
    }
    if (profession == "Dark Paladin"){
    
    }
    if (profession == "Demiurge"){
    
    }
    if (profession == "Diabolist"){
    
    }
    if (profession == "Druid"){
    
    }
    if (profession == "Duelist"){
    
    }
    if (profession == "Empyreal"){
    
    }
    if (profession == "Enchanter"){
    
    }
    if (profession == "Engineer"){
    
    }
    if (profession == "Etherialist"){
    
    }
    if (profession == "Explorer"){
    
    }
    if (profession == "Fletcher"){
    
    }
    if (profession == "Friar"){
    
    }
    if (profession == "Geomancer"){
    
    }
    if (profession == "Gladiator"){
    
    } 
    if (profession == "Healer"){
    
    }
    if (profession == "Herbalist"){
    
    }
    if (profession == "Highlander"){
      
    }
    if (profession == "Hunter"){
    
    }
    if (profession == "Huntress"){
      
    }
    if (profession == "Huntsman"){
    
    }
    if (profession == "Illusionist"){
    
    }
    if (profession == "Infernalist"){
    
    }
    if (profession == "Jeweler"){
    
    }
    if (profession == "Linguist"){
    
    }
    if (profession == "Lumberjack"){
    
    }
    if (profession == "Mage"){
    
    }
    if (profession == "Magician"){
    
    }
    if (profession == "Marksman"){
    
    }
    if (profession == "Mercenary"){
    
    }
    if (profession == "Merchant"){
      
    }
    if (profession == "Miner"){
    
    }
    if (profession == "Minstrel"){
    
    }
    if (profession == "Monk"){
      
    }
    if (profession == "Muse"){
    
    }
    if (profession == "Mystic"){
    
    }
    if (profession == "Necromancer"){
    
    }
    if (profession == "Outlaw"){
    
    }
    if (profession == "Paladin"){
    
    }
    if (profession == "Peasant"){
    
    }
    if (profession == "Performer"){
    
    }
    if (profession == "Philisopher"){
    
    }
    if (profession == "Pikeman"){

    }
    if (profession == "Poet"){

    }
    if (profession == "Prestidigitator"){

    }
    if (profession == "Pugilist"){

    }
    if (profession == "Ranger"){

    }
    if (profession == "Rogue"){

    }
    if (profession == "Sage"){

    }
    if (profession == "Scholar"){

    }
    if (profession == "Scoundrel"){

    }
    if (profession == "Scribe"){

    }
    if (profession == "Seer"){

    }
    if (profession == "Shaman"){

    }
    if (profession == "Skald"){

    }
    if (profession == "Slinger"){

    }
    if (profession == "Soldier"){

    }
    if (profession == "Sorcerer"){

    }
    if (profession == "Squire"){

    }
    if (profession == "Summoner"){

    }
    if (profession == "Swashbuckler"){

    }
    if (profession == "Sycophant"){

    }
    if (profession == "Tailor"){

    }
    if (profession == "Templar"){

    }
    if (profession == "Thaumaturgist"){

    }
    if (profession == "Theurge"){

    }
    if (profession == "Thief"){

    }
    if (profession == "Tinker"){

    }
    if (profession == "Troubador"){

    }
    if (profession == "Viking"){

    }
    if (profession == "Vinter"){

    }
    if (profession == "Warden"){

    }
    if (profession == "Warrior"){

    }
    if (profession == "Weaponsmith"){

    }
    if (profession == "Wizard"){

    }
    if (profession == "Woodsman"){

    }
    if (profession == "Zealot"){

    }
}


string character::pickSchool(){
    string line;
    ifstream schools;
    set<string> schoolSt;
    cout << "Please choose a spell school: " << endl << endl;
    line = "empty";
    schools.open("text/spellschools.txt");
    while (line != ""){
        getline (schools, line);
        cout << line << endl;
        schoolSt.insert(line);
    }
    schools.close();
    
    cin >> line;
    line[0] = toupper(line[0]);
    while (schoolSt.find(line) == schoolSt.end()){
        cout << SORRYSPELL << endl;
        cin >> line;
        line[0] = toupper(line[0]);
    }
    
    return line;
}

void character::setSchool(string sc, int power){
    if (sc == "Bardic") {bardic = power;}
    if (sc == "Conjuring") {conjuring = power;}
    if (sc == "Druidic") {druidic = power;}
    if (sc == "Illusion") {illusion = power;}
    if (sc == "Necromancy") {necromancy = power;}
    if (sc == "Sorcery") {sorcery = power;}
    if (sc == "Shamanic") {shamanic = power;}
}

string character::pickCraft(){
    string line;
    ifstream crafts;
    set<string> craftSt;
    cout << "Please choose a crafting school: " << endl << endl;
    line = "empty";
    crafts.open("text/craftschools.txt");
    while (line != ""){
        getline (crafts, line);
        cout << line << endl;
        craftSt.insert(line);
    }
    crafts.close();
    
    cin >> line;
    line[0] = toupper(line[0]);
    while (craftSt.find(line) == craftSt.end()){
        cout << SORRYCRAFT << endl;
        cin >> line;
        line[0] = toupper(line[0]);
    }
    
    return line;
}

void character::setCraft(string cc, int power){
    if (cc == "Armorsmithing") {armorsmithing = power;}
    if (cc == "Tailoring") {tailoring = power;}
    if (cc == "Fletching") {fletching = power;}
    if (cc == "Weaponsmithing") {weaponsmithing = power;}
    if (cc == "Alchemy") {alchemy = power;}
    if (cc == "Lapidary") {lapidary = power;}
    if (cc == "Calligraphy") {calligraphy = power;}
    if (cc == "Enchanting") {enchanting = power;}
}

string character::retName(){
    return name;
}

string character::retRace(){
    return race;
}

string character::retGender(){
    return gender;
}

string character::retProf(){
    return profession;
}

int character::retStr(){
    return strength;
}

int character::retCon(){
    return constitution;
}

int character::retInt(){
    return intelligence;
}

int character::retDex(){
    return dexterity;
}

int character::retLevel(){
    return level;
}

character::~character(){
    int none;
}

character* goLogin(){
    string inName, inPass;
    cout << "Please enter your Account name: " << endl;
    cin >> inName;
}

void createCharacter(string acct){
  
    //Variables
    string name, account, race, gender, profession;
    string line = "empty";
    set<string> racesSt, genderSt, professionsSt;
    ifstream races, professions;
    account = acct;
    
    cout << "Please name your character: " << endl;
    cin >> name;
    
    while (name.size() < 3 || name.size() > 12){
        cout << CHOOSENAME << endl;
        cin >> name;
    }
    
    cout << "Your name is: " << name << endl << endl;

    genderSt.insert("Male");
    genderSt.insert("Female");
    cout << "What gender are you? (Male/Female)" << endl;
    cin >> gender;
    gender[0] = toupper(gender[0]);

    while (genderSt.find(gender) == genderSt.end()){
        cout << "Please choose either 'Male' or 'Female'" << endl;
        cin >> gender;
        gender[0] = toupper(gender[0]);
    }
    cout << "You are a: " << gender << endl << endl;
    
    line = "empty";
    races.open("text/races.txt");
    while (line != ""){
        getline (races, line);
        cout << line << endl;
        racesSt.insert(line);
    }
    races.close();
    
    cout << "Please choose your race: " << endl;
    cin >> race;
    race[0] = toupper(race[0]);
    while (racesSt.find(race) == racesSt.end()){
        cout << ANOTHERRACE << endl;
        cin >> race;
        race[0] = toupper(race[0]);
    }
    cout << name << ", You have chosen to be ";
    if(race == "Ogre" || race == "Elf" || race == "Orc"){
        cout << "an " << race << endl << endl;
    }
    else{
        cout << "a " << race << endl << endl;
    }
    
    line = "empty";
    professions.open("text/professions.txt");
    while (line != ""){
        for (int i = 0; i<4; i++){
	        getline (professions, line);
	        professionsSt.insert(line);
	        int letters = line.size();
            cout << line;
	        for (int q = 0; q < (16 - letters); q++){
	            cout << " ";
	        }
        }
        cout << endl;
    }
    professions.close();
    
    cout << endl << PROFLIST << endl;
    cin >> profession;
    profession[0] = toupper(profession[0]);
    while (professionsSt.find(profession) == professionsSt.end()){
        cout << CVPROF << endl;
        cin >> profession;
        profession[0] = toupper(profession[0]);
    }
    
    character* player = new character(account, name, race, gender, profession);
    cout << endl <<  "You are now known as: " << endl;
    cout << player->retName() << ", the level " << player->retLevel() << " " 
         << player->retRace() << " " << player->retGender() << " "  
         << player->retProf() << endl;
    cout << "Strength: " << player->retStr() << endl;
    cout << "Constitution: " << player->retCon() << endl;
    cout << "Inteligence: " << player->retInt() << endl;
    cout << "Dexterity: " << player->retDex() << endl;
    
    cin >> line;
}
