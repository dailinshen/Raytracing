//
//  sphere.cpp
//  hw2
//
//  Created by lindashen on 10/13/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#include "sphere.h"
double Sphere::intersect(Ray &ray) const {
    Vector e_c = ray.position() - center_;
    Vector d = ray.direction();
    
    double d_d = d.dot(d);
    
    double term_1 = d.dot(e_c);
    term_1 *= term_1;
    
    double term_2 = e_c.dot(e_c);
    term_2 -= (radius_ * radius_);
    term_2 *= d_d;
    
    double term = term_1 - term_2;
    
    // complex root - missed the sphere:
    if (term < 0.0) return 0.0;
    
    double t1 = d.dot(e_c) * (-1) + sqrt(term);
    double t2 = d.dot(e_c) * (-1) - sqrt(term);
    
    double t = t1 < t2 ? t1 : t2;
    if (t <= 0) {
        return 0.0;
    } else {
        Point inter_point = ray.position() + ray.direction() * t;
        Vector inter_norm = inter_point - center_;
        inter_norm.normalize();
//        Intersection(inter_norm, inter_point);
        ray.intersection(Intersection(inter_norm, inter_point));
        return t;
    }
    
    // otherwise, we hit it (either once or twice)
    
    // if you want to know how far along the ray the intersection
    // is, you'll need to fill out the rest of the alg, determine
    // the one or two intersections, and return or store the closest one.

    
}
