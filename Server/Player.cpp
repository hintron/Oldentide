// File:     Player.cpp
// Created:  April 19, 2015
// Author:   Joseph DeVictoria
// Purpose:  Child class representing any player in Oldentide.
//        :  Inherits from "Character" class.

#include "Player.h"
#include <netinet/in.h>

//------------------------------------------------------------------------------------------------//
//-------------------                     Class Constructors                   -------------------//
//------------------------------------------------------------------------------------------------//

Player::Player(
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
    location_t location
)
: Character(
    firstname,
    lastname,
    guild,
    race,
    gender,
    face,
    skin,
    zone,
    profession,
    equipment,
    stats,
    location
)
{
    SetClient(client);
    SetAccount(account);
    SetId(id);
    SetSession(session);
}

Player::~Player() {
    return;
}

//------------------------------------------------------------------------------------------------//
//-------------------                      Getter Functions                    -------------------//
//------------------------------------------------------------------------------------------------//

std::string Player::GetFirstname() {
    return firstname;
}

std::string Player::GetLastname() {
    return lastname;
}

sockaddr_in Player::GetClient() {
    return client;
}

std::string Player::GetAccount() {
    return account;
}

int Player::GetId() {
    return id;
}

int Player::GetSession() {
    return session;
}



//------------------------------------------------------------------------------------------------//
//-------------------                      Setter Functions                    -------------------//
//------------------------------------------------------------------------------------------------//

void Player::SetFirstname(std::string firstname) {
    this->firstname = firstname;
}

void Player::SetLastname(std::string lastname) {
    this->lastname = lastname;
}

void Player::SetClient(sockaddr_in client) {
    this->client = client;
}

void Player::SetAccount(std::string account) {
    this->account = account;
}

void Player::SetId(int id) {
    this->id = id;
}

void Player::SetSession(int session) {
    this->session = session;
}



//------------------------------------------------------------------------------------------------//
//-------------------                      Class Functions                     -------------------//
//------------------------------------------------------------------------------------------------//

