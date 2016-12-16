//
//  ray.hpp
//  hw1_ds3420
//
//  Created by lindashen on 10/1/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#ifndef ray_hpp
#define ray_hpp

#include <stdio.h>
#include <iostream>

#include "point.h"
#include "vector.h"
#include "surface.h"
#include "intersection.h"

class Ray {
    
public:
    friend class Sphere;
    friend class Plane;
    
    Ray(const Point &point, const Vector &vector);
    Ray(float origin_x = 0, float origin_y = 0, float origin_z = 0, float direction_x = 0, float direction_y = 0, float direction_z = 0);
    inline const Point &point() const {
        return origin;
    };
    inline const Vector &direcion() const {
        return dir;
    };
    inline const Intersection &intersection() const {
        return intersec_;
    };
    inline bool intersected() const {
        return intersecting;
    };
    inline void intersection(Intersection &&intersection) {
        intersecting = true;
        intersec_ = intersection;
    };
    
    bool update_t(float t) const;

private:
    Point origin;
    Vector dir;
    bool intersecting;
    Intersection intersec_;
};

std::ostream &operator<<(std::ostream &os, const Ray &ray);

#endif /* ray_hpp */
