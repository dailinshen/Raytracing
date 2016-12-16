//
//  Triangle.cc
//  Raytra
//
//  Created by Qi Wang on 2/12/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#include "Triangle.h"

Triangle::Triangle(){
    _m = NULL;
    _p1 = _p2 = _p3 = Point();
    init();
}

Triangle::Triangle(double x1, double y1, double z1,
                   double x2, double y2, double z2,
                   double x3, double y3, double z3, Material *m){
    _p1 = Point(x1, y1, z1);
    _p2 = Point(x2, y2, z2);
    _p3 = Point(x3, y3, z3);
    
    init();
    _m = m;
}

bool Triangle::intersect(const Ray &r, Intersection &it, int flag){
    //matrix A
    
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
    
    
//    std::pair<bool, float> box_hit = box_intersect(r);
//    if (!box_hit.first) {
//        return false;
//    }
//    if (flag == 1 || flag == -1){
//        if (box_hit.second < it.getT1() && box_hit.second > 0.001f) {
//            Point inter_p = r.getOri() + r.getDir() * box_hit.second;
//            Vector norm = box_normal(inter_p);
//            it.set(box_hit.second, box_hit.second, r, norm);
////            it.set_id(get_Index());
//            it.set_Material(_m);
//            //            r.intersection(Intersection(box_hit.second, inter_p, norm, this));
//            return true;
//        }
////        return true;
//    }
    double g = r._dir._xyz[0];
    double h = r._dir._xyz[1];
    double i = r._dir._xyz[2];
    
    double ei_hf = _e * i - h * _f;
    double gf_di = g * _f - _d * i;
    double dh_eg = _d * h - _e * g;
    
    double M = _a * ei_hf + _b * gf_di + _c * dh_eg;
    
    if(M == 0)
        return false;
    else{
        double j = _p1._xyz[0] - r._ori._xyz[0];
        double k = _p1._xyz[1] - r._ori._xyz[1];
        double l = _p1._xyz[2] - r._ori._xyz[2];
        
        double ak_jb = _a * k - j * _b;
        double jc_al = j * _c - _a * l;
        double bl_kc = _b * l - k * _c;
        
        double t = -(_f * ak_jb + _e * jc_al + _d * bl_kc)/M;
        if(t < 0.0001f)
            return false;
        
        double gamma = (i * ak_jb + h * jc_al + g * bl_kc)/M;
        if(gamma < 0 || gamma > 1)
            return false;
        
        double beta = (j * ei_hf + k * gf_di + l * dh_eg)/M;
        if(beta < 0 || beta > 1 - gamma)
            return false;
        if (t > 0){
            it.set(t, t, r, _n);
            //            it.set_id(get_Index());
            it.set_Material(_m);
            return true;
        }
//        //intersection with edges
//        it.set(t, t, r, _n);
////        it.set_id(get_Index());
//        it.set_Material(_m);
//        return true;
    }
    return false;
}

