//
//  camera.hpp
//  hw2
//
//  Created by lindashen on 10/13/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#ifndef camera_hpp
#define camera_hpp

#include <stdio.h>
#include <vector>
#include <ImfRgbaFile.h>
#include <ImfStringAttribute.h>
#include <ImfMatrixAttribute.h>
#include <ImfArray.h>

#include "ray.h"
#include "material.h"
#include "light.h"
using namespace Imf;

class Surface;
class Camera {
    
public:
    
    void    init (
                  Point pos,
                  Vector dir,
                  double d,
                  double iw,
                  double ih,
                  int pw,
                  int ph);
    
    Ray     generateRay (const int i, const int j);
    void    renderScene (std::vector< Surface * > &surfaces,
                         std::vector< Light * > &lights,
                         std::vector< Material * > &materials);
    void    writeImage (const char *sceneFile);
    Vector blinn_phong (Vector &kd, Vector &intensity, Vector &n, Vector &l, Vector &ks, Vector &h, double p);
    void    setPixel (int pix_x, int pix_y, float r, float g, float b) {
        Rgba &px = pixelBuffer_[pix_y][pix_x];
        px.r = r;
        px.g = g;
        px.b = b;
        px.a = 1.0;
    }
    
private:
    
    // right-handed coordinate system:
    Vector   u_;  // u goes to the "right" with respect to the image plane
    Vector   v_;  // v goes "up" with respect to the image plane
    Vector   w_;  // remember: points in OPPOSITE the viewing direction!
    
    Point eye_;   // position of camera, & center of projection
    
    double   image_width_;
    double   image_height_;
    
    double   focal_length_;
    
    int     pixels_width_;
    int     pixels_height_;
    
    Array2D<Rgba>    pixelBuffer_;  // the image we are rendering
    
};
#endif /* camera_hpp */
