// Filename:    Utils.cpp
// Author:      Joseph DeVictoria
// Date:        Mar_10_2016
// Purpose:     Miscellaneous functions.

using namespace std;

#include "Utils.h"
#include <sstream>

vector<string> tokenfy(string s, char delim) {
    string token;
    vector<string> tokens;
    istringstream ss(s);
    while(getline(ss, token, delim)){
        tokens.push_back(token);
    }
    return tokens;
}
