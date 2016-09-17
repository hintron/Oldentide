// Filename:    AdminShell.h
// Author:      Joseph DeVictoria
// Date:        Mar_6_2016
// Purpose:     Header for the Administrator shell class used to implement
//              server commands.

#ifndef OLDENTIDE_ADMINSHELL_H
#define OLDENTIDE_ADMINSHELL_H

#include "SQLConnector.h"
#include "GameState.h"
#include <limits.h>
#include <unistd.h>
#include <vector>

class AdminShell {
    public:
        AdminShell(SQLConnector * sql, GameState * gameState);
        ~AdminShell();
        void operator()();
        void Run();
        void PrintUsage();
        void PrintLogo();
    private:
        SQLConnector * sql;
        GameState * gameState;
        char serverHostname[HOST_NAME_MAX];
};

#endif // OLDENTIDE_ADMINSHELL_H
