// File:     Npc.h
// Created:  January 31, 2016
// Author:   Joseph DeVictoria
// Purpose:  Child class representing any NPC in Oldentide.
//        :  Inherits from "Character" class.

#ifndef OLDENTIDE_NPC_H_
#define OLDENTIDE_NPC_H_

#pragma once

#include "Character.h"
#include <string>

using namespace std;

class Npc : public Character {
    
    protected:

    int id;

    public:

    // Constructors.
    Npc(int id, string name, string race, string gender, string profession, int weight, int x, int y, int z);
    //~Npc();

    // Getter Functions.
    
    int getId();

    // Setter Functions.
    
    void setId(int id);
    
    // Class Functions.
    
};

#endif
