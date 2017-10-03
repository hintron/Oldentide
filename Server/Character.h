// File:     Character.h
// Created:  April 19, 2015
// Author:   Joseph DeVictoria
// Purpose:  Child class representing any living object in Oldentide.

#ifndef OLDENTIDE_CHARACTER_H_
#define OLDENTIDE_CHARACTER_H_

#include <string>

typedef struct {
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
} equipment_t;


typedef struct {
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
} stats_t;

typedef struct {
    float x;
    float y;
    float z;
    float pitch;
    float yaw;
} location_t;



class Character {




    private:

    std::string firstname;
    std::string lastname;
    std::string guild;
    std::string race;
    std::string gender;
    std::string face;
    std::string skin;
    std::string zone;
    std::string profession;
    equipment_t equipment;
    stats_t stats;
    location_t location;

    public:

    // Constructors
    Character(
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
    );

    ~Character();

    // Getter Functions
    std::string GetFirstName();
    std::string GetLastname();
    std::string GetGuild();
    std::string GetRace();
    std::string GetGender();
    std::string GetFace();
    std::string GetSkin();
    std::string GetZone();
    std::string GetProfession();
    equipment_t GetEquipment();
    stats_t GetStats();
    location_t GetLocation();

    // Setter Functions
    void SetFirstName(std::string);
    void SetLastname(std::string);
    void SetGuild(std::string);
    void SetRace(std::string);
    void SetGender(std::string);
    void SetFace(std::string);
    void SetSkin(std::string);
    void SetZone(std::string);
    void SetProfession(std::string);
    void SetEquipment(equipment_t);
    void SetStats(stats_t);
    void SetLocation(location_t);

    // Class Functions
};

#endif //OLDENTIDE_CHARACTER_H_

