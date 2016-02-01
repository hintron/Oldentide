// File:     Player.h
// Created:  April 19, 2015
// Author:   Joseph DeVictoria
// Purpose:  Child class representing any player in Oldentide.
//        :  Inherits from "Character" class.

#ifndef OLDENTIDE_PLAYER_H_
#define OLDENTIDE_PLAYER_H_

#include "Character.h"
#include <string>

#pragma once

using namespace std;

class Player : public Character {
    
    protected:

    string account;
    int id;
    int session; 

    public:

    // Constructors.
    Player(string account, int id, int session, string name, string race, 
           string gender, string profession, int weight, int x, int y, int z);
    //~Player();

    // Getter Functions.
    
    string getAccount();
    int getId();
    int getSession();

    // Setter Functions.
    
    void setAccount(string account);
    void setId(int id);
    void setSession(int session);

    // Class Functions.
    
};

#endif
