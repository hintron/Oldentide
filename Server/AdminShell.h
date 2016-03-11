// Filename:    AdminShell.h
// Author:      Joseph DeVictoria
// Date:        Mar_6_2016
// Purpose:     Header for the Administrator shell class used to implement
//              server commands.

#ifndef OLDENTIDE_ADMINSHELL_H
#define OLDENTIDE_ADMINSHELL_H

#include "SQLConnector.h"
#include <limits.h>
#include <unistd.h>
#include <vector>

class AdminShell {
    public:
        AdminShell(SQLConnector * input);
        ~AdminShell();
        void operator()();
        void run();
        void printUsage();
        void printLogo();
    private:
        SQLConnector * sql;
        char serverHostname[HOST_NAME_MAX];
};

#endif // OLDENTIDE_ADMINSHELL_H
