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
    void PrintStringHex(std::string *);
    void PrependPacketHeader(std::string *, uint8_t);
    uint8_t GetPacketTypeFromPacket(char *);
    uint16_t GetMsgpckSizeFromPacket(char *);
    std::string GetMsgpckDataFromPacket(char *packet_buffer);

};


#endif // OLDENTIDE_UTILS_H
