// File:     Npc.h
// Created:  January 31, 2016
// Author:   Joseph DeVictoria
// Purpose:  Child class representing any NPC in Oldentide.
//        :  Inherits from "Character" class.

#ifndef OLDENTIDE_NPC_H_
#define OLDENTIDE_NPC_H_

#include "Character.h"
#include <string>

class Npc : public Character {
    
    protected:

    int id;

    public:

    // Constructors.
    Npc(int id, std::string firstname, std::string lastname, std::string guild, std::string race, 
        std::string gender, std::string face, std::string skin, int level, int hp, int maxHp,
        int bp, int maxBp, int mp, int maxMp, int ep, int maxEp, int strength, int constitution,
        int intelligence, int dexterity, std::string head, std::string chest, std::string arms,
        std::string hands, std::string legs, std::string feet, std::string cloak,
        std::string necklace, std::string ringone, std::string ringtwo, std::string righthand,
        std::string lefthand, std::string zone, float x, float y, float z, float pitch, float yaw);

    ~Npc();

    // Getter Functions.
    int GetId();

    // Setter Functions.
    void SetId(int id);
    
    // Class Functions.
    std::string ToString();
    
};

#endif //OLDENTIDE_NPC_H_

