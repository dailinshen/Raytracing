//
//  point.hpp
//  hw2
//
//  Created by lindashen on 10/13/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#ifndef point_hpp
#define point_hpp

#include <stdio.h>
#include <iostream>

class Point {
public:
    friend class Triangle;
    
    friend class Sphere;
    
    friend class Plane;
    
    friend class BBox;
    
    inline float x() const {
        return _x;
    }
    
    inline float y() const {
        return _y;
    }
    
    inline float z() const {
        return _z;
    }
    
    inline void x(float x) {
        _x = x;
    }
    
    inline void y(float y) {
        _y = y;
    }
    
    inline void z(float z) {
        _z = z;
    }
    
    Point(float x = 0, float y = 0, float z = 0);
    friend  std::istream &operator>>(std::istream &is, Point &p) {
        return is >> p._x >> p._y >> p._z;
    }
    
    friend std::ostream &operator<<(std::ostream &os, Point &p) {
        return os<<"<"<<p._x<<","<<p._y<<","<<p._z<<">";
    }
private:
    float _x, _y, _z;
};

std::ostream &operator<<(std::ostream &, const Point &);




#endif /* point_hpp */
