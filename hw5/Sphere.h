//
//  Sphere.h
//  Raytra
//
//  Created by Qi Wang on 2/6/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#ifndef Sphere_h
#define Sphere_h

#include "Surface.h"

class Sphere: public Surface{
private:
    void init() {
        float x_min, y_min, z_min, x_max, y_max, z_max;
        x_min = _center[0] - _radius;
        y_min = _center[1] - _radius;
        z_min = _center[2] - _radius;
        
        x_max = _center[0] + _radius;
        y_max = _center[1] + _radius;
        z_max = _center[2] + _radius;
        
        box(x_min, y_min, z_min, x_max, y_max, z_max);
    }
    Point _center;
    double _radius;
    
public:
    Sphere(): _center(Point()), _radius(0.0) {
        init();
    }
    
    Sphere(Material *m, const Point &p, double r){
        _m = m;
        _center = p;
        _radius = r;
        init();
    }
    
    bool intersect(const Ray &r, Intersection &it, int flag);
    
    Vector getNormal(const Point &p);
    
    Point getCenter() const{return _center;}
    
    double getRadius() const{return _radius;}
    
    string getType(){return "sphere";};
};


#endif /* Sphere_h */
