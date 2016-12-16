//
//  plane.hpp
//  hw1_ds3420
//
//  Created by lindashen on 10/1/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#ifndef plane_hpp
#define plane_hpp

#include <stdio.h>
#include <sstream>
#include "surface.h"
#include "vector.h"

class Plane : public Surface {
public:
    Plane(const Vector &n, const float distance = 0);
    Plane(float n_x = 0, float n_y = 0, float n_z = 0, float distance = 0);
    inline const Vector &normal() const {
        return normal_;
    };
    inline const float distance() const {
        return d_;
    };
    Plane &normal(const Vector &n);
    Plane &normal(float x, float y, float z);
    Plane &distance(float d);
    
    std::string to_string() const;
    
    bool ray_intersection(Ray &ray, int id) const;
private:
    Vector normal_;
    float d_;   // distance to origin
};
#endif /* plane_hpp */
