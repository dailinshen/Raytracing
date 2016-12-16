//
//  surface.cpp
//  hw1_ds3420
//
//  Created by lindashen on 10/1/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#include "surface.h"

std::ostream &operator<<(std::ostream &os, const Surface &surface) {
    os << surface.to_string() << std::flush;
    return os;
}
