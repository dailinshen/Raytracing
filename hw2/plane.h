//
//  plane.hpp
//  hw2
//
//  Created by lindashen on 10/13/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#ifndef plane_hpp
#define plane_hpp

#include <stdio.h>
#include <sstream>
#include "surface.h"
#include "vector.h"

class Plane: public Surface {
public:
    Plane(Vector normmal, double distance) {
        normal_ = normmal;
        distance_ = distance;
    }
    ~Plane();
    virtual double intersect (Ray &) const;
private:
    Vector normal_;
    double distance_;
};
#endif /* plane_hpp */
