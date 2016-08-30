// File:     Character.cpp
// Created:  April 19, 2015
// Author:   Joseph DeVictoria
// Purpose:  Child class representing any living object in Oldentide.

#include "Character.h"
#include "Utils.h"

//------------------------------------------------------------------------------------------------//
//-------------------                     Class Constructors                   -------------------//
//------------------------------------------------------------------------------------------------//

Character::Character(std::string name, std::string lastname, std::string race, std::string gender, 
                     std::string face, std::string skin, std::string zone, int level, int hp, 
                     int maxHp, int bp, int maxBp, int mp, int maxMp, int ep, int maxEp, 
                     int strength, int constitution, int intelligence, int dexterity, float x, 
                     float y, float z, float pitch, float yaw) {
    SetName(name);
    SetLastname(lastname);
    SetRace(race);
    SetGender(gender);
    SetFace(face);
    SetSkin(skin);
    SetZone(zone);
    SetLevel(level);
    SetHp(hp);
    SetMaxHp(maxHp);
    SetBp(bp);
    SetMaxBp(maxBp);
    SetMp(mp);
    SetMaxMp(maxMp);
    SetEp(ep);
    SetMaxEp(maxEp);
    SetStrength(strength);
    SetConstitution(constitution);
    SetIntelligence(intelligence);
    SetDexterity(dexterity);
    SetX(x);
    SetY(y);
    SetZ(z);
    SetPitch(pitch);
    SetYaw(yaw);
}

Character::Character(std::string fromString){
    std::vector<std::string> tokens = Utils::Tokenfy(fromString, '|');
    if (tokens[0] == "PLAYER_OBJECT"){
        SetName(tokens[57]);
        SetLastname(tokens[58]);
        SetRace(tokens[59]);
        SetGender(tokens[60]);
        SetFace(tokens[61]);
        SetSkin(tokens[62]);
        SetZone(tokens[63]);
        SetLevel(std::stoi(tokens[64]));
        SetHp(std::stoi(tokens[65]));
        SetMaxHp(std::stoi(tokens[66]));
        SetBp(std::stoi(tokens[67]));
        SetMaxBp(std::stoi(tokens[68]));
        SetMp(std::stoi(tokens[69]));
        SetMaxMp(std::stoi(tokens[70]));
        SetEp(std::stoi(tokens[71]));
        SetMaxEp(std::stoi(tokens[72]));
        SetStrength(std::stoi(tokens[73]));
        SetConstitution(std::stoi(tokens[74]));
        SetIntelligence(std::stoi(tokens[75]));
        SetDexterity(std::stoi(tokens[76]));
        SetX(std::stof(tokens[77]));
        SetY(std::stof(tokens[78]));
        SetZ(std::stof(tokens[79]));
        SetPitch(std::stof(tokens[80]));
        SetYaw(std::stof(tokens[81]));
    }
    // if (tokens[0] == "NPC_OBJECT"){
    //    
    // }
}

//------------------------------------------------------------------------------------------------//
//-------------------                      Getter Functions                    -------------------//
//------------------------------------------------------------------------------------------------//

std::string Character::GetName(){
    return name;
}

std::string Character::GetLastname(){
    return lastname;
}

std::string Character::GetRace(){
    return race;
}

std::string Character::GetGender(){
    return gender;
}

std::string Character::GetFace(){
    return face;
}

std::string Character::GetSkin(){
    return skin;
}

std::string Character::GetZone(){
    return zone;
}

int Character::GetLevel(){
    return level;
}

int Character::GetHp(){
    return hp;
}

int Character::GetMaxHp(){
    return maxHp;
}

int Character::GetBp(){
    return bp;
}

int Character::GetMaxBp(){
    return maxBp;
}

int Character::GetMp(){
    return mp;
}

int Character::GetMaxMp(){
    return maxMp;
}

int Character::GetEp(){
    return ep;
}

int Character::GetMaxEp(){
    return maxEp;
}

int Character::GetStrength(){
    return strength;
}

int Character::GetConstitution(){
    return constitution;
}

int Character::GetIntelligence(){
    return intelligence;
}

int Character::GetDexterity(){
    return dexterity;
}

float Character::GetX(){
    return x;
}

float Character::GetY(){
    return y;
}

float Character::GetZ(){
    return z;
}

float Character::GetPitch(){
    return pitch;
}

float Character::GetYaw(){
    return yaw;
}

//------------------------------------------------------------------------------------------------//
//-------------------                      Setter Functions                    -------------------//
//------------------------------------------------------------------------------------------------//

void Character::SetName(std::string name){
    this->name = name;
}

void Character::SetLastname(std::string lastname){
    this->lastname = lastname;
}
void Character::SetRace(std::string race){
    this->race = race;
}

void Character::SetGender(std::string gender){
    this->gender = gender;
}

void Character::SetFace(std::string face){
    this->face = face;
}

void Character::SetSkin(std::string skin){
    this->skin = skin;
}

void Character::SetZone(std::string zone){
    this->zone = zone;
}

void Character::SetLevel(int level){
    this->level = level;
}

void Character::SetHp(int hp){
    this->hp = hp;
}

void Character::SetMaxHp(int maxHp){
    this->maxHp = maxHp;
}

void Character::SetBp(int bp){
    this->bp = bp;
}

void Character::SetMaxBp(int maxBp){
    this->maxBp = maxBp;
}

void Character::SetMp(int mp){
    this->mp = mp;
}

void Character::SetMaxMp(int maxMp){
    this->maxMp = maxMp;
}

void Character::SetEp(int ep){
    this->ep = ep;
}

void Character::SetMaxEp(int maxEp){
    this->maxEp = maxEp;
}

void Character::SetStrength(int strength){
    this->strength = strength;
}

void Character::SetConstitution(int constitution){
    this->constitution = constitution;
}

void Character::SetIntelligence(int intelligence){
    this->intelligence = intelligence;
}

void Character::SetDexterity(int dexterity){
    this->dexterity = dexterity;
}

void Character::SetX(float x){
    this->x = x;
}

void Character::SetY(float y){
    this->y = y;
}

void Character::SetZ(float z){
    this->z = z;
}

void Character::SetPitch(float pitch){
    this->pitch = pitch;
}

void Character::SetYaw(float yaw){
    this->yaw = yaw;
}

//------------------------------------------------------------------------------------------------//
//-------------------                      Class Functions                     -------------------//
//------------------------------------------------------------------------------------------------//
