// File:     Npc.cpp
// Created:  January 31, 2016
// Author:   Joseph DeVictoria
// Purpose:  Child class representing any NPC in Oldentide.
//        :  Inherits from "Character" class.

#include "Npc.h"

using namespace std;

//------------------------------------------------------------------------------//
//----------                     Class Constructors                   ----------//
//------------------------------------------------------------------------------//

Npc :: Npc(int id, string name, string lastname, string race, string gender, 
           string profession, int weight, int x, int y, int z, float direction) 
     : Character(name, lastname, race, gender, profession, weight, x, y, z, 
                 direction) { 
    setId(id);
}

//------------------------------------------------------------------------------//
//----------                      Getter Functions                    ----------//
//------------------------------------------------------------------------------//

int Npc :: getId() {
    return id;
}

//------------------------------------------------------------------------------//
//----------                      Setter Functions                    ----------//
//------------------------------------------------------------------------------//

void Npc :: setId(int id) {
    this->id = id;
}

//------------------------------------------------------------------------------//
//----------                      Class Functions                     ----------//
//------------------------------------------------------------------------------//

