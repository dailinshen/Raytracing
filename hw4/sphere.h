//
//  sphere.hpp
//  hw3
//
//  Created by lindashen on 10/18/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#ifndef SPHERE_H_
#define SPHERE_H_

#include <iostream>

#include "ray.h"
#include "surface.h"

class Sphere : public Surface {

public:
    Sphere (Point pos, double r) {
        center_ = pos; radius_ = r;
    }
    virtual ~Sphere () {}
    
    virtual bool intersect (const Ray &r, double &t, Point &ipoint, Vector &normal, bool &isSphere) const;
    
private:
    
    Point center_;
    double  radius_;
};

#endif
