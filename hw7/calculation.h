//
//  calculation.hpp
//  hw1.5_ds3420
//
//  Created by lindashen on 11/17/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#ifndef calculation_hpp
#define calculation_hpp

#include <stdio.h>
#include <math.h>

#include "vector.h"
class Calculation{
public:
    float dot_product(Vector a, Vector b);
    Vector addThree(Vector a, Vector b, Vector c);
    Vector minus(Vector a, Vector b);
    Vector cross_product(Vector a, Vector b);
    
};


#endif /* calculation_hpp */
