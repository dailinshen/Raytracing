//
//  surface.cpp
//  hw2
//
//  Created by lindashen on 10/13/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#include "surface.h"

double Surface::intersect (
                         Ray &r
                         ) const
{
    std::cout << "error: surface::intersect should not be called - it's virtual!"
    << std::endl;
    
    return 0.0;
}
