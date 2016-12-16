//
//  pointlight.hpp
//  hw3
//
//  Created by lindashen on 10/19/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#ifndef pointlight_hpp
#define pointlight_hpp

#include <stdio.h>
#include "light.h"
class PointLight : public Light {
    
public:
    
    PointLight () {}
    PointLight (const Point &pos, const Vector &spd) {
        position_ = pos;
        spd_ = spd;
    }
    
    virtual Vector spd () {return spd_; }
    
private:
    
    Vector spd_;
    
};
#endif /* pointlight_hpp */
