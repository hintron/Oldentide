// Filename:    Packets.h
// Author:      Joseph DeVictoria
// Date:        Feb_14_2016
// Purpose:     UDP Packet Struct Definitions.

#ifndef PACKETS_H
#define PACKETS_H

#include <msgpack.hpp>

// Enumerate list of packet types (One-hot encoded)
enum PTYPE{
    // Reserve 0 for null/uninitialized
    GENERIC = 1,
    ACK = 2,
    CONNECT = 3,
    DISCONNECT = 4,
    GETSALT = 5,
    CREATEACCOUNT = 6,
    LOGIN = 7,
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


class TestData {
    public:
        std::string value;
        int i;
        // write the member variables that you want to pack
        MSGPACK_DEFINE(value, i);
};





class PacketGeneric {
public:
    int packetId;
    int sessionId;
    std::string message;
    MSGPACK_DEFINE(packetId, sessionId, message);
};

class PacketAck {
public:
    int packetId;
    int sessionId;
    MSGPACK_DEFINE(packetId, sessionId);
};

class PacketConnect {
public:
    int packetId;
    int sessionId;
    MSGPACK_DEFINE(packetId, sessionId);
};

class PacketDisconnect {
public:
    int packetId;
    int sessionId;
    MSGPACK_DEFINE(packetId, sessionId);
};

// class PacketGetsalt {
// public:
//     int packetId;
//     int sessionId;
//     std::string account;
//     // 512-bit key -> 64 bytes -> 2 chars per byte for hex -> 128 + 1 null = 129
//     std::string saltStringHex;
// };

// class PacketCreateaccount {
// public:
//     int packetId;
//     int sessionId;
//     std::string account;
//     // 512-bit key -> 64 bytes -> 2 chars per byte for hex -> 128 + 1 null = 129
//     std::string saltStringHex;
//     std::string keyStringHex;
//     MSGPACK_DEFINE(packetId, sessionId);
// };

class PacketListcharacters {
public:
    int packetId;
    int sessionId;
    // Array of characters!
    std::vector<std::string> characters;
    MSGPACK_DEFINE(packetId, sessionId, characters);
};

class PacketSelectcharacter {
public:
    int packetId;
    int sessionId;
    std::string character;
    MSGPACK_DEFINE(packetId, sessionId, character);
};

class PacketDeletecharacter {
public:
    int packetId;
    int sessionId;
    std::string character;
    MSGPACK_DEFINE(packetId, sessionId, character);
};

class PacketCreatecharacter {
public:
    int packetId;
    int sessionId;
    std::string firstName;
    std::string lastName;
    // std::string guild;
    // std::string race;
    // std::string gender;
    // std::string face;
    // std::string skin;
    // std::string profession;
    // int strength;
    // int constitution;
    // int intelligence;
    // int dexterity;
    // int axe;
    // int dagger;
    // int unarmed;
    // int hammer;
    // int polearm;
    // int spear;
    // int staff;
    // int sword;
    // int archery;
    // int crossbow;
    // int sling;
    // int thrown;
    // int armor;
    // int dualWeapon;
    // int shield;
    // int bardic;
    // int conjuring;
    // int druidic;
    // int illusion;
    // int necromancy;
    // int sorcery;
    // int shamanic;
    // int spellcraft;
    // int summoning;
    // int focus;
    // int armorsmithing;
    // int tailoring;
    // int fletching;
    // int weaponsmithing;
    // int alchemy;
    // int lapidary;
    // int calligraphy;
    // int enchanting;
    // int herbalism;
    // int hunting;
    // int mining;
    // int bargaining;
    // int camping;
    // int firstAid;
    // int lore;
    // int pickLocks;
    // int scouting;
    // int search;
    // int stealth;
    // int traps;
    // int aeolandis;
    // int hieroform;
    // int highGundis;
    // int oldPraxic;
    // int praxic;
    // int runic;
    MSGPACK_DEFINE(
        packetId,
        sessionId,
        firstName,
        lastName
        // guild,
        // race,
        // gender,
        // face,
        // skin,
        // profession,
        // strength,
        // constitution,
        // intelligence,
        // dexterity,
        // axe,
        // dagger,
        // unarmed,
        // hammer,
        // polearm,
        // spear,
        // staff,
        // sword,
        // archery,
        // crossbow,
        // sling,
        // thrown,
        // armor,
        // dualWeapon,
        // shield,
        // bardic,
        // conjuring,
        // druidic,
        // illusion,
        // necromancy,
        // sorcery,
        // shamanic,
        // spellcraft,
        // summoning,
        // focus,
        // armorsmithing,
        // tailoring,
        // fletching,
        // weaponsmithing,
        // alchemy,
        // lapidary,
        // calligraphy,
        // enchanting,
        // herbalism,
        // hunting,
        // mining,
        // bargaining,
        // camping,
        // firstAid,
        // lore,
        // pickLocks,
        // scouting,
        // search,
        // stealth,
        // traps,
        // aeolandis,
        // hieroform,
        // highGundis,
        // oldPraxic,
        // praxic,
        // runic
    );
};

class PacketInitializegame {
public:
    int packetId;
    int sessionId;
    MSGPACK_DEFINE(packetId, sessionId);
};

class PacketUpdatepc {
public:
    int packetId;
    int sessionId;
    std::string firstName;
    std::string lastName;
//     std::string race;
//     std::string gender;
//     std::string profession;
//     int level;
//     int hp;
//     int bp;
//     int mp;
//     int ep;
//     float x;
//     float y;
//     float z;
//     float pitch;
//     float yaw;
    MSGPACK_DEFINE(packetId, sessionId,
        firstName,
        lastName
//         race,
//         gender,
//         profession,
//         level,
//         hp,
//         bp,
//         mp,
//         ep,
//         x,
//         y,
//         z,
//         pitch,
//         yaw
    );
};

class PacketUpdatenpc {
public:
    int packetId;
    int sessionId;
    MSGPACK_DEFINE(packetId, sessionId);
};

class PacketSendplayercommand {
public:
    int packetId;
    int sessionId;
    std::string command;
    MSGPACK_DEFINE(packetId, sessionId, command);
};

class PacketSendservercommand {
public:
    int packetId;
    int sessionId;
    std::string command;
    MSGPACK_DEFINE(packetId, sessionId, command);
};

class PacketSendplayeraction {
public:
    int packetId;
    int sessionId;
    MSGPACK_DEFINE(packetId, sessionId);
};

class PacketSendserveraction {
public:
    int packetId;
    int sessionId;
    MSGPACK_DEFINE(packetId, sessionId);
};

class PacketUnity {
public:
    int packetId;
    int sessionId;
    int data1;
    int data2;
    int data3;
    int data4;
    int data5;
    MSGPACK_DEFINE(packetId, sessionId,
    data1,
    data2,
    data3,
    data4,
    data5);
};



#endif //PACKETS_H
