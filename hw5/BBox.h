//
//  BBox.hpp
//  hw1.4_ds3420
//
//  Created by lindashen on 11/12/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#ifndef BBox_hpp
#define BBox_hpp

#include <stdio.h>

#include <map>
#include <limits>

#include "Ray.h"

#define TOLERANCE 0.001f
#define BOUNDING 0.002f

/**
 * Bounding Box class used in rendering.
 */
class BBox {
    friend class BVHNode;
    friend class Surface;
public:
    std::pair<bool, float> intersect(const Ray &ray, bool isNode) const;
    
    Vector normal(const Point &inter_p) const;
    
    BBox(float x_min = .0f, float y_min = .0f, float z_min = .0f,
         float x_max = .0f, float y_max = .0f, float z_max = .0f) : _min{x_min, y_min, z_min},
    _max{x_max, y_max, z_max} { }
    
    void box(float x_min, float y_min, float z_min,
             float x_max, float y_max, float z_max);
    
    inline const Point &min() const {
        return _min;
    }
    
    inline const Point &max() const {
        return _max;
    }
    inline void set_isLeaf(bool leaf){
        isLeaf = leaf;
    };
    inline bool get_isLeaf(){
        return std::move(isLeaf);
    };
    inline void set_index(int index){
        _index = index;
    };
    inline int get_index(){
        return std::move(_index);
    };
private:
    Point _min, _max;
    int _index;
    bool isLeaf = false;
};




#endif /* BBox_hpp */
