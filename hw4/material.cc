//
//  material.cpp
//  hw3
//
//  Created by lindashen on 10/18/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#include "material.h"
Vector Material::blinn_phong(const Vector &L, const Vector &e, const Vector &N, const Vector &L_e) const {
    Vector R (0., 0., 0.); // the amount of light (color) returned along the ray
    
    double n_dot_l = N.dot(L);
    
    if (n_dot_l > 0.) {
        Vector diff (kd_.x() * L_e.x() * n_dot_l, kd_.y() * L_e.y() * n_dot_l, kd_.z() * L_e.z() * n_dot_l);
        R += diff;
    }
    
    // compute the specular component:
    Vector half_vec = e;
    half_vec += L;
    
    // check to make sure the vector towards the light, and the
    // vector towards the viewer, are not opposite (if they are
    // normalize() will fail)
    if (half_vec.magnitude() > 0.) {
        
        half_vec.normalize ();
        
        double n_dot_h = N.dot(half_vec);
        
        if (n_dot_h > 0.) {
            n_dot_h = pow (n_dot_h, p_);
            Vector spec (ks_.x() * L_e.x() * n_dot_h, ks_.y() * L_e.y() * n_dot_h, ks_.z() * L_e.z() * n_dot_h);
            R += spec;
        }
    }
    return R;
    
}

