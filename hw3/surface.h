//
//  surface.hpp
//  hw3
//
//  Created by lindashen on 10/18/16.
//  Copyright © 2016 lindashen. All rights reserved.
//
#ifndef SURFACE_H_
#define SURFACE_H_


#include <iostream>

#include "ray.h"

class Surface {
    
public:
    
    // default constructor give it the default material
    Surface () {
        materialIndex_ = 0;
    }
    inline void setMaterialIndex (int indx) {
        materialIndex_ = indx;
    };
    inline int materialIndex () {
        return materialIndex_;
    };

    virtual bool intersect (const Ray &, double &, Point &, Vector &) const;

protected:
    int materialIndex_;
    
};



#endif
