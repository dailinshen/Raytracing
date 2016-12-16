//
//  ray.hpp
//  hw2
//
//  Created by lindashen on 10/13/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#ifndef ray_hpp
#define ray_hpp

#include <stdio.h>
#include "vector.h"
#include "point.h"
#include "intersection.h"
class Ray {
public:
    friend class Sphere;
    friend class Plane;
    Ray() {}
    Ray(const Point &point, const Vector &direction) {
        position_ = point;
        direction_ = direction;
    }
    void setDirection(const Vector direction) {
        direction_ = direction;
    }
    void setPosition(const Point position) {
        position_ = position;
    }
    
    inline const Intersection &intersection() const {
        return intersection_;
    }
    
    inline void intersection(Intersection &&intersect) {
        intersection_ = intersect;
    }
    
    Vector direction() const {
        return direction_;
    }
    Point position() const {
        return position_;
    }
private:
    Point position_;
    Vector direction_;
    Intersection intersection_;
};

#endif /* ray_hpp */
