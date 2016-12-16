//
//  BVHNode.hpp
//  hw1.4_ds3420
//
//  Created by lindashen on 11/12/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#ifndef BVHNode_hpp
#define BVHNode_hpp

#include <stdlib.h>
#include <vector>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <limits>
#include <cmath>
#include "Surface.h"
#include "Point.h"
#include "Material.h"
#include "Intersection.h"

struct compminX {
public:
    bool operator()(Surface*  a, Surface* b) const{
        return a->box().min()[0] < b->box().min()[0];
    }
};
struct compminY {
public:
    bool operator()(Surface*  a, Surface* b) const{
        return a->box().min()[1] < b->box().min()[1];
    }
};
struct compminZ {
public:
    bool operator()(Surface*  a, Surface* b) const{
        return a->box().min()[2] < b->box().min()[2];
    }
};

class BVHNode :public Surface{
public:
    BVHNode(std::vector<Surface *> &objects, int &AXIS){
        unsigned long N = objects.size();
        if (N == 1) {
            _left = objects[0];
            _right = NULL;
            box_ = objects[0]->box();
        }else if (N == 2){
            _left = objects[0];
            _right = objects[1];
            
            Vector mincombined{std::min(_left->box().min()[0], _right->box().min()[0]),
                               std::min(_left->box().min()[1], _right->box().min()[1]),
                               std::min(_left->box().min()[2], _right->box().min()[2])};
            
            Vector maxcombined{std::max(_left->box().max()[0], _right->box().max()[0]),
                               std::max(_left->box().max()[1], _right->box().max()[1]),
                               std::max(_left->box().max()[2], _right->box().max()[2])};
            BBox boxcombined{static_cast<float>(mincombined[0]),
                static_cast<float>(mincombined[1]),
                static_cast<float>(mincombined[2]),
                static_cast<float>(maxcombined[0]),
                static_cast<float>(maxcombined[1]),
                static_cast<float>(maxcombined[2])};
            box_ = boxcombined;
        } else {
            if (AXIS == 0) {
                std::sort(objects.begin(), objects.end(), compminX());
            } else if (AXIS == 1) {
                std::sort(objects.begin(), objects.end(), compminY());
            } else {
                std::sort(objects.begin(), objects.end(), compminZ());
            }
            std::vector<Surface *> objects_left(objects.begin(), objects.begin() + N / 2);
            std::vector<Surface *> objects_right(objects.begin() + N / 2, objects.end());
            
            AXIS = (AXIS + 1) % 3;
            
            _left = new BVHNode(objects_left, AXIS);
            _right = new BVHNode(objects_right, AXIS);
            
            Vector mincombined{std::min(_left->box().min()[0], _right->box().min()[0]),
                std::min(_left->box().min()[1], _right->box().min()[1]),
                std::min(_left->box().min()[2], _right->box().min()[2])};
            
            Vector maxcombined{std::max(_left->box().max()[0], _right->box().max()[0]),
                std::max(_left->box().max()[1], _right->box().max()[1]),
                std::max(_left->box().max()[2], _right->box().max()[2])};

            box_.box(static_cast<float>(mincombined[0]),
                    static_cast<float>(mincombined[1]),
                    static_cast<float>(mincombined[2]),
                    static_cast<float>(maxcombined[0]),
                    static_cast<float>(maxcombined[1]),
                    static_cast<float>(maxcombined[2]));
        }
    }
    BBox bounding_box(Surface *objects){
        return objects->box();
    }
    bool intersect(const Ray &r, Intersection &it, int flag) {
//        std::cout<<box.min()[0]<<","<<box.min()[1]<<","<<box.min()[2]<<std::endl;

        if (box_.intersect(r, true).first) {
//            std::cout<<box.min()[0]<<","<<box.min()[1]<<","<<box.min()[2]<<std::endl;

            Intersection itleft, itright;
            bool left_hit = (_left != NULL) && _left->intersect(r, itleft, flag);
            bool right_hit = (_right != NULL) && _right->intersect(r, itright, flag);
            if (left_hit && right_hit) {
                if (itleft.getT1()  < itright.getT1()) {
                    it = itleft;
                    it.set_Material(itleft.get_Material());
                } else{
                    it = itright;
                    it.set_Material(itright.get_Material());
                }
//                std::cout<<"Both Sides"<<std::endl;
                return true;
            }else if (left_hit){
                it = itleft;
                it.set_Material(itleft.get_Material());
                return true;
            }else if (right_hit){
                it = itright;
                it.set_Material(itright.get_Material());
//                std::cout<<"Only right"<<std::endl;
                return true;
            }else
                return false;
        } else
            return false;
    }
    Surface *get_left() {
        return _left;
    }
    Surface *get_right() {
        return _right;
    }
    
    BBox box(){
        return box_;
    }
private:
    Surface *_left;
    Surface *_right;
    BBox box_;
};




#endif /* BVHNode_hpp */
//
