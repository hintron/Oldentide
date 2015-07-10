// File:     Object.h
// Created:  April 19, 2015
// Author:   Joseph DeVictoria
// Purpose:  Base class representing any game object in Oldentide.
//        :  Inherits from UDK gameobject class.

#pragma once

using namespace std;

class Object {
    
    protected:

    int weight;
    int x;
    int y;

    public:

    // Getter Functions
    int getWeight();
    int getX();
    int getY();

    // Setter Functions
    void setWeight(int weight);
    void setX(int x);
    void setY(int y);

    // Class Functions

}
