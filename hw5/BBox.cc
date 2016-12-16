//
//  BBox.cpp
//  hw1.4_ds3420
//
//  Created by lindashen on 11/12/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

//
#include "BBox.h"

std::pair<bool, float> BBox::intersect(const Ray &ray, bool isNode) const {
    std::pair<bool, float> ret{false, .0f};
    
    const Vector &ray_dir = ray.getDir();
    const Point &ray_orig = ray.getOri();
    float tx_min, tx_max, ty_min, ty_max, tz_min, tz_max, t_min, t_max;
    // tx_min, tx_max
    if (ray_dir[0] < 0) {
        tx_max = (_min[0] - ray_orig[0]) / ray_dir[0];
        tx_min = (_max[0] - ray_orig[0]) / ray_dir[0];
    } else if (ray_dir[0] > 0) {
        tx_max = (_max[0] - ray_orig[0]) / ray_dir[0];
        tx_min = (_min[0] - ray_orig[0]) / ray_dir[0];
    } else {
        if (_min[0] > ray_orig[0] || ray_orig[0] > _max[0]) {
            return std::move(ret);
        } else {
            tx_max = std::numeric_limits<float>::infinity();
            tx_min = -std::numeric_limits<float>::infinity();
        }
    }
    // ty_min, ty_max
    if (ray_dir[1] < 0) {
        ty_max = (_min[1] - ray_orig[1]) / ray_dir[1];
        ty_min = (_max[1] - ray_orig[1]) / ray_dir[1];
    } else if (ray_dir[1] > 0) {
        ty_max = (_max[1] - ray_orig[1]) / ray_dir[1];
        ty_min = (_min[1] - ray_orig[1]) / ray_dir[1];
    } else {
        if (_min[1] > ray_orig[1] || ray_orig[1] > _max[1]) {
            return std::move(ret);
        } else {
            ty_max = std::numeric_limits<float>::infinity();
            ty_min = -std::numeric_limits<float>::infinity();
        }
    }
    // tz_min, tz_max
    if (ray_dir[2] < 0) {
        tz_max = (_min[2] - ray_orig[2]) / ray_dir[2];
        tz_min = (_max[2] - ray_orig[2]) / ray_dir[2];
    } else if (ray_dir[2] > 0) {
        tz_max = (_max[2] - ray_orig[2]) / ray_dir[2];
        tz_min = (_min[2] - ray_orig[2]) / ray_dir[2];
    } else {
        if (_min[2] > ray_orig[2] || ray_orig[2] > _max[2]) {
            return std::move(ret);
        } else {
            tz_max = std::numeric_limits<float>::infinity();
            tz_min = -std::numeric_limits<float>::infinity();
        }
    }
    t_min = std::fmaxf(std::fmaxf(tx_min, ty_min), tz_min);
    t_max = std::fminf(std::fminf(tx_max, ty_max), tz_max);
    // very important here, my trick
    if (isNode) {
        if (t_max < .0f) {
            return std::move(ret);
        }
    } else {
        if (t_min < -10.f) {
            return std::move(ret);
        }
    }
    
    // for triangle, the bounding box might be a thin layer
    ret.first = t_min < t_max;
    ret.second = t_min;
    
    return std::move(ret);
}

void BBox::box(float x_min, float y_min, float z_min, float x_max, float y_max, float z_max) {
    
    
    Point temp_min{x_min - BOUNDING, y_min - BOUNDING, z_min - BOUNDING };
    _min = temp_min;
    Point temp_max{x_max + BOUNDING, y_max + BOUNDING, z_max + BOUNDING };
    _max = temp_max;
}

Vector BBox::normal(const Point &inter_p) const {
    Vector ret(.0f, .0f, .0f);
    float x = 0.0f, y = 0.0f, z = 0.0f;
    if (std::abs(inter_p[0] - _min[0]) < TOLERANCE) {
        x = -1;
    } else if (std::abs(inter_p[0] - _max[0]) < TOLERANCE) {
        x = 1;
    } else if (std::abs(inter_p[1] - _min[1]) < TOLERANCE) {
        y = -1;
    } else if (std::abs(inter_p[1] - _max[1]) < TOLERANCE) {
        y = 1;
    } else if (std::abs(inter_p[2] - _min[2]) < TOLERANCE) {
        z = -1;
    } else if (std::abs(inter_p[2] - _max[2]) < TOLERANCE) {
        z = 1;
    }
    Vector temp{x, y, z};
    ret = temp;
    return std::move(ret);
}
