//
//  intersection.hpp
//  hw1_ds3420
//
//  Created by lindashen on 10/1/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#ifndef intersection_hpp
#define intersection_hpp

#include <stdio.h>
#include "point.h"
#include "vector.h"

class Intersection {
public:
    Intersection(): _id{-1} {}
    Intersection(float t_, const Point &point_, const Vector &normal_, int id): _t{t_}, _point{point_}, _normal{normal_}, _id{id} {}
    inline float t() const {
        return _t;
    };
    inline const Point &point() const {
        return _point;
    };
    inline const Vector &normal() const {
        return _normal;
    };
    inline int id() const {
        return _id;
    };
    
private:
    float _t;
    int _id;
    
    Point _point;
    Vector _normal;
};
#endif /* intersection_hpp */
