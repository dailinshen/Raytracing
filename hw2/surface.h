//
//  surface.hpp
//  hw2
//
//  Created by lindashen on 10/13/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#ifndef surface_hpp
#define surface_hpp

#include <stdio.h>
#include "ray.h"
class Surface {
public:
    Surface () {material = 0;}
    virtual double intersect (Ray &) const;
    void set_Material (int index) {
        material = index;
    }
    int made_up_of_material () {
        return material;
    }
private:
    int material;
};


#endif /* surface_hpp */
