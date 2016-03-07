// File:     Player.cpp
// Created:  April 19, 2015
// Author:   Joseph DeVictoria
// Purpose:  Child class representing any player in Oldentide.
//        :  Inherits from "Character" class.

#include "Player.h"

using namespace std;

//------------------------------------------------------------------------------//
//----------                     Class Constructors                   ----------//
//------------------------------------------------------------------------------//

Player :: Player(string account, int id, int session, string name, string lastname,
                 string race, string gender, string profession, int weight, int x,
                 int y, int z, float direction) 
        : Character(name, lastname, race, gender, profession, weight, x, y, z,
                    direction) { 
    setAccount(account);
    setId(id);
    setSession(session);
}

//------------------------------------------------------------------------------//
//----------                      Getter Functions                    ----------//
//------------------------------------------------------------------------------//

string Player :: getAccount() {
    return account;
}

int Player :: getId() {
    return id;
}

int Player :: getSession() {
    return session;
}

//------------------------------------------------------------------------------//
//----------                      Setter Functions                    ----------//
//------------------------------------------------------------------------------//

void Player :: setAccount(string account) {
    this->account = account;
}

void Player :: setId(int id) {
    this->id = id;
}

void Player :: setSession(int session) {
    this->session = session;
}

//------------------------------------------------------------------------------//
//----------                      Class Functions                     ----------//
//------------------------------------------------------------------------------//

