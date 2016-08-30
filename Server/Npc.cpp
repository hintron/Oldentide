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

Npc::Npc(int id, std::string name, std::string lastname, std::string race, std::string gender, 
         std::string face, std::string skin, std::string zone, int level, int hp, int maxHp, int bp, 
         int maxBp, int mp, int maxMp, int ep, int maxEp, int strength, int constitution, 
         int intelligence, int dexterity, float x, float y, float z, float pitch, float yaw) 
    :Character(name, lastname, race, gender, face, skin, zone, level, hp, maxHp, bp, maxBp, mp, 
               maxMp, ep, maxEp, strength, constitution, intelligence, dexterity, x, y, z, pitch, 
               yaw){ 
    SetId(id);
}

Npc::Npc(std::string fromString)
    :Character(fromString){
    std::vector<std::string> tokens = Utils::Tokenfy(fromString, '|');
    if (tokens[0] != "NPC_OBJECT")
        return;
    Npc::GetId(stoi(tokens[1]));
}

//------------------------------------------------------------------------------------------------//
//-------------------                      Getter Functions                    -------------------//
//------------------------------------------------------------------------------------------------//

int Npc::GetId(){
    return id;
}

//------------------------------------------------------------------------------------------------//
//-------------------                      Setter Functions                    -------------------//
//------------------------------------------------------------------------------------------------//

void Npc::SetId(int id){
    this->id = id;
}

//------------------------------------------------------------------------------------------------//
//-------------------                      Class Functions                     -------------------//
//------------------------------------------------------------------------------------------------//

std::string Npc::ToString(){
    std::string serial;
    serial.append("NPC_OBJECT|");
    serial.append(std::to_string(id));
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
