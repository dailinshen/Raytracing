//
//  vector.hpp
//  hw2
//
//  Created by lindashen on 10/13/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#ifndef vector_hpp
#define vector_hpp

#include <stdio.h>

#include <iostream>
#include <cmath>

#include "point.h"
    
    /**
     * The Vector class stores RBG values and overloads operations for easy manipulation on RGB vectors.
     * The public member functions have obvious meanings as their names indicate.
     */
class Vector {
public:
    friend class Triangle;
        
    friend class Sphere;
        
    friend class Plane;
    
    friend class BBox;
    
    Vector(float x = 0, float y = 0, float z = 0);
    
    inline float dot(const Vector &vector) const {
        return _x * vector._x + _y * vector._y + _z * vector._z;
    }
    
    Vector cross(const Vector &) const;
        
    inline void normalize() {
        *this /= magnitude();
    }
        
    inline float magnitude() const {
        return sqrtf(_x * _x + _y * _y + _z * _z);
    }
        
    Vector &operator+=(const Vector &);
        
    Vector &operator-=(const Vector &);
        
    Vector &operator*=(float scalar);
        
    Vector &operator/=(float scalar);
        
    inline float x() const {
        return _x;
    }
        
    inline float y() const {
        return _y;
    }
        
    inline float z() const {
        return _z;
    }
    
    inline void x(float _x) {
        Vector::_x = _x;
    }
        
    inline void y(float _y) {
        Vector::_y = _y;
    }
        
    inline void z(float _z) {
        Vector::_z = _z;
    }
    
    friend std::istream &operator>>(std::istream &is, Vector &v) {
        return is>>v._x>>v._y>>v._z;
    }
    
    friend std::ostream &operator<<(std::ostream &os, Vector &v) {
        return os<<"<"<<v._x<<","<<v._y<<","<<v._z<<">";
    }
    
private:
    float _x, _y, _z;
};
    
Vector operator+(const Vector &lhs, const Vector &rhs);
    
Vector operator-(const Vector &lhs, const Vector &rhs);
    
Vector operator*(const Vector &lhs, float scalar);
    
Vector operator*(const Vector &lhs, const Vector &rhs);
    
Vector operator/(const Vector &lhs, float scalar);
    
inline Vector operator-(const Point &lhs, const Point &rhs) {
    return std::move(Vector(lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() - rhs.z()));
}
    
Point operator+(const Point &point, const Vector &vector);
    
std::ostream &operator<<(std::ostream &os, const Vector &vector);
    
Vector bisector(const Vector &lhs, const Vector &rhs);


#endif /* vector_hpp */
