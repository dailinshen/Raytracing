//
//  camera.hpp
//  hw1_ds3420
//
//  Created by lindashen on 10/1/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#ifndef camera_hpp
#define camera_hpp
#include <iostream>
#include <stdio.h>
#include <vector>
#include <ImfRgbaFile.h>
#include <ImfStringAttribute.h>
#include <ImfMatrixAttribute.h>
#include <ImfArray.h>

#include "point.h"
#include "vector.h"
#include "ray.h"
#include "surface.h"

using namespace std;
using namespace Imf;
using namespace Imath;
class Surface;
class Image;
class Camera {
public:
    Camera(const Point &e = Point(), float focal_length = 0, const Vector &dir_u = Vector(), const Vector &dir_v = Vector(), const Vector &dir_w = Vector(), int nx_ = 0, int ny_ = 0, float l_ = 0, float r_ = 0, float t_ = 0, float b_ = 0);
    
    void configuration(float e_x, float e_y, float e_z, float focal_length, float dx, float dy, float dz, int nx_, int ny_, float iw_, float ih_);
   
    // Project a pixel. Generate a ray and spot the pixel on the scene.
    Ray ray_generation(int i, int j);
    
    Camera &position(float x, float y, float z);
    Camera &position(const Point &point);
    
    Camera &focal_length(float d_length);
    
    Camera &direction(float x, float y, float z);
    Camera &direction(const Vector &vector);
    
    Camera &image_range(float iw, float ih);
    
    // Set the image range, the ny, and the ny
    Camera &image_pixels(int _nx, int _ny);
    
    // Rendering pixels.
    void render(std::vector<Surface *> &object);
    
    void writeRgba(const char fileName[], const Rgba *pixels) const;
    
    inline int width() const {
        return nx;
    };
    inline int height() const {
        return ny;
    };
    inline const Point &eye_pos() const {
        return eye;
    };
    
    inline char path(char *path_){
        _path = path_;
        return *_path;
    };

private:
    Point eye;
    
    float d;   //focal length
    
    Vector u;
    Vector v;
    Vector w;
    
    int nx;
    int ny;
    
    float l, r, t, b;   // or just w, h if film is centered.
    
    Array2D<Rgba> image;

    char *_path;
};

#endif /* camera_hpp */
