//
//  sphere.hpp
//  hw1.5_ds3420
//
//  Created by lindashen on 11/17/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#ifndef sphere_hpp
#define sphere_hpp

#include <stdio.h>
#include "point.h"
#include "surface.h"
#include "camera.h"
#include "calculation.h"
#include "ray.h"
#include "light.h"

class Sphere : public Calculation, public Surface{
    Point origin;
    float radius;
public:
    Sphere();
    Sphere(float x, float y, float z, float r);
    float intersection(Ray& r);
    void setPosition(float x, float y, float z);
    void setRadius(float r);
    std::vector<Ray* > getRayToLight(Point& intersect, Light *light, int shadowNum);
    Ray getNormalAtIntersect(Point& intersect);
    Point getPosition();
    float getRadius();
    
};


#endif /* sphere_hpp */
