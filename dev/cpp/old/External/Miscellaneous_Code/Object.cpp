// File:     Object.cpp
// Created:  April 19, 2015
// Author:   Joseph DeVictoria
// Purpose:  Base class representing any game object in Oldentide.

using namespace std;

//------------------------------------------------------------------------------//
//----------                     Class Constructors                   ----------//
//------------------------------------------------------------------------------//

Object :: Object(int weight, int x, int y) {
    setWeight(weight);
    setX(x);
    setY(y);
}

//------------------------------------------------------------------------------//
//----------                      Getter Functions                    ----------//
//------------------------------------------------------------------------------//

int getWeight() {
    return weight;
}

int getX() {
    return x;
}

int getY() {
    return y;
}

//------------------------------------------------------------------------------//
//----------                      Setter Functions                    ----------//
//------------------------------------------------------------------------------//

void setWeight(int weight) {
    this.weight = weight;
}

void setX(int x) {
    this.x = x;
}

void setY(int y) {
    this.y = y;
}

//------------------------------------------------------------------------------//
//----------                      Class Functions                     ----------//
//------------------------------------------------------------------------------//
