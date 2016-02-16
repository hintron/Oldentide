// File:     Player.h
// Created:  April 19, 2015
// Author:   Joseph DeVictoria
// Purpose:  Child class representing any player in Oldentide.
//        :  Inherits from "Character" class.

#ifndef OLDENTIDE_PLAYER_H_
#define OLDENTIDE_PLAYER_H_

#include "Character.h"
#include <string>

class Player : public Character {
    
    protected:

    std::string account;
    int id;
    int session; 

    public:

    // Constructors.
    Player(std::string account, int id, int session, std::string name, 
           std::string lastname, std::string race, std::string gender, 
           std::string profession, int weight, int x, int y, int z,
           float direction);
    //~Player();

    // Getter Functions.
    
    std::string getAccount();
    int getId();
    int getSession();

    // Setter Functions.
    
    void setAccount(std::string account);
    void setId(int id);
    void setSession(int session);

    // Class Functions.
    
};

#endif //OLDENTIDE_PLAYER_H_
