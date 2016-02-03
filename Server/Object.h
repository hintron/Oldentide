// File:     Object.h
// Created:  April 19, 2015
// Author:   Joseph DeVictoria
// Purpose:  Base class representing any game object in Oldentide.
//        :  Inherits from UDK gameobject class.

#ifndef OLDENTIDE_OBJECT_H_
#define OLDENTIDE_OBJECT_H_

class Object {
    
    protected:

    int weight;
    int x;
    int y;
    int z;

    public:

    Object(int weight, int x, int y, int z);
    // ~Object();

    // Getter Functions
    int getWeight();
    int getX();
    int getY();
    int getZ();

    // Setter Functions
    void setWeight(int weight);
    void setX(int x);
    void setY(int y);
    void setZ(int z);

    // Class Functions

};

#endif //OLDENTIDE_OBJECT_H_

