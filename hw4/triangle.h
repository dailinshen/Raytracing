//
//  triangle.hpp
//  hw3
//
//  Created by lindashen on 10/18/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#ifndef triangle_hpp
#define triangle_hpp

#include <stdio.h>
#include "vector.h"
#include "point.h"
#include "surface.h"

class Triangle : public Surface {
public:
    Triangle() {}
    Triangle( Point &a, Point &b, Point &c) {
        pa_ = a, pb_ = b, pc_ = c;
        normal_ = (pb_ - pa_).cross(pc_ - pa_);
//        normal_.crossProduct(pb_ - pa_, pc_ - pa_);
        normal_.normalize();
    }
    virtual ~Triangle() {}
    
    virtual bool intersect (const Ray &ray,
                            double &t,
                            Point &ipoint,
                            Vector &normal,
                            bool &isSphere) const;
private:
    // These points are in counterclockwise direction.
    Point pa_, pb_, pc_;
    Vector normal_;
};
#endif /* triangle_hpp */
