//
//  parse.hpp
//  hw1_ds3420
//
//  Created by lindashen on 9/28/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#ifndef parse_hpp
#define parse_hpp

#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <iostream>
#include "surface.h"
#include "sphere.h"
#include "plane.h"
#include "camera.h"

using namespace std;

struct float3 {
    float x,y,z;
};
inline istream &operator>>(istream &is, float3 &f) {
    return is>>f.x>>f.y>>f.z;
}
inline ostream &operator<<(ostream &os, float3 &f) {
    return os<<"<"<<f.x<<","<<f.y<<","<<f.z<<">";
}
class Camera;
class Parser {
    
public:
    
    Surface *sphere(float3 pos, float r);
//    virtual void sph(float3 pos, float r);
    Plane *plane(float3 n, float d);
//    virtual void p(float3 n, float d);
    void camera(float3 pos, float3 dir, float d, float iw, float ih, int pw, int ph, Camera &cameras, vector<Surface *> &surfaces);
//    virtual void cam(float3 pos, float3 dir, float d, float iw, float ih, int pw, int ph);
    Material material(float3 diff, float3 spec, float r, float3 refl);
//    virtual void mat(float3 diff, float3 spec, float r, float3 refl);
    
//    virtual void triangle(float3 p1, float3 p2, float3 p3) {}
//    virtual void pointLight(float3 pos, float3 rgb) {}
//    virtual void directionalLight(float3 dir, float3 rgb) {}
//    virtual void ambientLight(float3 rgb) {}

//    void start(const char *file);
    void start(const char *file, char *path);
    
    
//    virtual void parse(const char *file, vector<Surface *> &surfaces, Camera &cameras);
    virtual void parse(const char *file, vector<Surface *> &surfaces, Camera &cameras);
private:
    
};

#endif /* parse_hpp */
