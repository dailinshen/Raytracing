//
//  vector.cpp
//  hw1.5_ds3420
//
//  Created by lindashen on 11/17/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#include "vector.h"

void Vector:: setDirection(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vector:: setDirection(Vector a){
    this->x = a.getX();
    this->y = a.getY();
    this->z = a.getZ();
}

void Vector:: setPosition(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vector:: setPosition(Vector a){
    this->setPosition(a.getX(), a.getY(), a.getZ());
}

Vector Vector:: getPosition(){
    Vector temp;
    temp.setDirection(this->getX(), this->getY(), this->getZ());
    return temp;
}

float Vector:: getX(){
    return x;
}

float Vector:: getY(){
    return y;
}
float Vector:: getZ(){
    return z;
}
