// File:     Player.h
// Created:  April 19, 2015
// Author:   Joseph DeVictoria
// Purpose:  Child class representing any player in Oldentide.
//        :  Inherits from "Character" class.

#pragma once

using namespace std;

class Player : public Character {
    
    protected:

    string account;
    int id;
    int session; 

    public:

    // Getter Functions.
    
    string getAccount();
    int getId();
    int getSession();

    // Setter Functions.
    
    void setAccount(string account);
    void setId(int id);
    void setSession(int session);

    // Class Functions.
    
}
