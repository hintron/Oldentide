// Filename:    OldentideServer.h
// Author:      Joseph DeVictoria
// Date:        Jan_31_2016
// Purpose:     Header for dedicated server class.

#ifndef OLDENTIDE_OLDENTIDESERVER_H
#define OLDENTIDE_OLDENTIDESERVER_H

#include "Player.h"
#include "Npc.h"
#include <vector>

class OldentideServer{
    public:
        OldentideServer(int port);
        ~OldentideServer();
        void run();
        std::vector<Player>* getPlayers();
        std::vector<Npc>* getNpcs();
    private:
        int sockfd;
        std::vector<Player>* players;
        std::vector<Npc>* npcs;
        void populateNpcs();
};

#endif //OLDENTIDE_OLDENTIDESERVER_H
