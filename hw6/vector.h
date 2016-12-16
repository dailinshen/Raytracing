//
//  vector.hpp
//  hw1.5_ds3420
//
//  Created by lindashen on 11/17/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#ifndef vector_hpp
#define vector_hpp

#include <stdio.h>
#include <math.h>

class Vector{
    friend class Triangle;
    friend class Plane;
    friend class Sphere;
    friend class Surface;
    friend class BVHNode;
    friend class Ray;
    float x;
    float y;
    float z;
    
public:
    void setPosition(float x, float y, float z);
    void setPosition(Vector a);
    void setDirection(float x, float y, float z);
    void setDirection(Vector a);
    Vector getPosition();
    float getX();
    float getY();
    float getZ();
    Vector(){};
    Vector(float x, float y, float z){
        this->setPosition(x, y, z);
    }
    Vector &operator+= (Vector v) {
        x = x + v.getX();
        y = y + v.getY();
        z = z + v.getZ();
        
        return *this;
    }
    
    Vector operator+ (Vector v) {
        return Vector (x+v.getX(), y+v.getY(), z+v.getZ());
    }
    
    Vector operator- (Vector v) {
        return Vector (x-v.getX(), y-v.getY(), z-v.getZ());
    }
    
    Vector operator* (const float scale) {
        return Vector (scale * x,scale * y,scale * z);
    }
    
    Vector operator*= (const float scale){
        x = x*scale;
        y = y*scale;
        z = z*scale;
        return *this;
    }
    
    float norm(){
        float norm =sqrtf(x*x+y*y+z*z);
        return norm;
    }
    void normalize(){
        float norm = this->norm();
        *this = *this*(1/norm);
    }
};


#endif /* vector_hpp */
