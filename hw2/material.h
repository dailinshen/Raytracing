//
//  material.hpp
//  hw2
//
//  Created by lindashen on 10/13/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#ifndef material_hpp
#define material_hpp

#include <stdio.h>
#include "vector.h"

class Material {
public:
    Material(){}
    Material (Vector &kd, Vector &ks, Vector &kr, double exponent) {
        kd_ = kd;
        ks_ = ks;
        kr_ = kr;
        exponent_ = exponent;
    }
    Vector diffuse() {
        return kd_;
    }
    Vector specular() {
        return ks_;
    }
    Vector isreflective() {
        return kr_;
    }
    double exponent() {
        return exponent_;
    }
private:
    Vector kd_;
    Vector ks_;
    Vector kr_;
    double exponent_;
    
};
#endif /* material_hpp */
