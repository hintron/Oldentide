// File:     GameObject.cpp
// Created:  April 19, 2015
// Author:   Joseph DeVictoria
// Purpose:  Base class representing any game object in Oldentide.

#include "GameObject.h"

using namespace std;

//------------------------------------------------------------------------------//
//----------                     Class Constructors                   ----------//
//------------------------------------------------------------------------------//

GameObject::GameObject(int weight, int x, int y, int z, float direction, string zone){
    setWeight(weight);
    setX(x);
    setY(y);
    setZ(z);
    setDirection(direction);
    setZone(zone);
}

//------------------------------------------------------------------------------//
//----------                      Getter Functions                    ----------//
//------------------------------------------------------------------------------//

int GameObject::getWeight(){
    return weight;
}

int GameObject::getX(){
    return x;
}

int GameObject::getY(){
    return y;
}

int GameObject::getZ(){
    return z;
}

float GameObject::getDirection(){
    return direction;
}

string GameObject::getZone(){
    return zone;
}

//------------------------------------------------------------------------------//
//----------                      Setter Functions                    ----------//
//------------------------------------------------------------------------------//

void GameObject::setWeight(int weight){
    this->weight = weight;
}

void GameObject::setX(int x){
    this->x = x;
}

void GameObject::setY(int y){
    this->y = y;
}

void GameObject::setZ(int z){
    this->z = z;
}

void GameObject::setDirection(float direction){
    this->direction = direction;
}

void GameObject::setZone(string zone){
    this->zone = zone;
}

//------------------------------------------------------------------------------//
//----------                      Class Functions                     ----------//
//------------------------------------------------------------------------------//
