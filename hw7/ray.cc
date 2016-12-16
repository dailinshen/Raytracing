//
//  ray.cpp
//  hw1.5_ds3420
//
//  Created by lindashen on 11/17/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#include "ray.h"

void Ray:: setDirection(float x, float y, float z){
    float temp =sqrt(x*x+y*y+z*z);
    x = x/temp;
    y = y/temp;
    z = z/temp;
    dir.setDirection(x, y, z);
}

void Ray:: setDirection(Vector a){
    this->setDirection(a.x, a.y, a.z);
}

void Ray:: setOrigin(float x, float y, float z){
    this->origin.setPosition(x, y, z);
}

void Ray:: setOrigin(Vector a){
    this->origin.setPosition(a);
}

Ray Ray:: reverse(){
    Ray r_re;
    r_re.setDirection(-dir.x, -dir.y, -dir.z);
    return std::move(r_re);
}


Point Ray:: getOrigin(){
    return std::move(origin);
}
Vector Ray:: getDir(){
    return std::move(dir);
}
