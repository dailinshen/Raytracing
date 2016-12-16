//
//  ray.cpp
//  hw1_ds3420
//
//  Created by lindashen on 10/1/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#include "ray.h"


Ray::Ray(const Point &point, const Vector &vector) : origin{point}, dir{vector}, intersecting{false}, intersec_{} {}

Ray::Ray(float origin_x, float origin_y, float origin_z, float direction_x, float direction_y, float direction_z) : origin{origin_x, origin_y, origin_z}, dir{direction_x, direction_y, direction_z}, intersecting{false}, intersec_{} {}
std::ostream &operator<<(std::ostream &os, const Ray &ray) {
    os << "Ray:\n";
    os << "\teyepoint :" << ray.point().x() << ray.point().y() << ray.point().z() << "\n";
    os << "\tdirection :" << ray.direcion().x() << ray.direcion().y() << ray.direcion().z() << std::endl;
    return os;
}

bool Ray::update_t(float t) const {
    if (intersecting) {
        if (t > 0.00005f && t < intersec_.t())
            return true;
        else
            return false;
    } else {
        if (t > 0.00005f)
            return true;
        else
            return false;
    }
}
