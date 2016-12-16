//
//  vector.hpp
//  hw1_ds3420
//
//  Created by lindashen on 10/1/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#ifndef vector_hpp
#define vector_hpp

#include <stdio.h>
#include <math.h>
#include "point.h"

class Vector {
public:
    Vector(float x = 0, float y = 0, float z = 0);
    Vector &operator+=(const Vector &);
    Vector &operator-=(const Vector &);
    Vector &operator*=(float coefficient);
    Vector &operator/=(float coefficient);
    Vector cross_product(const Vector &vector) const;
    inline float dot_product(const Vector &vector) const {
        return xx * vector.xx + yy * vector.yy + zz * vector.zz;
    };
    inline float magnitude() const {
        return sqrtf(xx * xx + yy * yy + zz * zz);
    };
    inline void normalization() {
        *this /= magnitude();
    };
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
        Vector::xx = x;
    };
    inline void y(float y) {
        Vector::yy = y;
    };
    inline void z(float z) {
        Vector::zz = z;
    };
private:
    float xx, yy, zz;
};

Point operator+(const Point &point, const Vector &vector);
Vector operator+(const Vector &first, const Vector &second);
Vector operator-(const Vector &first, const Vector &second);
Vector operator-(const Point &first, const Point &second);
Vector operator*(const Vector &first, float coefficient);
Vector operator*(const Vector &first, const Vector &second);
Vector operator/(const Vector &first, float coefficient);


#endif /* vector_hpp */
