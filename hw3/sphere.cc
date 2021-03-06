//
//  sphere.cpp
//  hw3
//
//  Created by lindashen on 10/18/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#include "sphere.h"

bool Sphere::intersect (const Ray &r, double &t, Point &ipoint, Vector &normal) const
{
    
    // straight out of the text: p 77
    
    // these first two terms are used a lot, so compute them once:
    
    // (e - c):
    Vector e_c = r.getOrigin () - center_;
    
    // D . D
    Vector d = r.getDir ();
    double d_dot_d = d.dot(d);
    
    
    // now compute the two terms under the square root sign:
    
    double discrim_term1 = d.dot(e_c);
    discrim_term1 *= discrim_term1; // square it.
    
    double discrim_term2 = e_c.dot(e_c);
    discrim_term2 -= (radius_ * radius_);
    discrim_term2 *= d_dot_d;
    
    
    // this is what's under the square root sign:
    double discriminant = discrim_term1 - discrim_term2;
    
    // complex root - missed the sphere:
    if (discriminant < 0.0) return false;
    
    // otherwise, we hit it (either once or twice) - and discriminant is >= 0
    
    discriminant = sqrt (discriminant);
    
    double quadratic_form = -1 * d.dot(e_c);
    
    t = (quadratic_form + discriminant) / d_dot_d;
    
    if (discriminant > 0.) {
        double temp_t = (quadratic_form - discriminant) / d_dot_d;
        if (temp_t > 0 and (t <=0 or temp_t < t)) {
            t = temp_t;
        }
    }
    if (t <= 0) return false;    // intersections are behind the camera.
    
    
    // otherwise, t is the parameter of the closest intersection > 0.
    
    Vector offset = r.getDir () * t;
    ipoint = r.getOrigin () + offset;
    
    normal = ipoint - center_;
    normal = normal * (1.0 / radius_);
    
    return true;
    
}

