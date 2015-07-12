// File:     Player.cpp
// Created:  April 19, 2015
// Author:   Joseph DeVictoria
// Purpose:  Child class representing any player in Oldentide.
//        :  Inherits from "Character" class.

using namespace std;

//------------------------------------------------------------------------------//
//----------                     Class Constructors                   ----------//
//------------------------------------------------------------------------------//

Player :: Player(string account, int id, int session, string name, string race, 
                 string gender, string profession, int weight, int x, int y) 
        : Character(name, race, gender, profession, weight, x, y) { 
    setAccount(account);
    setId(id);
    setSession(session);
}

//------------------------------------------------------------------------------//
//----------                      Getter Functions                    ----------//
//------------------------------------------------------------------------------//

string getAccount() {
    return account;
}

int getId() {
    return id;
}

int getSession() {
    return session;
}

//------------------------------------------------------------------------------//
//----------                      Setter Functions                    ----------//
//------------------------------------------------------------------------------//

void setAccount(string account) {
    this.account = account;
}

void setId(int id) {
    this.id = id;
}

void setSession(int session) {
    this.session = session;
}

//------------------------------------------------------------------------------//
//----------                      Class Functions                     ----------//
//------------------------------------------------------------------------------//

