//
//  plane.hpp
//  hw1.5_ds3420
//
//  Created by lindashen on 11/17/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#ifndef plane_hpp
#define plane_hpp

#include <stdio.h>

#include "surface.h"
#include "material.h"
#include "calculation.h"
#include "ray.h"


class Plane: public Calculation, public Surface{
    Ray normal;
    float d;
public:
    Plane(){};
    virtual ~Plane(){};
    Plane(float x, float y, float z, float d);
    
    float intersection(Ray r, int option);
    Ray getRayToLight(Point intersect, Light light);
    Ray getNormalAtIntersect(Point Intersect, int option);
    
    Ray getSurfaceNormal();
    float getSurfaceD();
    
};


#endif /* plane_hpp */
