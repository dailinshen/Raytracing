//
//  camera.cpp
//  hw1_ds3420
//
//  Created by lindashen on 10/1/16.
//  Copyright © 2016 lindashen. All rights reserved.
//
#include <ImfRgbaFile.h>
#include <ImfStringAttribute.h>
#include <ImfMatrixAttribute.h>
#include <ImfArray.h>

#include <iostream>
#include "material.h"
#include "camera.h"
#include "surface.h"
using namespace std;
using namespace Imf;
using namespace Imath;

using namespace std;

Camera::Camera(const Point &e, float focal_length, const Vector &dir_u, const Vector &dir_v, const Vector &dir_w, int nx_, int ny_, float l_, float r_, float t_, float b_): eye{e}, d{focal_length}, u{dir_u}, v{dir_v}, w{dir_w}, nx{nx_}, ny{ny_}, l{l_}, r{r_}, t{t_}, b{b_} {}

// Project on a world-space coordinator.
Ray Camera::ray_generation(int i,int j) {
    float u_ = l + (r - l) * (i + 0.5f) / nx;
    float v_ = b + (t - b) * (ny - j + 0.5f) / ny;    // start from the top left coner on the image
    
    Vector direction(u.x() * u_ + v.x() * v_ - w.x() * d, u.y() * u_ + v.y() * v_ - w.y() * d, u.z() * u_ + v.z() * v_ - w.z() * d);
    direction.normalization();    // normalize the direction vector.
    
    return std::move(Ray(eye, direction));
}
//void Camera::render(int i, int j, const std::vector<Surface *> &objects) {
void Camera::render(std::vector<Surface *> &object) {
    for (int i = 0; i < ny; ++i){
        for (int j = 0; j < nx; ++j){
            Rgba &rgba = image[i][j];
            Material m;
            Ray ray = ray_generation(j, i);
            for (int k = 0; k < object.size(); ++k) {
                object[k]->ray_intersection(ray, k);
            }
            const Intersection &intersect = ray.intersection();
            if (intersect.id() == -1) {
                rgba.r = 0, rgba.g = 0, rgba.b = 0, rgba.a = 1;
                continue;
            }
            m = object[intersect.id()]->material();
            Vector it = m.diffuse();
            rgba.r = it.x(), rgba.g = it.y(), rgba.b = it.z(), rgba.a = 1;
        }
    }

//    writeRgba("/Users/lindashen/Desktop/Raytra.exr", &image[0][0]);
    writeRgba(_path, &image[0][0]);

}

// Make a configuration of the camera.
void Camera::configuration(float e_x, float e_y, float e_z, float focal_length, float dx, float dy, float dz, int nx_, int ny_, float iw_, float ih_) {
    eye.x(e_x), eye.y(e_y), eye.z(e_z);
    
    d = focal_length;
    
    Vector dir{dx, dy, dz};
    
    u = dir.cross_product(Vector{0, 1, 0});
    v = u.cross_product(dir);
    w = dir * (-1);
    
    u.normalization();
    v.normalization();
    w.normalization();
        
    nx = nx_;
    ny = ny_;
    
    l =  - iw_ / 2, r = iw_ / 2, t = ih_ / 2, b = - ih_ / 2;
    
    image.resizeErase(ny, nx);
}
void Camera::writeRgba(const char fileName[], const Rgba *pixels) const {
    //Write an RGBA image using class RgbaOutputFile
    //
    // - open the file
    // - describe the memory layout of the pixels
    // - store the pixels in the file
    
    RgbaOutputFile file (fileName, nx, ny, WRITE_RGBA);
    file.setFrameBuffer(pixels, 1, nx);
    file.writePixels(ny);
}

Camera &Camera::position(float x, float y, float z){
    eye.x(x);
    eye.y(y);
    eye.z(z);
    return *this;
}

Camera &Camera::position(const Point &point) {
    eye.x(point.x()), eye.y(point.y()), eye.z(point.z());
    return *this;
}
Camera &Camera::focal_length(float d_length){
    d = d_length;
    return *this;
}
Camera &Camera::direction(float x, float y, float z){
    Vector dir;
    dir.x(x), dir.y(y), dir.z(z);
    
    u = dir.cross_product(Vector{0,1,0});
    v = u.cross_product(dir);
    w = dir * (-1);
    
    u.normalization();
    v.normalization();
    w.normalization();
    
    return *this;
}
Camera &Camera::direction(const Vector &vector) {
    u = vector.cross_product(Vector{0,1,0});
    v = u.cross_product(vector);
    w = vector * (-1);
    
    u.normalization();
    v.normalization();
    w.normalization();
    
    return *this;
}
Camera &Camera::image_range(float iw, float ih) {
    l = - iw / 2, r = iw / 2, t = ih / 2, b = - ih / 2;
    return *this;
}

Camera &Camera::image_pixels(int _nx, int _ny) {
    nx = _nx;
    ny = _ny;
    return *this;
}
