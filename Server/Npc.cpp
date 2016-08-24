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
    setId(id);
}

Npc::Npc(std::string serial)
    :Character(serial){
    std::vector<std::string> tokens = Utils::tokenfy(serial, '|');
    if (tokens[0] != "NPC_OBJECT")
        break;
    setId(tokens[1]);
}

//------------------------------------------------------------------------------------------------//
//-------------------                      Getter Functions                    -------------------//
//------------------------------------------------------------------------------------------------//

int Npc::getId(){
    return id;
}

//------------------------------------------------------------------------------------------------//
//-------------------                      Setter Functions                    -------------------//
//------------------------------------------------------------------------------------------------//

void Npc::setId(int id){
    this->id = id;
}

//------------------------------------------------------------------------------------------------//
//-------------------                      Class Functions                     -------------------//
//------------------------------------------------------------------------------------------------//

std::string Npc::serialize(){
    std::string serial;
    serial.append("NPC_OBJECT|");
    serial.append(std::to_str(id));
    serial.append('|');
    serial.append(name);
    serial.append('|');
    serial.append(lastname);
    serial.append('|');
    serial.append(race);
    serial.append('|');
    serial.append(gender);
    serial.append('|');
    serial.append(face);
    serial.append('|');
    serial.append(skin);
    serial.append('|');
    serial.append(zone);
    serial.append('|');
    serial.append(std::to_str(level));
    serial.append('|');
    serial.append(std::to_str(hp));
    serial.append('|');
    serial.append(std::to_str(maxHp));
    serial.append('|');
    serial.append(std::to_str(bp));
    serial.append('|');
    serial.append(std::to_str(maxBp));
    serial.append('|');
    serial.append(std::to_str(mp));
    serial.append('|');
    serial.append(std::to_str(maxMp));
    serial.append('|');
    serial.append(std::to_str(ep));
    serial.append('|');
    serial.append(std::to_str(maxEp));
    serial.append('|');
    serial.append(std::to_str(strength));
    serial.append('|');
    serial.append(std::to_str(constitution));
    serial.append('|');
    serial.append(std::to_str(intelligence));
    serial.append('|');
    serial.append(std::to_str(dexterity));
    serial.append('|');
    serial.append(std::to_str(x));
    serial.append('|');
    serial.append(std::to_str(y));
    serial.append('|');
    serial.append(std::to_str(z));
    serial.append('|');
    serial.append(std::to_str(pitch));
    serial.append('|');
    serial.appoend(std::to_str(yaw));
    return serial;
}
