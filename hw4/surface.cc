//
//  surface.cpp
//  hw3
//
//  Created by lindashen on 10/18/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#include "surface.h"

bool Surface::intersect (const Ray &, double &,Point &,Vector &, bool &) const
{
    std::cout << "error: surface::intersect should not be called - it's virtual!"
    << std::endl;
    
    return false;
}
