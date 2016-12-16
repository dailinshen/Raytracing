//
//  plane.cpp
//  hw1_ds3420
//
//  Created by lindashen on 10/1/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#include "plane.h"

Plane &Plane::normal(const Vector &n) {
    normal_ = n;
    return *this;
}
Plane &Plane::normal(float x, float y, float z) {
    normal_.x(x), normal_.y(y), normal_.z(z);
    return *this;
}
Plane &Plane::distance(float d) {
    d_ = d;
    return *this;
}
std::string Plane::to_string() const {
    std::stringstream os;
    os << "Plane:\n";
    os << "\tnormal: " << &normal_ << "\n";
    os << "\tscalar: " << d_ << std::flush;
    return os.str();
}
bool Plane::ray_intersection(Ray &ray, int id) const {
    Point p0 = ray.origin;
    Vector p0_(p0.x(), p0.y(), p0.z());
    Vector dd = ray.dir;
    float up = - p0_.dot_product(normal_);
    float down = dd.dot_product(normal_);
    if (down == 0) {
        return false;
    } else {
        float t;
        t = - ( up + d_) / down;
        if (t == 0) {
            return false;
        }
        if (ray.update_t(t)) {
            Point point = ray.origin + ray.dir * t;
            ray.intersection(Intersection(t, point, normal_,id));
        }
        return true;
    }
}
