//
//  pointlight.hpp
//  hw2
//
//  Created by lindashen on 10/13/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#ifndef pointlight_hpp
#define pointlight_hpp


#include <ImfRgbaFile.h>
#include <ImfStringAttribute.h>
#include <ImfMatrixAttribute.h>
#include <ImfArray.h>

#include <stdio.h>
#include "vector.h"
#include "light.h"
#include "point.h"

using namespace std;
using namespace Imf;
using namespace Imath;

class PointLight: public Light {
public:
    PointLight(const Point &point, const Vector &color);
    PointLight(float x = 0, float y = 0, float z = 0, float r = 0, float g = 0, float b = 0);
    Vector &color();
    Point &position();
    inline Point position(const Vector &pos) {
        position_.x(pos.x()), position_.y(pos.y()), position_.z(pos.z());
        return position_;
    };
    inline Point position(float x, float y, float z) {
        position_.x(x), position_.y(y), position_.z(z);
        return position_;
    };
    inline Vector color(const Vector &color) {
        color_.x(color.x()), color_.y(color.y()), color_.z(color.z());
        return color_;
    };
    inline Vector color(float r, float g, float b) {
        color_.x(r), color_.y(g), color_.z(b);
        return color_;
    };
private:
    Point position_;
    Vector color_;
};

#endif /* pointlight_hpp */
