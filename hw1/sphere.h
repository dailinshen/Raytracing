//
//  sphere.hpp
//  hw1_ds3420
//
//  Created by lindashen on 10/1/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#ifndef sphere_hpp
#define sphere_hpp

#include <stdio.h>
#include <sstream>
#include "surface.h"
#include "vector.h"
#include "material.h"

class Sphere : public Surface{
public:
    
    //Constructor
    Sphere(const Point &origin, float radius);
    Sphere(float origin_x = 0, float origin_y = 0, float origin_z = 0, float radius = 0);
    
    inline const Point &origin() const {
        return O;
    };
    inline float radius() const {
        return r;
    };
    
    std::string to_string() const;
    
    Sphere &origin_position(const Point &origin);
    Sphere &origin_position(float x, float y, float z);
    Sphere &radius(float r_);
    Sphere &material_composition(const Material &material);
    
    // Whether has intersection or not
    bool ray_intersection(Ray &ray, int id) const;
    
private:
    Point O;  // origin
    float r;  // radius
    
};

#endif /* sphere_hpp */
