//
//  light.hpp
//  hw3
//
//  Created by lindashen on 10/18/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#ifndef LIGHT_H_
#define LIGHT_H_


#include "vector.h"
#include "point.h"

class Light {
    
public:
    
    Light () { }
    virtual Vector spd () = 0;    // return the spectral power distribution
    Point position () const { return position_; }
    
protected:
    Point position_;
    
};

#endif
