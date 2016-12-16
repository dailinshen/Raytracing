//
//  material.hpp
//  hw3
//
//  Created by lindashen on 10/18/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#ifndef MATERIAL_H_
#define MATERIAL_H_
#include "vector.h"
#include "point.h"
class Material {
    
public:
    
    Material () {}
    
    Material (Vector &k_d, Vector &k_s, Vector &k_r, double p) {
        kd_ = k_d; ks_ = k_s; kr_ = k_r; p_ =p;
    }

    // compute phong shading
    Vector blinn_phong (const Vector &L, const Vector &e, const Vector &N, const Vector &L_e) const; //
    
private:
    
    Vector kd_;     // diffuse coefficient
    Vector ks_;     // specular coefficient
    Vector kr_;  // total reflection coefficient
    
    double p_;             // phong exponent
    
};

#endif
