//
//  sphere.hpp
//  hw2
//
//  Created by lindashen on 10/13/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#ifndef sphere_hpp
#define sphere_hpp

#include <iostream>
#include "surface.h"
#include "ray.h"

class Sphere: public Surface {
public:
    Sphere(Point position, double radius) {
        center_ = position;
        radius_ = radius;
    }
    ~Sphere();
    virtual double intersect (Ray &) const;
private:
    Point center_;
    double radius_;
};
#endif /* sphere_hpp */
