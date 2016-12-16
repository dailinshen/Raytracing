//
//  color.hpp
//  hw1.5_ds3420
//
//  Created by lindashen on 11/17/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#ifndef color_hpp
#define color_hpp

#include <stdio.h>

class Color{
    friend class AreaLight;
    float r;
    float g;
    float b;
    public :
    void setRGB(float r, float g, float b);
    float getR();
    float getG();
    float getB();
    
};




#endif /* color_hpp */
