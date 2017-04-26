// Filename:    Packets.h
// Author:      Joseph DeVictoria
// Date:        Feb_14_2016
// Purpose:     UDP Packet Struct Definitions.

#ifndef PACKETS_H
#define PACKETS_H

#include <msgpack.hpp>

// Currently, we can have up to 255 packet types
// Enumerate list of packet types (One-hot encoded)
enum PTYPE {
    // Reserve 0 for null/uninitialized
    GENERIC = 1,
    ACK = 2,
    CONNECT = 3,
    DISCONNECT = 4,
    // GETSALT = 5,
    // CREATEACCOUNT = 6,
    // LOGIN = 7,
    LISTCHARACTERS = 8,
    SELECTCHARACTER = 9,
    DELETECHARACTER = 10,
    CREATECHARACTER = 11,
    INITIALIZEGAME = 12,
    UPDATEPC = 13,
    UPDATENPC = 14,
    SENDPLAYERCOMMAND = 15,
    SENDSERVERCOMMAND = 16,
    SENDPLAYERACTION = 17,
    SENDSERVERACTION = 18,
    UNITY = 19
};


// Use this to send enums over messagepack - currently not needed
// MSGPACK_ADD_ENUM(PTYPE);

// Define packet maximums
// Generally, to avoid packet fragmentation, it is suggested to keep it to around 512 for maximum leniency,
// though they say you can go up to about 1400 for general use.
// See http://stackoverflow.com/questions/2862071/how-large-should-my-recv-buffer-be-when-calling-recv-in-the-socket-library
// See http://stackoverflow.com/questions/1098897/what-is-the-largest-safe-udp-packet-size-on-the-internet
#define PACKET_MAX_SIZE 512
#define PACKET_HEADER_SIZE 3
const uint16_t MSGPCK_MAX_PAYLOAD_SIZE = PACKET_MAX_SIZE - PACKET_HEADER_SIZE;

class PacketGeneric {
public:
    int32_t packetId;
    int32_t sessionId;
    std::string message;
    MSGPACK_DEFINE(packetId, sessionId, message);
};

class PacketAck {
public:
    int32_t packetId;
    int32_t sessionId;
    MSGPACK_DEFINE(packetId, sessionId);
};

class PacketConnect {
public:
    int32_t packetId;
    int32_t sessionId;
    MSGPACK_DEFINE(packetId, sessionId);
};

class PacketDisconnect {
public:
    int32_t packetId;
    int32_t sessionId;
    MSGPACK_DEFINE(packetId, sessionId);
};

class PacketListcharacters {
public:
    int32_t packetId;
    int32_t sessionId;
    // Array of characters!
    std::vector<std::string> characters;
    MSGPACK_DEFINE(packetId, sessionId, characters);
};

class PacketSelectcharacter {
public:
    int32_t packetId;
    int32_t sessionId;
    std::string character;
    MSGPACK_DEFINE(packetId, sessionId, character);
};

class PacketDeletecharacter {
public:
    int32_t packetId;
    int32_t sessionId;
    std::string character;
    MSGPACK_DEFINE(packetId, sessionId, character);
};

class PacketCreatecharacter {
public:
    int32_t packetId;
    int32_t sessionId;
    std::string firstName;
    std::string lastName;
    std::string guild;
    std::string race;
    std::string gender;
    std::string face;
    std::string skin;
    std::string profession;


    std::map<std::string, uint32_t> attributes;

    MSGPACK_DEFINE(
        packetId,
        sessionId,
        firstName,
        lastName,
        guild,
        race,
        gender,
        face,
        skin,
        profession,
        attributes
    );
};

class PacketInitializegame {
public:
    int32_t packetId;
    int32_t sessionId;
    MSGPACK_DEFINE(packetId, sessionId);
};

class PacketUpdatepc {
public:
    int32_t packetId;
    int32_t sessionId;
    std::string firstName;
    std::string lastName;
    std::string race;
    std::string gender;
    std::string profession;
    uint32_t level;
    uint32_t hp;
    uint32_t bp;
    uint32_t mp;
    uint32_t ep;
    float x;
    float y;
    float z;
    float pitch;
    float yaw;
    MSGPACK_DEFINE(packetId, sessionId,
        firstName,
        lastName,
        race,
        gender,
        profession,
        level,
        hp,
        bp,
        mp,
        ep,
        x,
        y,
        z,
        pitch,
        yaw
    );
};

class PacketUpdatenpc {
public:
    int32_t packetId;
    int32_t sessionId;
    MSGPACK_DEFINE(packetId, sessionId);
};

class PacketSendplayercommand {
public:
    int32_t packetId;
    int32_t sessionId;
    std::string command;
    MSGPACK_DEFINE(packetId, sessionId, command);
};

class PacketSendservercommand {
public:
    int32_t packetId;
    int32_t sessionId;
    std::string command;
    MSGPACK_DEFINE(packetId, sessionId, command);
};

class PacketSendplayeraction {
public:
    int32_t packetId;
    int32_t sessionId;
    MSGPACK_DEFINE(packetId, sessionId);
};

class PacketSendserveraction {
public:
    int32_t packetId;
    int32_t sessionId;
    MSGPACK_DEFINE(packetId, sessionId);
};

class PacketUnity {
public:
    int32_t packetId;
    int32_t sessionId;
    int32_t data1;
    int32_t data2;
    int32_t data3;
    int32_t data4;
    int32_t data5;
    MSGPACK_DEFINE(packetId, sessionId,
    data1,
    data2,
    data3,
    data4,
    data5);
};



#endif //PACKETS_H
