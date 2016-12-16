//
//  plane.cpp
//  hw2
//
//  Created by lindashen on 10/13/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#include "plane.h"

double Plane::intersect (Ray &ray) const {

    Point p0 = ray.position();
    Vector p0_(p0.x(), p0.y(), p0.z());
    Vector dd = ray.direction();
    float up = p0_.dot(normal_);
    float down = dd.dot(normal_);
    if (down == 0) {
        return 0.0;
    } else {
        float t;
        t = - ( up - distance_) / down;
        if (t <= 0) {
            return 0.0;
        }
        Vector inter_norm = normal_;
        Point inter_point = ray.position() + ray.direction() * t;
        ray.intersection(Intersection(inter_norm, inter_point));
        return t;
    }

}
