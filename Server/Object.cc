// File:     Object.cc
// Created:  April 19, 2015
// Author:   Joseph DeVictoria
// Purpose:  Base class representing any game object in Oldentide.

#include "Object.h"

using namespace std;

//------------------------------------------------------------------------------//
//----------                     Class Constructors                   ----------//
//------------------------------------------------------------------------------//

Object :: Object(int weight, int x, int y, int z) {
    setWeight(weight);
    setX(x);
    setY(y);
    setZ(z);
}

//------------------------------------------------------------------------------//
//----------                      Getter Functions                    ----------//
//------------------------------------------------------------------------------//

int Object :: getWeight() {
    return weight;
}

int Object :: getX() {
    return x;
}

int Object :: getY() {
    return y;
}

int Object :: getZ() {
    return z;
}
//------------------------------------------------------------------------------//
//----------                      Setter Functions                    ----------//
//------------------------------------------------------------------------------//

void Object :: setWeight(int weight) {
    this->weight = weight;
}

void Object :: setX(int x) {
    this->x = x;
}

void Object :: setY(int y) {
    this->y = y;
}

void Object :: setZ(int z) {
    this->z = z;
}

//------------------------------------------------------------------------------//
//----------                      Class Functions                     ----------//
//------------------------------------------------------------------------------//
