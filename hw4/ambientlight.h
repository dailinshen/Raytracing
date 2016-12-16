//
//  ambientlight.hpp
//  hw3
//
//  Created by lindashen on 10/26/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#ifndef ambientlight_hpp
#define ambientlight_hpp

#include <stdio.h>
#include "light.h"
class AmbientLight : public Light {
public:
    
    AmbientLight () {}
    AmbientLight (const Vector &spd) {
        spd_ = spd;
    }
};
#endif /* ambientlight_hpp */
