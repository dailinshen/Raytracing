//
//  material.hpp
//  hw1_ds3420
//
//  Created by lindashen on 10/2/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#ifndef material_hpp
#define material_hpp

#include <stdio.h>
#include <sstream>
#include "vector.h"
class Material {
public:
    Material(float dr_ = 0, float dg_ = 0, float db_ = 0, float sr_ = 0, float sg_ = 0, float sb_ = 0,
             float r_ = 0, float ir_ = 0, float ig_ = 0, float ib_ = 0): d{dr_, dg_, db_}, s{sr_, sg_, sb_}, r{r_}, i{ir_, ig_, ib_} {}
    inline const Vector &diffuse() const {
        return d;
    };
    inline const Vector &specular() const {
        return s;
    };
    inline const Vector &ideal_specular() const {
        return i;
    };
    inline float roughness() const {
        return r;
    };
private:
    Vector d, s, i;
    
    float r;
};

#endif /* material_hpp */
