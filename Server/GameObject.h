// File:     GameObject.h
// Created:  April 19, 2015
// Author:   Joseph DeVictoria
// Purpose:  Base class representing any game object in Oldentide.

#ifndef OLDENTIDE_GAMEOBJECT_H_
#define OLDENTIDE_GAMEOBJECT_H_

#include <string>

class GameObject {
    
    protected:

    int weight;
    int x;
    int y;
    int z;
    float direction;
    std::string zone;

    public:

    GameObject(int weight, int x, int y, int z, float direction, std::string zone);
    // ~GameObject();

    // Getter Functions
    int getWeight();
    int getX();
    int getY();
    int getZ();
    float getDirection();
    std::string getZone();

    // Setter Functions
    void setWeight(int weight);
    void setX(int x);
    void setY(int y);
    void setZ(int z);
    void setDirection(float direction);
    void setZone(std::string zone);

    // Class Functions

};

#endif //OLDENTIDE_GAMEOBJECT_H_

