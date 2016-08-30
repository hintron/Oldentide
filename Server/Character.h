// File:     Character.h
// Created:  April 19, 2015
// Author:   Joseph DeVictoria
// Purpose:  Child class representing any living object in Oldentide.

#ifndef OLDENTIDE_CHARACTER_H_
#define OLDENTIDE_CHARACTER_H_

#include <string>

class Character {

    protected:

    std::string name;
    std::string lastname;
    std::string race;
    std::string gender;
    std::string face;
    std::string skin;
    std::string zone;
    int level;
    int hp;
    int maxHp;
    int bp;
    int maxBp;
    int mp;
    int maxMp;
    int ep;
    int maxEp;
    int strength;
    int constitution;
    int intelligence;
    int dexterity;
    float x;
    float y;
    float z;
    float pitch;
    float yaw;

    public:

    // Constructors
    Character(std::string name, std::string lastname, std::string race, std::string gender, 
              std::string face, std::string skin, std::string zone, int level, int hp, int maxHp, 
              int bp, int maxBp, int mp, int maxMp, int ep, int maxEp, int strength, 
              int constitution, int intelligence, int dexterity, float x, float y, float z, 
              float pitch, float yaw);
              
    Character(std::string fromString);

    //~Character();
    
    // Getter Functions
    std::string GetName();
    std::string GetLastname();
    std::string GetRace();
    std::string GetGender();
    std::string GetFace();
    std::string GetSkin();
    std::string GetZone();
    int GetLevel();
    int GetHp();
    int GetMaxHp();
    int GetBp();
    int GetMaxBp();
    int GetMp();
    int GetMaxMp();
    int GetEp();
    int GetMaxEp();
    int GetStrength();
    int GetConstitution();
    int GetIntelligence();
    int GetDexterity();
    float GetX();
    float GetY();
    float GetZ();
    float GetPitch();
    float GetYaw();

    // Setter Functions
    void SetName(std::string name);
    void SetLastname(std::string lastname);
    void SetRace(std::string race);
    void SetGender(std::string gender);
    void SetFace(std::string face);
    void SetSkin(std::string skin);
    void SetZone(std::string zone);
    void SetLevel(int level);
    void SetHp(int hp);
    void SetMaxHp(int hp);
    void SetBp(int bp);
    void SetMaxBp(int bp);
    void SetMp(int mp);
    void SetMaxMp(int mp);
    void SetEp(int ep);
    void SetMaxEp(int ep);
    void SetStrength(int strength);
    void SetConstitution(int constitution);
    void SetIntelligence(int intelligence);
    void SetDexterity(int dexterity);
    void SetX(float x);
    void SetY(float y);
    void SetZ(float z);
    void SetPitch(float pitch);
    void SetYaw(float yaw);

    // Class Functions

};

#endif //OLDENTIDE_CHARACTER_H_

