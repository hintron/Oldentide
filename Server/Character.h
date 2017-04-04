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
    std::string guild;
    std::string race;
    std::string gender;
    std::string face;
    std::string skin;
    std::string zone;
    std::string head;
    std::string chest;
    std::string arms;
    std::string hands;
    std::string legs;
    std::string feet;
    std::string cloak;
    std::string necklace;
    std::string ringOne;
    std::string ringTwo;
    std::string rightHand;
    std::string leftHand;
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
    Character(std::string name, std::string lastname, std::string guild, std::string race, 
              std::string gender, std::string face, std::string skin, std::string zone, 
              int level, int hp, int maxHp, int bp, int maxBp, int mp, int maxMp, int ep,
              int maxEp, int strength, int constitution, int intelligence, int dexterity,
              float x, float y, float z, float pitch, float yaw);
              
    ~Character();
    
    // Getter Functions
    std::string GetName();
    std::string GetLastname();
    std::string GetGuild();
    std::string GetRace();
    std::string GetGender();
    std::string GetFace();
    std::string GetSkin();
    std::string GetZone();
    std::string GetHead();
    std::string GetChest();
    std::string GetArms();
    std::string GetHands();
    std::string GetLegs();
    std::string GetFeet();
    std::string GetCloak();
    std::string GetNecklace();
    std::string GetRingOne();
    std::string GetRingTwo();
    std::string GetRightHand();
    std::string GetLeftHand();
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
    void SetGuild(std::string guild);
    void SetRace(std::string race);
    void SetGender(std::string gender);
    void SetFace(std::string face);
    void SetSkin(std::string skin);
    void SetZone(std::string zone);
    void SetHead(std::string head);
    void SetChest(std::string chest);
    void SetArms(std::string arms);
    void SetHands(std::string hands);
    void SetLegs(std::string legs);
    void SetFeet(std::string feet);
    void SetCloak(std::string cloak);
    void SetNecklace(std::string necklace);
    void SetRingOne(std::string ringOne);
    void SetRingTwo(std::string ringTwo);
    void SetRightHand(std::string rightHand);
    void SetLeftHand(std::string leftHand);
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
    void SetPosition(float x, float y, float z, float pitch, float yaw);

};

#endif //OLDENTIDE_CHARACTER_H_

