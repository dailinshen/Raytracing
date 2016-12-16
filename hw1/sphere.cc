//
//  sphere.cpp
//  hw1_ds3420
//
//  Created by lindashen on 10/1/16.
//  Copyright © 2016 lindashen. All rights reserved.
//
#include <cmath>
#include "sphere.h"


Sphere::Sphere(const Point &origin, float radius): O{origin}, r{radius} {}
Sphere::Sphere(float origin_x, float origin_y, float origin_z, float radius): O{origin_x, origin_y, origin_z}, r{radius} {}

Sphere &Sphere::origin_position(const Point &origin) {
    O.x(origin.x()), O.y(origin.y()), O.z(origin.z());
    return *this;
}
Sphere &Sphere::origin_position(float x, float y, float z) {
    O.x(x), O.y(y), O.z(z);
    return *this;
}
Sphere &Sphere::radius(float r_) {
    r = r_;
    return *this;
}
Sphere &Sphere::material_composition(const Material &material) {
    Surface::material(material);
    return *this;
}
std::string Sphere::to_string() const {
    std::stringstream os;
    os << "Sphere:\n";
    os << "\torigin: " << O.x() << O.y() << O.z() << "\n";
    os << "\tradius: " << r << std::flush;
    return os.str();
}
bool Sphere::ray_intersection(Ray &ray, int id) const {
    Vector ray_o_sphere_o = ray.origin - O;
    Vector ray_direction = ray.dir;
    float d_p0_O = ray_o_sphere_o.dot_product(ray_direction);
    float d_d = ray_direction.dot_product(ray_direction);
    float p0_O_p0_O = ray_o_sphere_o.dot_product(ray_o_sphere_o);
    if ((d_p0_O * d_p0_O - (d_d * p0_O_p0_O - r * r)) >= 0) {
        float t;
        float square_root = sqrt(d_p0_O * d_p0_O - (d_d * p0_O_p0_O - r * r));
        float t1, t2;
        t1 = (- d_p0_O + square_root) / d_d;
        t2 = (- d_p0_O - square_root) / d_d;
        if (t1 == t2) {
            t = t1;
        } else {
            t = (t1 > t2 ? t1 : t2);
            if (t < 0) {
                return false;
            }
        }
        if (ray.update_t(t)) {
            Point point = ray.origin + ray.dir * t;
            Vector normalized_vector = point - O;
            normalized_vector.normalization();
            ray.intersection(Intersection(t, point, normalized_vector, id));
        }
        return true;
    } else {
        return false;
    }
}
