//
//  color.cpp
//  hw1.5_ds3420
//
//  Created by lindashen on 11/17/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#include "color.h"


void Color:: setRGB(float r, float g, float b){
    this->r = r;
    this->g = g;
    this->b = b;
}

float Color:: getR(){
    return r;
}

float Color:: getG(){
    return g;
}

float Color:: getB(){
    return b;
}
