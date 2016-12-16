//
//  camera.cpp
//  hw2
//
//  Created by lindashen on 10/13/16.
//  Copyright © 2016 lindashen. All rights reserved.
//
#include <vector>
#include <cmath>
#include "camera.h"
#include "surface.h"
#include "ray.h"
#include "material.h"
void Camera::init (
                   Point pos,
                   Vector dir,
                   double d,
                   double iw,
                   double ih,
                   int pw,
                   int ph)
{
    eye_ = pos;
    w_ = dir * (-1.0);
    w_.normalize ();
    
    focal_length_ = d;
    
    image_width_ = iw;
    image_height_ = ih;
    
    pixels_width_ = pw;
    pixels_height_ = ph;
    
    // make an orthonormal frame for the camera:
    if (1.0 - fabs (w_.x()) < .0001) {
        // camera is pointing up or down - make an arbitrary
        // right-handed coordinate system:
        u_.x(1.0), u_.y(0.0), u_.z(0.0);
        v_ = w_.cross(u_);

    }
    else {
        Vector up{0., 1., 0.};
        u_ = up.cross(w_);
        v_ = w_.cross(u_);
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


//
// Generate a ray for a specific pixel:
//
Ray Camera::generateRay (
                         const int i, // i is in the u direction (similar to X in cartesian)
                         const int j) // j is in the v direction (similar to Y in cartesian)
{
    
    
    // get the u and v values that correspond to i and j:
    
    // we are assuming a centered image here - but maybe that
    // will change in the future, so let's calculate u,v from
    // the more general image plane description:
    double r = image_width_ / 2.0;
    double l = -1. * r;
    double t = image_height_ / 2.0;
    double b = -1. * t;
    
    double u = l + (r - l) * (i + .5) / pixels_width_;
    
    // OpenEXR files have [0 0] pixel in top left, i.e. the v goes from
    // smallest at the top, largest at the bottom, so this is (b-t) insted
    // of (t - b) like the book shows. For other imag formats, this may be
    // different.
    double v = t + (b - t) * (j + .5) / pixels_height_;
    
    
    // compute the direction vector d based on this:
    Vector d = w_ * (-1.0) * focal_length_;
    d += u_ * u;
    d += v_ * v;
    
    d.normalize ();
    
    Ray retRay (eye_, d);
    
    return retRay;
    
}


//
// Render the scene:
//
void Camera::renderScene (
                          std::vector< Surface * > &surfaces,
                          std::vector< Light * > &lights,
                          std::vector< Material * > &materials
                          )
{
    
    std::cout << "rendering";
    
    int printProgress = pixels_height_ * pixels_width_ / 10.0;
    
    // for each of the pixels, generate a ray, then test against the
    // scene for intersection:
    for (int yy = 0; yy < pixels_height_; ++yy) {
        for (int xx = 0; xx < pixels_width_; ++xx) {
            
            // print one of these for every 1/10th of the image:
            if ((yy * pixels_width_ + xx) % printProgress == 0)
                std::cout << ".";
            
            Ray r = generateRay (xx, yy);


            bool foundIntersection = false;
            int materialId = 0; // which material to use
            double mini = INFINITY;
            Vector kd, ks;
            double exp = 0;
            Vector norm;
            Point point;
            // If we intersect anything, stop since we don't need to test
            // anymore. To render with  shading, however, we will have to test
            // all the objects and select the closest one.
            for (int whichSurf = 0;
                 whichSurf < surfaces.size ();
                 ++whichSurf) {
//                std::cerr << "detect."<< mini <<std::endl;
                Surface *s = surfaces[whichSurf];
                double temp = s->intersect(r);
                if (temp != 0.0) {
                    
                    if (temp < mini) {
                        
//                        if (mini!=INFINITY){
//                            std::cerr << "mini is not INIFINITY."<< std::endl;
//                        }
                        mini = temp;
                        
                        const Intersection intersec = r.intersection();
                        norm = intersec.norm();
                        point = intersec.point();
                        foundIntersection = true;
                        materialId = s->made_up_of_material(); // save for later!
                        kd = materials[materialId]->diffuse();
                        ks = materials[materialId]->specular();
                        exp = materials[materialId]->exponent();
                    }
                }
//                std::cerr << "update."<< mini <<std::endl;
            }
            
            
            if (foundIntersection) {
                
                Vector l = lights[0]->position() - point;
                double d = l.magnitude();
                l.normalize();
                Vector v = r.position() - point;
                v.normalize();
                Vector h = bisector(v, l);
                Vector intensity = lights[0]->color();
//                Vector ret_rgb = materials[materialId]->diffuse();
                
                Vector ret_rgb = blinn_phong(kd, intensity, norm, l, ks, h, exp) / ( d * d );
                
    
                setPixel (xx, yy, ret_rgb.x(), ret_rgb.y(), ret_rgb.z());
            }
            else
                setPixel (xx, yy, 0.1, 0.1, 0.1);
            
        }
    }
    
    std::cout << "done!" << std::endl;
    
}

Vector Camera::blinn_phong(Vector &kd, Vector &intensity, Vector &n, Vector &l, Vector &ks, Vector &h, double p) {
    Vector diffuse;
    diffuse.x(kd.x() * intensity.x());
    diffuse.y(kd.y() * intensity.y());
    diffuse.z(kd.z() * intensity.z());
    diffuse *= n.dot(l) > 0 ? n.dot(l) : 0;
    
    Vector specular;
    specular.x(ks.x() * intensity.x());
    specular.y(ks.y() * intensity.y());
    specular.z(ks.z() * intensity.z());
    
    double max = n.dot(h) > 0 ? n.dot(h) : 0;
    specular *= pow(max, p);
    
    Vector L = specular + diffuse;
    return L;
}
//
// Save out the final image:
//
void Camera::writeImage (
                         const char *sceneFile)
{
    
    // write the image data as an openEXR file
    // OpenEXR uses exceptions - catch and print on error
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
