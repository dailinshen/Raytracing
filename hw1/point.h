//
//  point.hpp
//  hw1_ds3420
//
//  Created by lindashen on 10/1/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#ifndef point_hpp
#define point_hpp

#include <stdio.h>

class Point {
public:
    Point(float x = 0, float y = 0, float z = 0);
    inline float x() const {
        return xx;
    };
    inline float y() const {
        return yy;
    };
    inline float z() const {
        return zz;
    };
    inline void x(float x) {
        xx = x;
    };
    inline void y(float y) {
        yy = y;
    };
    inline void z(float z) {
        zz = z;
    };
private:
    float xx, yy, zz;
};

#endif /* point_hpp */
