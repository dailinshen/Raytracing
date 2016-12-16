//
//  pointlight.cpp
//  hw2
//
//  Created by lindashen on 10/13/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#include "pointlight.h"

PointLight::PointLight(const Point &point, const Vector &color): color_{color}, position_{point} {}
PointLight::PointLight(float x, float y, float z, float r, float g, float b): position_{x, y, z}, color_{r, g, b} {}
Vector &PointLight::color() {
    return color_;
}
Point &PointLight::position() {
    return position_;
}

