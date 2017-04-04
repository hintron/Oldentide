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

Npc::Npc(int id, std::string name, std::string lastname, std::string guild, std::string race, 
         std::string gender, std::string face, std::string skin, std::string zone, int level, 
         int hp, int maxHp, int bp, int maxBp, int mp, int maxMp, int ep, int maxEp, int strength, 
         int constitution, int intelligence, int dexterity, float x, float y, float z, float pitch, 
         float yaw) 
    :Character(name, lastname, guild, race, gender, face, skin, zone, level, hp, maxHp, bp, maxBp, 
               mp, maxMp, ep, maxEp, strength, constitution, intelligence, dexterity, x, y, z, 
               pitch, yaw) { 
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
