// Filename:    Utils.h
// Author:      Joseph DeVictoria
// Date:        Mar_10_2016
// Purpose:     Header for miscellaneous functions.

#ifndef OLDENTIDE_UTILS_H
#define OLDENTIDE_UTILS_H

#include <string>
#include <vector>

namespace utils{
    std::vector<std::string> Tokenfy(std::string s, char delim);
    bool CheckPasswordLength(char *);
    bool CheckAccountNameLength(char *);
    bool SanitizeAccountName(char *);
    bool SanitizeAlphanumeric(char *);
    bool SanitizeHexString(char *);
};


#endif // OLDENTIDE_UTILS_H
