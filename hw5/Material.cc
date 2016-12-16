//
//  Material.cc
//  Raytra
//
//  Created by Qi Wang on 2/12/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#include "Material.h"

Material::Material(){
    _diffuse = _specular = Vector(0.0, 0.0, 0.0);
    _idealSpec = _attenuate = Vector(0.0, 0.0, 0.0);
    _r = _ni = 0.0;
}

Material::Material(double dr, double dg, double db,
                   double sr, double sg, double sb,
                   double r, double ir, double ig, double ib){
    _diffuse = Vector(dr, dg, db);
    _specular = Vector(sr, sg, sb);
    _idealSpec = Vector(ir, ig, ib);
    _r = r;
}

void Material::setRefraction(double ni, double ar, double ag, double ab){
    _ni = ni;
    _attenuate = Vector(ar, ag, ab);
}

//Blinn-Phong shading
Vector Material::phongShading(const Vector &i_e, const Vector &n,
                              const Vector &i_l, const Vector &l_Rgb){
    Vector rgb(0.0, 0.0, 0.0);
    
    Vector h = i_e + i_l;
    h.normalize();
    
    double cosnl = max(0.0, n.dot(i_l));
    double cosnh = max(0.0, n.dot(h));
    
    rgb += (_diffuse * l_Rgb) * cosnl + (_specular * l_Rgb) * pow(cosnh, _r);
    return rgb;
}

//Diffuse shading
Vector Material::lambertianShading(const Vector &n, const Vector &l,
                                   const Vector &l_Rgb){
    Vector rgb(0.0, 0.0, 0.0);
    
    double cosnl = max(0.0, n.dot(l));
    rgb += (_diffuse * l_Rgb) * cosnl;
    return rgb;
}


Vector Material::backShading (
                                const Vector &L,    // unit vector to the light
                                const Vector & /*e*/, // unit vector to the viewer - not used!
                                const Vector &N,    // unit surface normal
                                const Vector &L_e)
{
    
    Vector R (0., 0., 0.); // the amount of light (color) returned along the ray
    
    double n_dot_l = N.dot (L);
    
    if (n_dot_l > 0.) {
        Vector diff (1.0 * L_e[0] * n_dot_l,
                     1.0 * L_e[1] * n_dot_l,
                     0.0 * L_e[2] * n_dot_l);
        R = diff;
    }
    
    return R;
}


