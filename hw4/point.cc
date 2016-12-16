//
//  point.cpp
//  hw3
//
//  Created by lindashen on 10/18/16.
//  Copyright © 2016 lindashen. All rights reserved.
//
#include "point.h"
Point::Point(float x, float y, float z) : _x{x}, _y{y}, _z{z} { }

std::ostream &operator<<(std::ostream &os, const Point &p) {
    os << "Point: " << p.x() << " " << p.y() << " " << p.z() << std::flush;
    return os;
}
