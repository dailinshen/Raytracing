//
//  Surface.h
//  Raytra
//
//  Created by Qi Wang on 2/6/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#ifndef Surface_h
#define Surface_h

#include "Ray.h"
#include "Material.h"
#include "Intersection.h"
#include "BBox.h"
class Surface{
protected:
    Material *_m;
    BBox _box;
    int index;
public:
    Surface(): _m(NULL) {}
    
//    virtual bool intersect(const Ray &r, Intersection &it) {return false;}
//    
//    virtual Vector getNormal() {return Vector();}
//    
//    virtual Material* getMaterial() const{return _m;}
//    
//    virtual string getType(){return "surface";};
    inline void box(float x_min, float y_min, float z_min,
                    float x_max, float y_max, float z_max) {
        _box.box(x_min, y_min, z_min, x_max, y_max, z_max);
    };
    inline void set_Index(int n){
        index = n;
    };
    inline int get_Index(){
        return std::move(index);
    };
    
    inline std::pair<bool, float> box_intersect(const Ray &ray, bool isNode = false) const {
        return _box.intersect(ray, isNode);
    }
    
    inline Vector box_normal(const Point &inter_p) const {
        return _box.normal(inter_p);
    }
    //--------------------------------------------------------
    //    virtual bool intersect(Ray &, const Render &) const = 0;
    
    //    virtual std::string to_string() const = 0;
    
    virtual bool intersect(const Ray &r, Intersection &it, int flag) {return false;}
    
    virtual Vector getNormal() {return Vector();}
    
    virtual Material* getMaterial() const{return _m;}
    
    virtual string getType(){return "surface";};
    
    virtual BBox box() {
        return _box;
    }
};

#endif /* Surface_h */
