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
    virtual ~Light (){}
    virtual Vector spd () {
        return spd_;
    }    // return the spectral power distribution
    virtual Point position () const {
        return Point{0., 0., 0.};;
    }
    
protected:
    Vector spd_;
    
};

#endif
