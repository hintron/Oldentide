// File:     Npc.cpp
// Created:  January 31, 2016
// Author:   Joseph DeVictoria
// Purpose:  Child class representing any NPC in Oldentide.
//        :  Inherits from "Character" class.

#include "Npc.h"
#include "Utils.h"

//------------------------------------------------------------------------------------------------//
//-------------------                     Class Constructors                   -------------------//
//------------------------------------------------------------------------------------------------//

Npc::Npc(int id, std::string firstname, std::string lastname, std::string guild, std::string race, 
         std::string gender, std::string face, std::string skin, int level, int hp, int maxHp,
         int bp, int maxBp, int mp, int maxMp, int ep, int maxEp, int strength, int constitution,
         int intelligence, int dexterity, std::string head, std::string chest, std::string arms,
         std::string hands, std::string legs, std::string feet, std::string cloak,
         std::string necklace, std::string ringone, std::string ringtwo, std::string righthand,
         std::string lefthand, std::string zone, float x, float y, float z, float pitch, float yaw) 
    :Character(firstname, lastname, guild, race, gender, face, skin, level, hp, maxHp, bp, maxBp, 
               mp, maxMp, ep, maxEp, strength, constitution, intelligence, dexterity, head, chest,
               arms, hands, legs, feet, cloak, necklace, ringone, ringtwo, righthand, lefthand, 
               zone, x, y, z, pitch, yaw) { 
    SetId(id);
}

Npc::~Npc() {
    return;
}

//------------------------------------------------------------------------------------------------//
//-------------------                      Getter Functions                    -------------------//
//------------------------------------------------------------------------------------------------//

int Npc::GetId() {
    return id;
}

//------------------------------------------------------------------------------------------------//
//-------------------                      Setter Functions                    -------------------//
//------------------------------------------------------------------------------------------------//

void Npc::SetId(int id) {
    this->id = id;
}

//------------------------------------------------------------------------------------------------//
//-------------------                      Class Functions                     -------------------//
//------------------------------------------------------------------------------------------------//
