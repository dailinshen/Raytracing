//
//  parser.hpp
//  hw2
//
//  Created by lindashen on 10/13/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#ifndef parser_hpp
#define parser_hpp

#include <stdio.h>

#include <iostream>
#include <vector>
#include "light.h"
#include "camera.h"

//
// Basic parser for the scene files:
//
class Parser {
public:
    virtual void parse(
                       const char *file,
                       std::vector< Surface * > &surfaceVector,
                       std::vector< Light *> &lightVector,
                       std::vector< Material * > &materialVector,
                       Camera &cam);
};


#endif /* parser_hpp */
