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
    setGuild(guild);
    SetRace(race);
    SetGender(gender);
    SetFace(face);
    SetSkin(skin);
    SetZone(zone);
    SetHead("head");
    SetChest("chest");
    SetArms("arms");
    SetHands("hands");
    SetLegs("legs");
    SetFeet("feet");
    SetCloak("cloak");
    SetNecklace("necklace");
    SetRingOne("ringOne");
    SetRingTwo("ringTwo");
    SetRightHand("rightHand");
    SetLeftHand("leftHand");
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

Character::~Character() {
    return;
}

//------------------------------------------------------------------------------------------------//
//-------------------                      Getter Functions                    -------------------//
//------------------------------------------------------------------------------------------------//

std::string Character::GetName() {
    return name;
}

std::string Character::GetLastname() {
    return lastname;
}

std::string Character::GetGuild() {
    return guild;
}

std::string Character::GetRace() {
    return race;
}

std::string Character::GetGender() {
    return gender;
}

std::string Character::GetFace() {
    return face;
}

std::string Character::GetSkin() {
    return skin;
}

std::string Character::GetZone() {
    return zone;
}

std::string Character::GetHead() {
    return head;
}

std::string Character::GetChest() {
    return chest;
}

std::string Character::GetArms() {
    return arms;
}

std::string Character::GetHands() {
    return hands;
}

std::string Character::GetLegs() {
    return legs;
}

std::string Character::GetFeet() {
    return feet;
}

std::string Character::GetCloak() {
    return cloak;
}

std::string Character::GetNecklace() {
    return necklace;
}

std::string Character::GetRingOne() {
    return ringOne;
}

std::string Character::GetRingTwo() {
    return ringTwo;
}

std::string Character::GetRightHand() {
    return rightHand;
}

std::string Character::GetLeftHand() {
    return leftHand;
}

int Character::GetLevel() {
    return level;
}

int Character::GetHp() {
    return hp;
}

int Character::GetMaxHp() {
    return maxHp;
}

int Character::GetBp() {
    return bp;
}

int Character::GetMaxBp() {
    return maxBp;
}

int Character::GetMp() {
    return mp;
}

int Character::GetMaxMp() {
    return maxMp;
}

int Character::GetEp() {
    return ep;
}

int Character::GetMaxEp() {
    return maxEp;
}

int Character::GetStrength() {
    return strength;
}

int Character::GetConstitution() {
    return constitution;
}

int Character::GetIntelligence() {
    return intelligence;
}

int Character::GetDexterity() {
    return dexterity;
}

float Character::GetX() {
    return x;
}

float Character::GetY() {
    return y;
}

float Character::GetZ() {
    return z;
}

float Character::GetPitch() {
    return pitch;
}

float Character::GetYaw() {
    return yaw;
}

//------------------------------------------------------------------------------------------------//
//-------------------                      Setter Functions                    -------------------//
//------------------------------------------------------------------------------------------------//

void Character::SetName(std::string name) {
    this->name = name;
}

void Character::SetLastname(std::string lastname) {
    this->lastname = lastname;
}

void Character::SetGuild(std::string guild) {
    this->guild = guild;
}

void Character::SetRace(std::string race) {
    this->race = race;
}

void Character::SetGender(std::string gender) {
    this->gender = gender;
}

void Character::SetFace(std::string face) {
    this->face = face;
}

void Character::SetSkin(std::string skin) {
    this->skin = skin;
}

void Character::SetZone(std::string zone) {
    this->zone = zone;
}

void Character::SetHead(std::string head){
    this->head = head;
}

void Character::SetChest(std::string chest){
    this->chest = chest;
}

void Character::SetArms(std::string arms){
    this->arms = arms;
}

void Character::SetHands(std::string hands){
    this->hands = hands;
}

void Character::SetLegs(std::string legs){
    this->legs = legs;
}

void Character::SetFeet(std::string feet){
    this->feet = feet;
}

void Character::SetCloak(std::string cloak){
    this->cloak = cloak;
}

void Character::SetNecklace(std::string necklace){
    this->necklace = necklace;
}

void Character::SetRingOne(std::string ringOne){
    this->ringOne = ringOne;
}

void Character::SetRingTwo(std::string ringTwo){
    this->ringTwo = ringTwo;
}

void Character::SetRightHand(std::string rightHand){
    this->rightHand = rightHand;
}

void Character::SetLeftHand(std::string leftHand){
    this->leftHand = leftHand;
}

void Character::SetLevel(int level) {
    this->level = level;
}

void Character::SetHp(int hp) {
    this->hp = hp;
}

void Character::SetMaxHp(int maxHp) {
    this->maxHp = maxHp;
}

void Character::SetBp(int bp) {
    this->bp = bp;
}

void Character::SetMaxBp(int maxBp) {
    this->maxBp = maxBp;
}

void Character::SetMp(int mp) {
    this->mp = mp;
}

void Character::SetMaxMp(int maxMp) {
    this->maxMp = maxMp;
}

void Character::SetEp(int ep) {
    this->ep = ep;
}

void Character::SetMaxEp(int maxEp) {
    this->maxEp = maxEp;
}

void Character::SetStrength(int strength) {
    this->strength = strength;
}

void Character::SetConstitution(int constitution) {
    this->constitution = constitution;
}

void Character::SetIntelligence(int intelligence) {
    this->intelligence = intelligence;
}

void Character::SetDexterity(int dexterity) {
    this->dexterity = dexterity;
}

void Character::SetX(float x) {
    this->x = x;
}

void Character::SetY(float y) {
    this->y = y;
}

void Character::SetZ(float z) {
    this->z = z;
}

void Character::SetPitch(float pitch) {
    this->pitch = pitch;
}

void Character::SetYaw(float yaw) {
    this->yaw = yaw;
}

//------------------------------------------------------------------------------------------------//
//-------------------                      Class Functions                     -------------------//
//------------------------------------------------------------------------------------------------//
