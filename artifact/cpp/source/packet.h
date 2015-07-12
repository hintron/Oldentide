// Packet class for communication between server and client.

#ifndef packet_h
#define packet_h

#include <string>
#include <iostream>
#include <fstream>
#include <cctype>
using namespace std;

class packet{
    private:
        string header;
        string data;

    public:
        packet(string head, string dat);
        ~packet();
        string returnPackedString();
        string retHeader();
        string retData();
        void setHeader(string inH);
        void setData(string inD);
};

#endif
