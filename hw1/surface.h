//
//  surface.hpp
//  hw1_ds3420
//
//  Created by lindashen on 10/1/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#ifndef surface_hpp
#define surface_hpp
#include <iostream>
#include <string>

#include "material.h"
#include "ray.h"

class Ray;
class Surface {
public:
    virtual ~Surface() {}

    inline const Material &material() const {
        return material_;
    };
    inline void material(const Material &material__) {
        Surface::material_ = material__;
    };
    virtual bool ray_intersection(Ray &ray, int id) const = 0;
    virtual std::string to_string() const = 0;
private:
    Material material_;
};
std::ostream &operator<<(std::ostream &os, const Surface &surface);

#endif /* surface_hpp */
