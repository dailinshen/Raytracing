//
//  point.cpp
//  hw1.5_ds3420
//
//  Created by lindashen on 11/17/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#include "point.h"
void Point:: setPosition(Vector a){
    this->Vector::setPosition(a.getX(), a.getY(), a.getZ());
}


void Point:: setPosition(float x, float y, float z){
    this->Vector::setPosition(x, y, z);
}
