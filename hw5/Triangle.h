//
//  Triangle.h
//  Raytra
//
//  Created by Qi Wang on 2/12/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#ifndef Triangle_h
#define Triangle_h

#include <stdio.h>
#include "Surface.h"

class Triangle : public Surface{
    
private:
    void init() {
        Vector p12 = _p2 - _p1;
        Vector p13 = _p3 - _p1;
        _n = p12.cross(p13);
        _n.normalize();
        // init cache too
        _a = _p1[0] - _p2[0];
        _b = _p1[1] - _p2[1];
        _c = _p1[2] - _p2[2];
        _d = _p1[0] - _p3[0];
        _e = _p1[1] - _p3[1];
        _f = _p1[2] - _p3[2];
        
        float x_min, y_min, z_min, x_max, y_max, z_max;
        x_min = std::min(std::min(_p1[0], _p2[0]), _p3[0]);
        y_min = std::min(std::min(_p1[1], _p2[1]), _p3[1]);
        z_min = std::min(std::min(_p1[2], _p2[2]), _p3[2]);
        x_max = std::max(std::max(_p1[0], _p2[0]), _p3[0]);
        y_max = std::max(std::max(_p1[1], _p2[1]), _p3[1]);
        z_max = std::max(std::max(_p1[2], _p2[2]), _p3[2]);
        
        box(x_min, y_min, z_min, x_max, y_max, z_max);
    }
    
    Point _p1, _p2, _p3;
    Vector _n;
    double _a, _b, _c, _d, _e, _f;
    
public:
    Triangle();
    Triangle(double x1, double y1, double z1,
             double x2, double y2, double z2,
             double x3, double y3, double z3, Material *m);
    
    bool intersect(const Ray &r, Intersection &it, int flag);
    
    Vector getNormal(const Point &p){return move(_n);}
    
    Point getP1(){return _p1;}
    Point getP2(){return _p2;}
    Point getP3(){return _p3;}
    
    string getType(){return "triangle";};
};

#endif /* Triangle_h */
