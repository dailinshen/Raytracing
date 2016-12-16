#ifndef PARSE_H
#define PARSE_H

#include <iostream>
#include <vector>

#include "camera.h"

class Surface;
class Material;
class Light;


//
// Basic parser for the scene files:
//
class Parser {
public:
    virtual void parse (
                        const char *file,
                        std::vector< Surface * > &surfaceVector,
                        std::vector< Light * > &lightVector,
                        std::vector< Material * > &materialVector,
                        Camera &cam);
    
};

#endif
