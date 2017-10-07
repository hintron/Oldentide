// File:     Player.h
// Created:  April 19, 2015
// Author:   Joseph DeVictoria
// Purpose:  Child class representing any player in Oldentide.
//        :  Inherits from "Character" class.

#ifndef OLDENTIDE_PLAYER_H_
#define OLDENTIDE_PLAYER_H_

#include "Character.h"
#include <string>
#include <netinet/in.h>

class Player : public Character {
public:
    int id;
    int session;
    sockaddr_in client;
    std::string account;
    std::string profession;
    std::string firstname;
    std::string lastname;

    public:

    // Constructors.
    Player(
        sockaddr_in client,
        std::string account,
        int id,
        int session,
        std::string firstname,
        std::string lastname,
        std::string guild,
        std::string race,
        std::string gender,
        std::string face,
        std::string skin,
        std::string zone,
        std::string profession,
        equipment_t equipment,
        stats_t stats,
        skills_t skills,
        location_t location
    );

    ~Player();

    // Getter Functions.

    std::string GetFirstname();
    std::string GetLastname();
    sockaddr_in GetClient();
    std::string GetAccount();
    int GetId();
    int GetSession();

    // Setter Functions.

    void SetFirstname(std::string firstname);
    void SetLastname(std::string lastname);
    void SetClient(sockaddr_in client);
    void SetAccount(std::string account);
    void SetId(int id);
    void SetSession(int session);

    // Class Functions.
};

#endif //OLDENTIDE_PLAYER_H_
