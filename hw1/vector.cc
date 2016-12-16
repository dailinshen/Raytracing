//
//  vector.cpp
//  hw1_ds3420
//
//  Created by lindashen on 10/1/16.
//  Copyright © 2016 lindashen. All rights reserved.
//
#include <iostream>
#include "vector.h"
using namespace std;

Vector::Vector(float x, float y, float z): xx{x}, yy{y}, zz{z} {}
Vector &Vector::operator+=(const Vector &vector) {
    xx += vector.xx;
    yy += vector.yy;
    zz += vector.zz;
    return *this;
}
Vector &Vector::operator-=(const Vector &vector) {
    xx -= vector.xx;
    yy -= vector.yy;
    zz -= vector.zz;
    return *this;
}
Vector &Vector::operator*=(float coefficient) {
    xx *= coefficient;
    yy *= coefficient;
    zz *= coefficient;
    return *this;
}
Vector &Vector::operator/=(float coefficient) {
    xx /= coefficient;
    yy /= coefficient;
    zz /= coefficient;
    return *this;
}
Vector Vector::cross_product(const Vector &vector) const {
    Vector temp;
    temp.xx = yy * vector.zz - zz * vector.yy;
    temp.yy = zz * vector.xx - xx * vector.zz;
    temp.zz = xx * vector.yy - yy * vector.xx;
    return std::move(temp);
}
Point operator+(const Point &point, const Vector &vector) {
    Point p{point};
    p.x(p.x() + vector.x());
    p.y(p.y() + vector.y());
    p.z(p.z() + vector.z());
    return std::move(p);
}
Vector operator+(const Vector &first, const Vector &second) {
    Vector vector{first};
    vector += second;
    return std::move(vector);
}
Vector operator-(const Vector &first, const Vector &second) {
    Vector vector{first};
    vector -= second;
    return std::move(vector);
}
Vector operator-(const Point &first, const Point &second) {
    Vector temp;
    temp.x(first.x() - second.x());
    temp.y(first.y() - second.y());
    temp.z(first.z() - second.z());
    return std::move(temp);
}
Vector operator*(const Vector &first, const Vector &second) {
    Vector vector{first};
    vector.x(first.x() * second.y());
    return std::move(vector);
}
Vector operator*(const Vector &first, float coefficient) {
    Vector vector{first};
    vector *= coefficient;
    return std::move(vector);
}
Vector operator/(const Vector &first, float coefficient) {
    Vector vector{first};
    vector /= coefficient;
    return std::move(vector);
}
