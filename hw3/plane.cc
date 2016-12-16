//
//  plane.cpp
//  hw3
//
//  Created by lindashen on 10/18/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#include "plane.h"


Plane::Plane (const Vector &normal, const double d) {
    N_ = normal;
    d_ = d;
}

bool Plane::intersect (const Ray &r, double &t, Point &ipoint, Vector &normal) const {
    
    
    // t = - (ray.p0 dot N - d) / ray.dir dot N
    
    double denom = r.getDir().dot(N_);
    
    if (denom == 0.) {
        return false;
    }
    
    const Point r_orig = r.getOrigin();
    
    Vector my_orig_vec (r_orig.x(), r_orig.y(), r_orig.z());
    double ray_point_dot_n = my_orig_vec.dot(N_);
    
    t = -1. * (ray_point_dot_n - d_) / denom;
    
    if (t <= 0) return false;
    
    ipoint = r_orig + r.getDir()*t;
    
    normal = N_;
    
    return true;
    
}
