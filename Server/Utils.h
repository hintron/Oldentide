// Filename:    Utils.h
// Author:      Joseph DeVictoria
// Date:        Mar_10_2016
// Purpose:     Header for miscellaneous functions.

#ifndef OLDENTIDE_UTILS_H
#define OLDENTIDE_UTILS_H

#include <string>
#include <vector>

std::vector<std::string> tokenfy(std::string s, char delim);

class Utils{
    public:
        Utils();
        ~Utils();
        static int check_password_length(char *);
        static int check_account_name_length(char *);
        static int sanitize_account_name(char *);
        static int sanitize_alphanumeric(char *);
        static int sanitize_hex_string(char *);
};


#endif // OLDENTIDE_UTILS_H
