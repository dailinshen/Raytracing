//
//  readscene.h
//  hw1.5_ds3420
//
//  Created by lindashen on 11/17/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#ifndef readscene_h
#define readscene_h


#include <ImfRgbaFile.h>
#include <ImfStringAttribute.h>
#include <ImfMatrixAttribute.h>
#include <ImfArray.h>
#include <cmath>
#include <cstdlib>
#include <iostream>    // input output
#include <fstream>
#include <cstring>
#include <string>
#include <math.h>
#include <vector>
#include "point.h"
#include "camera.h"
#include "ray.h"
#include "sphere.h"
#include "material.h"
#include "light.h"
#include "calculation.h"
#include "plane.h"
#include "triangle.h"
#include "surface.h"
#include "BVHNode.h"

using namespace std;
using namespace Imf;
using namespace Imath;
class Readscene: public Calculation{
    
public:
    void writeRgba (const char fileName[], const Rgba *pixels, int width, int height);
    void parseSceneFile (char *filnam, char *output, char *primaryRay, char *shadowRay);
    Imf::Rgba rec(Ray& r, float mint_t, float max_t, int type, int recurse_limit,int lightIndex, int shadowRayNum, Ray& surfaceNormal);
    void read_wavefront_file (const char *file, std::vector< int > &tris, std::vector< float > &verts);
    
    
};


#endif /* readscene_h */
