//
//  triangle.hpp
//  hw1.5_ds3420
//
//  Created by lindashen on 11/17/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#ifndef triangle_hpp
#define triangle_hpp

#include <stdio.h>
#include "point.h"
#include "ray.h"
#include "material.h"
#include "calculation.h"
#include "surface.h"

class Triangle: public Calculation, public Surface{
    Point a;
    Point b;
    Point c;
    Ray normal;
    float ta,tb,tc,td,te,tf;
    int a_index, b_index, c_index;
    Vector N1, N2, N3;
    Vector N{0.0,0.0,0.0};
    char type;
public:
    
    void setSurfaceNormal(Point a, Point b, Point c);
    Point getA();
    Point getB();
    Point getC();
    inline Vector getSurfaceNormal(){
        return std::move(normal.getDir());
    }
    Triangle();
    virtual ~Triangle(){};
    Triangle(float xa, float ya, float za, float xb, float yb, float zb, float xc, float yc, float zc);
    Triangle(float xa, float ya, float za, float xb, float yb, float zb, float xc, float yc, float zc, int a_index_, int b_index, int c_index);
    float intersection(Ray& r);
    std::vector<Ray* > getRayToLight(Point& intersect, Light *light, int shadowRayNum);
    Ray getNormalAtIntersect(Point& Intersect);
    
    inline char get_type(){
        return std::move(type);
    };
    inline void set_type(char temp){
        type = temp;
    };
    inline void set_vertex_normal(Vector N1_, Vector N2_, Vector N3_) {
        N1 = N1_;
        N2 = N2_;
        N3 = N3_;
    };
    inline Vector get_smooth_normal() {
        return std::move(N);
    };
    inline int get_a_index(){
        return std::move(a_index);
    };
    inline int get_b_index(){
        return std::move(b_index);
    };
    inline int get_c_index(){
        return std::move(c_index);
    };
    
};

#endif
