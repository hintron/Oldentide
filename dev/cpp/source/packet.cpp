//  Implementation of packet class for sending packed data.

#include <string>
#include "packet.h"
using namespace std;

packet::packet(string head, string dat){
    header = head;
    data = dat;
}

packet::~packet(){
}

string packet::returnPackedString(){
    string packedData;
    packedData.append(header);
    packedData.append("|");
    packedData.append(data);
    return packedData;
}

string packet::retHeader(){
    return header;
}

string packet::retData(){
    return data;
}

void packet::setHeader(string inH){
    header = inH;
}

void packet::setData(string inD){
    data = inD;
}
