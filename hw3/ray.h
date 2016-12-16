//
//  ray.hpp
//  hw3
//
//  Created by lindashen on 10/18/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#ifndef RAY_H_
#define RAY_H_

#include "vector.h"
#include "point.h"

class Ray {
    
public:
    
    Ray () {}
    Ray (const Point &p, const Vector &d) {
        pos = p;
        dir = d;
    }
    // Get and set functions, for the direction and origin:
    inline Vector getDir () const {
        return dir;
    };
    inline Point getOrigin () const {
        return pos;
    };
    inline void setDir (const Vector dirr)   {
        dir = dirr;
    };
    inline void setOrigin (const Point pnt) {
        pos = pnt;
    };
    
private:
    Vector    dir; // direction of ray
    Point     pos; // origin of ray
    
};

#endif
