//
//  triangle.cpp
//  hw3
//
//  Created by lindashen on 10/18/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#include "triangle.h"

bool Triangle::intersect (const Ray &r, double &t, Point &ipoint, Vector &normal, bool &isSphere) const
{
    Vector d = r.getDir ();
    Point e = r.getOrigin ();
    
    double a_ = pa_.x() - pb_.x();
    double b_ = pa_.y() - pb_.y();
    double c_ = pa_.z() - pb_.z();
    
    double d_ = pa_.x() - pc_.x();
    double e_ = pa_.y() - pc_.y();
    double f_ = pa_.z() - pc_.z();
    
    double g_ = d.x();
    double h_ = d.y();
    double i_ = d.z();
    
    double j_ = pa_.x() - e.x();
    double k_ = pa_.y() - e.y();
    double l_ = pa_.z() - e.z();
    
    double M    =  a_*(e_*i_ - h_*f_) + b_*(g_*f_ - d_ * i_) + c_*(d_*h_ - e_*g_);
    t = ( f_*(a_*k_ - j_*b_) + e_*(j_*c_ - a_ * l_) + d_*(b_*l_ - k_*c_)) / (-M);
    
    // otherwise, t is the parameter of the closest intersection > 0.
    if (t <= 0.0001)
        return false;
    double beta = ( j_*(e_*i_ - h_*f_) + k_*(g_*f_ - d_ * i_) + l_*(d_*h_ - e_*g_)) / M;
    if ((beta < 0.) || (beta > 1.))
        return false;
    double gama = ( i_*(a_*k_ - j_*b_) + h_*(j_*c_ - a_ * l_) + g_*(b_*l_ - k_*c_)) / M;
    if ((gama < 0.) || (gama > ( 1. - beta)))
        return false;

    ipoint = r.getOrigin() + r.getDir() * t;
    normal = normal_;
    isSphere = false;
    return true;
}

