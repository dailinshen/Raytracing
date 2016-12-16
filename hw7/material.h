//
//  material.hpp
//  hw1.5_ds3420
//
//  Created by lindashen on 11/17/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#ifndef material_hpp
#define material_hpp

#include <stdio.h>

#include "color.h"
class Material {
    Color diffuse;
    Color specular;
    Color reflective;
    float roughness;
    
    public :
    bool isReflective;
    void setDiffuse(float d_r, float d_g, float d_b);
    void setSpecular(float d_r, float d_g, float d_b);
    void setReflective(float d_r, float d_g, float d_b);
    void setRoughness(float r);
    Color getDiffuse();
    Color getReflective();
    Color getSpecular();
    float getRoughness();
};




#endif /* material_hpp */
