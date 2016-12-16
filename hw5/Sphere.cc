//
//  Sphere.cc
//  Raytra
//
//  Created by Qi Wang on 2/6/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#include "Sphere.h"

bool Sphere::intersect(const Ray &r, Intersection &it, int flag){
    //Calculate descriminant
    
//    std::cout<<_m->getDiffuse()[0]<<","<<_m->getDiffuse()[1]<<","<<_m->getDiffuse()[2]<<std::endl;
    
    std::pair<bool, float> box_hit = box_intersect(r);
    if (!box_hit.first)
        return false;
    if (flag == 1 || flag == -1) {
        if (it.getT1() > box_hit.second && box_hit.second > 0.001f) {
            Point inter_p = r.getOri() + r.getDir() * box_hit.second;
            Vector norm = box_normal(inter_p);
            it.set(box_hit.second, box_hit.second, r, norm);
//            it.set_id(get_Index());
            it.set_Material(_m);
//            std::cout<<it.get_Material()->getDiffuse()[0]<<","<<it.get_Material()->getDiffuse()[1]<<","<<it.get_Material()->getDiffuse()[2]<<std::endl;
            return true;
        }
    }
    
    Vector v(getCenter(), r.getOri());
    Vector d = r.getDir();

    double tmp1 = d.dot(v);
    double tmp2 = d.dot(d);
    double tmp3 = v.dot(v) - getRadius() * getRadius();
    double desc = tmp1 * tmp1 - tmp2 * tmp3;
    
    if(desc >= 0){
        double t1, t2;
        Vector d_neg = d * (-1);
        if(desc == 0)                               //One intersection points
            t1 = t2 = d_neg.dot(v)/tmp2;
        else{                                       //Two intersection points
            t1 = (d_neg.dot(v) - sqrt(desc))/tmp2;
            t2 = (d_neg.dot(v) + sqrt(desc))/tmp2;
        }
        Point p = r.getOri() + r.getDir() * t1;
        Vector n = getNormal(p);
        if (t1 > 0){
            it.set(t1, t2, r, n);
//            it.set_id(get_Index());
            it.set_Material(_m);
            return true;
        }
    }
    return false;
}

Vector Sphere::getNormal(const Point &p){
    Vector n(_center, p);
    n.normalize();
    return move(n);
}
