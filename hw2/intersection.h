//
//  intersection.hpp
//  hw2
//
//  Created by lindashen on 10/13/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#ifndef intersection_hpp
#define intersection_hpp

#include <stdio.h>
#include "point.h"
#include "vector.h"

class Intersection {
public:
    Intersection() {}
    Intersection(Vector norm, Point point) {
        norm_ = norm;
        point_ = point;
    }
    inline const Point &point() const {
        return point_;
    }
    inline const Vector &norm() const {
        return norm_;
    }
private:
    Vector norm_;
    Point point_;
};

#endif /* intersection_hpp */
