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
#include "ambientlight.h"
#include "pointlight.h"
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

Vector Camera::LOL(Ray &ray,
                 double min_t,
                 double max_t,
                 int recursive_limit,
                 const char *ray_type,
                 std::vector<Surface *> &surfaces,
                 std::vector<Light *> &lights,
                 int light_index,
                 std::vector<Material *> &materials){
    if (recursive_limit == 0)
        return Vector{0., 0., 0.};
    
    //Check whether the ray is a shadow ray.
    const char *shadow = "SHADOW_RAY";
    if (strncmp(ray_type, shadow, 3) == 0) {
        bool blocked = false;
        for (int whichSurf = 0; whichSurf < surfaces.size() && !blocked; ++whichSurf) {
            Surface *s = surfaces[whichSurf];
            double tt;
            Point tt_point;
            Vector tt_normal;
            bool isT;
            if (s->intersect(ray, tt, tt_point, tt_normal, isT) && (tt < max_t && tt > min_t)) {
                blocked = true;
            }
        }
        //if there is any intersection on [min_t, max_t] interval, return [0,0,0]
        //else return light->spd()
        if(blocked)
            return Vector{0., 0., 0.};
        else
            return lights[light_index]->spd();
    }
    
    
    //get closest intersction within the scene, along ray
    //if there is no intersection, return [0,0,0]
    double best_t = INFINITY;
    // keep the best intersections info here:
    Point ipoint;     // intersction point on surface
    Vector normal;    // normal at intersection point
    int materialId = 0; // which material to use
    bool foundIntersection = false;
    bool isSphere = false;
    // To render with shading, however, we will have to test
    // all the objects and select the closest one.
    for (int whichSurf = 0; whichSurf < surfaces.size (); ++whichSurf) {
    
        Surface *s = surfaces[whichSurf];
        
        double t;           // ray parameterization of intersection point
        Point temp_point;     // intersction point on surface
        Vector temp_normal;    // normal at intersection point
        bool check = true;
        if (s->intersect (ray, t, temp_point, temp_normal, check) && t < best_t) {
            isSphere = check;
            foundIntersection = true;
            ipoint = temp_point;
            normal = temp_normal;
            best_t = t;
            materialId = s->materialIndex (); // save for later!
        }
    }
    if (!foundIntersection)
        return Vector{0., 0., 0.};
    
    //for each light "thislight":
    // compute ray "s_ray", from intersection point to light, and maximum t_value "s_max_t"
    Vector R{0., 0., 0.}; // R is a accumulator vector
    Vector L_rgb{0., 0., 0.};
    for (int whichLight = 0; whichLight < lights.size(); ++whichLight){
        
        Light *lgt = lights[whichLight];
        
        Vector l_e = lgt->spd ();
        Vector l = lgt->position () - ipoint;
        
        double lightdistsq = l.dot(l);
        l.normalize ();
        
        double s_max_t = sqrt(lightdistsq);
        Vector e = ray.getDir ();
        e = e * (-1);
        
        if (!isSphere && normal.dot(ray.getDir()) > 0) {
            normal = normal * (-1);
            materialId = 1;
        }
        
        
        Ray s_ray{ipoint, l};
        const char *shadow_ray = "SHADOW_RAY";
        L_rgb = LOL(s_ray, 0.01, s_max_t, 1, shadow_ray, surfaces, lights, whichLight, materials);
        if (L_rgb.magnitude() > 0)
            R += materials[materialId]->blinn_phong(l, e, normal, l_e) * (1.0 / lightdistsq);
        if (AmbientLight *ambientlight = dynamic_cast<AmbientLight *> (lgt)) {
            const char* reflect = "REF_RAY";
            if (strncmp(ray_type, reflect, 3) != 0) {
                Vector temp;
                temp.x(ambientlight->spd().x() * materials[materialId]->kd().x());
                temp.y(ambientlight->spd().y() * materials[materialId]->kd().y());
                temp.z(ambientlight->spd().z() * materials[materialId]->kd().z());
                R += temp; //No attenuation.
            }
        }
    }
    
    // if material is not reflective return R[]
    if (!materials[materialId]->isReflective())
        return R;
    else {
        Vector r = normal * (- 2.0 * ray.getDir().dot(normal));
        r += ray.getDir();
        r.normalize();
        Ray ref_ray{ipoint, r};
        const char * reflection_ray = "REF_RAY";
        R += materials[materialId]->kr() * LOL(ref_ray, .01, INFINITY, recursive_limit - 1 , reflection_ray, surfaces, lights, 0, materials);
        return R;
    }
}

void Camera::renderScene (std::vector< Surface * > &surfaces,
                          std::vector< Light * > &lights,
                          std::vector< Material * > &materials) {
    
    std::cout << "rendering";
    
    int printProgress = pixels_height_ * pixels_width_ / 10.0;
    
    // for each of the pixels, generate a ray, then test against the
    // scene for intersection:
    
    for (int yy = 0; yy < pixels_height_; ++yy) {
        for (int xx = 0; xx < pixels_width_; ++xx) {
            
            // print one of these for every 1/10th of the image:
            if (printProgress && (yy * pixels_width_ + xx) % printProgress == 0)
                std::cout << ".";
            Vector rgb{0., 0., 0.};
            Ray r = generateRay (xx, yy);
            const char *camera_ray = "CAMERA_RAY";
            rgb += LOL(r, 0.01, INFINITY, 20, camera_ray, surfaces, lights, 0, materials);
            
            setPixel (xx, yy, rgb.x(), rgb.y(), rgb.z());
            
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


