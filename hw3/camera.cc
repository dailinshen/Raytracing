//
//  camera.cpp
//  hw3
//
//  Created by lindashen on 10/18/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#include <vector>  // std::vector - template for array-like structures.
#include <cmath>
#include <limits>

#include "camera.h"
#include "surface.h"
#include "ray.h"
#include "light.h"
#include "material.h"

void Camera::init (Point pos, Vector dir, double d, double iw, double ih, int pw, int ph)
{
    eye_ = pos;
    w_ = dir * (-1);
    w_.normalize ();
    
    focal_length_ = d;
    
    image_width_ = iw;
    image_height_ = ih;
    
    pixels_width_ = pw;
    pixels_height_ = ph;
    
    // make an orthonormal frame for the camera:
    if (1.0 - fabs (w_.y()) < .0001) {
        // camera is pointing up or down - make an arbitrary
        // right-handed coordinate system:
        u_ = {1.0, 0.0, 0.0};
//        u_.set (1.0, 0.0, 0.0);
        v_ = w_.cross(u_);
//        v_.crossProduct (w_, u_);
    }
    else {
        Vector up{0., 1., 0.};
        u_ = up.cross(w_);
        v_ = w_.cross(u_);
//        u_.crossProduct (up, w_);
//        v_.crossProduct (w_, u_);
    }
    
    u_.normalize ();
    v_.normalize ();
    
    // set up the image:
    // OpenEXR uses exceptions - catch and print on error
    
    try
    {
        pixelBuffer_.resizeErase(pixels_height_, pixels_width_);
    }
    catch (const std::exception &exc) {
        std::cerr << exc.what() << std::endl;
        return;
    }
}


void Camera::renderScene (std::vector< Surface * > &surfaces, std::vector< Light * > &lights, std::vector< Material * > &materials) {
    
    std::cout << "rendering";
    
    int printProgress = pixels_height_ * pixels_width_ / 10.0;
    
    // for each of the pixels, generate a ray, then test against the
    // scene for intersection:
    
    for (int yy = 0; yy < pixels_height_; ++yy) {
        for (int xx = 0; xx < pixels_width_; ++xx) {
            
            // print one of these for every 1/10th of the image:
            if (printProgress &&
                (yy * pixels_width_ + xx) % printProgress == 0) std::cout << ".";
            
            Ray r = generateRay (xx, yy);
            
            double best_t = std::numeric_limits<double>::max();  // largest possible double
            
            // keep the best intersections info here:
            Point ipoint;     // intersction point on surface
            Vector normal;    // normal at intersection point
            int materialId = 0; // which material to use
            int check_index;
            bool foundIntersection = false;
            
            // To render with shading, however, we will have to test
            // all the objects and select the closest one.
            for (int whichSurf = 0; whichSurf < surfaces.size (); ++whichSurf) {
                
                Surface *s = surfaces[whichSurf];
                
                double t;           // ray parameterization of intersection point
                Point temp_point;     // intersction point on surface
                Vector temp_normal;    // normal at intersection point
                
                if (s->intersect (r, t, temp_point, temp_normal) &&
                    t < best_t) {
                    check_index = whichSurf;
                    foundIntersection = true;
                    ipoint = temp_point;
                    normal = temp_normal;
                    best_t = t;
                    materialId = s->materialIndex (); // save for later!
                }
            }
            
            if (foundIntersection) {
                
                // set up shading calulation
                Vector ret_rgb;
                Vector LL{0,0,0};
                for (int whichLight = 0; whichLight < lights.size(); ++whichLight){
                    bool block = false;
                    Light *lgt = lights[whichLight];
                    Vector L_e = lgt->spd ();
                    Vector L = lgt->position () - ipoint;
                    double lightdistsq = L.dot(L);
                    L.normalize ();
                    
                    Ray shadow_ray{ipoint, L};
                    
                    for (int whichSurf = 0; whichSurf < surfaces.size(); ++whichSurf) {
                        if (whichSurf == check_index)
                            continue;
                        Surface *s = surfaces[whichSurf];
                        double tt;
                        Point tt_point;
                        Vector tt_normal;
                        if (s->intersect(shadow_ray, tt, tt_point, tt_normal)) {
                            double distance = (tt_point - ipoint).magnitude();
                            if (distance < sqrt(lightdistsq)) {
                                block = true;
                                break;
                            }
                        }
                        
                    }
                    
                    if (!block){
                        Vector e = r.getDir ();
                        e = e * (-1);    
                        LL += materials[materialId]->blinn_phong(L, e, normal, L_e) * (1.0 / lightdistsq);
                    }
                }
                
                // scale by 1 over distance squared:
                ret_rgb = LL;
                setPixel (xx, yy, ret_rgb.x(), ret_rgb.y(), ret_rgb.z());
            }
            else {
                setPixel (xx, yy, 0., 0., 0.);
            }
            
        }
    }
    
    std::cout << "done!" << std::endl;
    
}
Ray Camera::generateRay (const int i, const int j) {

    double r = image_width_ / 2.0;
    double l = -1. * r;
    double t = image_height_ / 2.0;
    double b = -1. * t;
    
    double u = l + (r - l) * (i + .5) / pixels_width_;
    double v = t + (b - t) * (j + .5) / pixels_height_;
    
    
    // compute the direction vector d based on this:
    Vector d = w_ * -1.0 * focal_length_;
    d += u_ * u;
    d += v_ * v;
    
    d.normalize ();
    
    return Ray (eye_, d);;
    
}

void Camera::writeImage (const char *sceneFile) {
    try
    {
        RgbaOutputFile file (sceneFile, pixels_width_, pixels_height_, WRITE_RGBA);
        file.setFrameBuffer (&pixelBuffer_[0][0], 1, pixels_width_);
        file.writePixels (pixels_height_);
    }
    
    catch (const std::exception &exc) {
        std::cerr << exc.what() << std::endl;
        return;
    }
}


