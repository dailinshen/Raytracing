//
//  plane.hpp
//  hw3
//
//  Created by lindashen on 10/18/16.
//  Copyright © 2016 lindashen. All rights reserved.
//


#ifndef PLANE_H_
#define PLANE_H_

#include <iostream>

#include "ray.h"
#include "surface.h"

class Plane : public Surface {
    
    
public:
    Plane (const Vector &normal, const double d);
    ~Plane ();
    
    virtual bool intersect (const Ray &r,
                            double &t,
                            Point &ipoint,
                            Vector &normal) const;
    
private:
    
    Vector    N_;
    double      d_;
    
};


#endif
