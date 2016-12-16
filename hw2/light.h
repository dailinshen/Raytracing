//
//  light.hpp
//  hw2
//
//  Created by lindashen on 10/13/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#ifndef light_hpp
#define light_hpp

#include <stdio.h>
#include "vector.h"


class Light {
public:
    
    virtual ~Light() {};
    
    virtual Vector &color() = 0;
    virtual Point &position() = 0;
    
};
#endif /* light_hpp */
