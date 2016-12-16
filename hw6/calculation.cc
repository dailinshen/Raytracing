//
//  calculation.cpp
//  hw1.5_ds3420
//
//  Created by lindashen on 11/17/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#include "calculation.h"

float Calculation::  dot_product(Vector a, Vector b){
    float product = a.getX()*b.getX() + a.getY()*b.getY() + a.getZ()*b.getZ();
    return product;
}


Vector Calculation:: addThree(Vector a, Vector b, Vector c){
    Vector rlt;
    rlt.setDirection(a.getX()+b.getX()+c.getX(), a.getY()+b.getY()+c.getY(), a.getZ()+b.getZ()+c.getZ());
    return rlt;
}


Vector Calculation:: cross_product(Vector a, Vector b){
    float first = a.getY()*b.getZ()-a.getZ()*b.getY();
    float second = a.getZ()*b.getX()-a.getX()*b.getZ();
    float third = a.getX()*b.getY() - a.getY()*b.getX();
    Vector v;
    v.setDirection(first, second, third);
    return v;
    
}

Vector Calculation:: minus(Vector a, Vector b){
    Vector v;
    v.setDirection(a.getX()-b.getX(), a.getY()-b.getY(), a.getZ()-b.getZ());
    return v;
}
