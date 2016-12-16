//
//  point.hpp
//  hw1.5_ds3420
//
//  Created by lindashen on 11/17/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#ifndef point_hpp
#define point_hpp

#include <stdio.h>


#include "vector.h"

class Point :public Vector{
public:
    void setPosition(Vector a);
    void setPosition(float a, float b, float c);
    
};


#endif /* point_hpp */
