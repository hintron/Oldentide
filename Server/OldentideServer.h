// Filename:    OldentideServer.h
// Author:      Joseph DeVictoria
// Date:        Jan_31_2016
// Purpose:     Header for dedicated server class.

#ifndef OLDENTIDE_OLDENTIDESERVER_E
#define OLDENTIDE_OLDENTIDESERVER_E

#include "Player.h"
#include "Npc.h"
#include <vector>

#pragma once

class OldentideServer{
    public:
        OldentideServer();
        ~OldentideServer();
        void run();
        vector<Player>* getPlayers();
        vector<Npc>* getNpcs();
    private:
        vector<Player>* players;
        vector<Npc>* npcs;
        void populateNpcs();
}

#endif
