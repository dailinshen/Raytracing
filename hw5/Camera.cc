//
//  Camera.cc
//  Raytra
//
//  Created by Qi Wang on 2/6/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//

#include "Camera.h"

Camera::Camera(){
    _eye = Point();
    _f = 0.0;
    _iw = _ih = 0.0;
    _pw = _ph = 0.0;
    _u = _v = _w = Vector();
    _pixels.resizeErase(0, 0);
}

Camera::Camera(const Point &p, const Vector &dir,
               double d, double iw, double ih,
               int pw, int ph){
    _eye = p;
    _f = d;
    _iw = iw;
    _ih = ih;
    _pw = pw;
    _ph = ph;
    setUvw(dir);
    _pixels.resizeErase(ph, pw);
}

//Set up the camera coordinates
void Camera::setUvw(const Vector &d){
    _w = d * (-1.0);
    _w.normalize();
    if(1 - abs(_w[1]) < 0.0001)
    {
        _u = Vector(1.0, 0.0, 0.0);
        _v = _u.cross(d);
    }
    else{
        Vector up(0.0, 1.0, 0.0);
        _u = d.cross(up);
        _v = _u.cross(d);
    }
    _u.normalize();
    _v.normalize();
}

//Generate ray through the current pixel
Ray Camera::generateRay(double i, double j){
    //Convert pixel coordinates to image plane coordinates
    double l = -_iw/2.0;
    double t = _ih/2.0;
    double U = l + _iw * (i + 0.5) / _pw;
    double V = t - _ih * (j + 0.5) / _ph;
    
    
    Vector dir = _w * (-_f)+ _u * U + _v * V;
    dir.normalize();
    return move(Ray(_eye, dir));
}

//Render the image
void Camera::render(const vector<Surface*> &objects,
                    const vector<Light*> &lights,
                    const AmbientLight *aLight,
                    int flag,
                    BVHNode &root){
//    if (flag == -1){
//        root = new BVHNode();
//        cout << "Starting building BVH tree..."<< endl;
//        root = root->buildBVH(0, objects);
//        cout << "Building BVH tree done!" << endl;
//        cout << "rendering...." << endl;
//        //for each pixel generate a ray through it
//        srand((unsigned int)time(NULL));
//        for(int y = 0; y < _ph; ++y){
//            for(int x = 0; x < _pw; ++x){
//                Ray r = generateRay(x, y);
//                Vector rgb = rayColor_NULL(r, 1, 10, lights, aLight, objects, root, std::numeric_limits<int>::max());
////                Vector rgb = rayColor_NULL(r, 1, 10, lights, aLight, objects);
//                setPixel(x, y, rgb[0], rgb[1], rgb[2]);
//            }
//        }
       
//    }
//    else{
    
    
    cout << "render image." << endl;
    
    //for each pixel generate a ray through it
    for(int y = 0; y < _ph; ++y){
        for(int x = 0; x < _pw; ++x){
            Ray r = generateRay(x, y);
            Vector rgb;
            
            if (flag == 0)
                rgb += rayColor_0(r, 1, 10, lights, aLight, objects);
            else if (flag == 1)
                rgb += rayColor_1(r, 1, 10, lights, aLight, objects);
            else if (flag == -1)
                rgb += rayColor_NULL(r, 1, 10, lights, aLight, objects, root);
            setPixel(x, y, rgb[0], rgb[1], rgb[2]);
        }
    }
//    }
    cout << "finished rendering." << endl;
}

//Recursive ray tracing
//ray_type: 1 - primary ray; 2 - reflected ray; 3 - refracted ray
Vector Camera::rayColor_0(const Ray &r, int ray_type, int recurse_limit,
                        const vector<Light*> lights,
                        const AmbientLight *aLight,
                        const vector<Surface*> &objects){
    if(recurse_limit == 0)
        return move(Vector(0.0, 0.0, 0.0));
    
    //find closest intersection
    Material *m = NULL;
    Intersection it, tmp;
    
    for(auto obj : objects){
        if(obj->intersect(r, tmp, 0)){
            if(tmp.getT1() > 0.0001 && tmp.getT1() < it.getT1()){
                it = tmp;
                m = obj->getMaterial();
            }
        }
    }
    
    //color accumulator
    Vector ret_rgb(0.0, 0.0, 0.0);
    
    if(it.intersect()){
        Point p1 = it.getP1();
        
        //Normal at intersection
        Vector n = it.getNormal();
        
        //Vector from intersection to camera
        Vector i_e = r.getDir();
        i_e *= -1.0;
        
#define NEW_WAY
        
        // if it's flipped, flip the normal, and only consider lights on
        // that side of the
        bool flipped = false;
        if (i_e.dot(n) < 0.0) {
#ifdef NEW_WAY
            n *= -1.0;
#endif
            flipped = true;
        }
        
       for(auto li : lights){
            //bling-phong shading
            if (li->getType() == 'p'){
                //Vector from intersection to light position
                Vector i_l = Vector(p1, li->getPos());
                
                //t should be less than the distance from intersection to light position
                double max_t = i_l.getLen();
                double lightdistsq = max_t * max_t;
                i_l.normalize();
                
                //check shadow
                Ray s_ray(p1, i_l);
                bool inShadow = false;
                
                for(auto obj : objects){
                    if(obj->intersect(s_ray, tmp, 0)){
                        if(tmp.getT1() > 0.0001 && tmp.getT1() < max_t){
                            inShadow = true;
                            break;
                        }
                    }
                }
                
                // not in shadow - the light is visible to the point on
                // the surface.
                if(!inShadow) {
                    Vector tmp_rgb;

                    //Two sided shading
#ifdef NEW_WAY
                    if (flipped) {
                        // we are looking at the back side of it - only consider
                        // lights on this side
                        tmp_rgb = Material::backShading (i_l, i_e, n, li->getRgb());
                    }

#else
                    if (i_e.dot(n) < 0.0) {
                        // we are looking at the back side of it - only consider
                        // lights on this side
                        Vector flippednorm = n;
                        flipped = true;
                        flippednorm *= -1;
                        tmp_rgb = Material::backShading (i_l, i_e, flippednorm, li->getRgb());
                    }
#endif
                    else
                        tmp_rgb = m->phongShading(i_e, n, i_l, li->getRgb());
                    
                    ret_rgb += tmp_rgb * (1.0 / lightdistsq);
                    
                }
            }
        }
        
        //add ambient if needed
        if(aLight && ray_type == 1) {
            if (flipped) {
                Vector flatyellow (1.0, 1.0, 0.0);
                ret_rgb += aLight->getRgb() * flatyellow;
            }
            else
                ret_rgb += aLight->getRgb() * m->getDiffuse();
        }
    
        //ideal specular shading
        Vector km = m->getIdealSpec();
        if(km.getLen() > 0.0 and !flipped){
            //reflected ray
            Vector rfl = n * (2 * n.dot(i_e)) - i_e;
            rfl.normalize();
            Ray r_ray(p1, rfl);
            ret_rgb += km * rayColor_0(r_ray, 2, recurse_limit - 1, lights, aLight, objects);
        }
    }
    return move(ret_rgb);
}
Vector Camera::rayColor_1(const Ray &r, int ray_type, int recurse_limit,
                          const vector<Light*> lights,
                          const AmbientLight *aLight,
                          const vector<Surface*> &objects){
    if(recurse_limit == 0)
        return move(Vector(0.0, 0.0, 0.0));
    
    //find closest intersection
    Material *m = NULL;
    Intersection it, tmp;
    
    for(auto obj : objects){
        if(obj->intersect(r, tmp, 1)){
            if(tmp.getT1() > 0.0001 && tmp.getT1() < it.getT1()){
                it = tmp;
                m = obj->getMaterial();
            }
        }
    }
    
    //color accumulator
    Vector ret_rgb(0.0, 0.0, 0.0);
    
    if(it.intersect()){
        Point p1 = it.getP1();
        
        //Normal at intersection
        Vector n = it.getNormal();
        
        //Vector from intersection to camera
        Vector i_e = r.getDir();
        i_e *= -1.0;
        
#define NEW_WAY
        
        // if it's flipped, flip the normal, and only consider lights on
        // that side of the
        bool flipped = false;
        if (i_e.dot(n) < 0.0) {
#ifdef NEW_WAY
            n *= -1.0;
#endif
            flipped = true;
        }
        
        for(auto li : lights){
            //bling-phong shading
            if (li->getType() == 'p'){
                //Vector from intersection to light position
                Vector i_l = Vector(p1, li->getPos());
                
                //t should be less than the distance from intersection to light position
                double max_t = i_l.getLen();
                double lightdistsq = max_t * max_t;
                i_l.normalize();
                
                //check shadow
                Ray s_ray(p1, i_l);
                bool inShadow = false;
                
                for(auto obj : objects){
                    if(obj->intersect(s_ray, tmp, 1)){
                        if(tmp.getT1() > 0.0001 && tmp.getT1() < max_t){
                            inShadow = true;
                            break;
                        }
                    }
                }
                
                // not in shadow - the light is visible to the point on
                // the surface.
                if(!inShadow) {
                    Vector tmp_rgb;
                    
                    //Two sided shading
#ifdef NEW_WAY
                    if (flipped) {
                        // we are looking at the back side of it - only consider
                        // lights on this side
                        tmp_rgb = Material::backShading (i_l, i_e, n, li->getRgb());
                    }
                    
#else
                    if (i_e.dot(n) < 0.0) {
                        // we are looking at the back side of it - only consider
                        // lights on this side
                        Vector flippednorm = n;
                        flipped = true;
                        flippednorm *= -1;
                        tmp_rgb = Material::backShading (i_l, i_e, flippednorm, li->getRgb());
                    }
#endif
                    else
                        tmp_rgb = m->phongShading(i_e, n, i_l, li->getRgb());
                    
                    ret_rgb += tmp_rgb * (1.0 / lightdistsq);
                    
                }
            }
        }
        
        //add ambient if needed
        if(aLight && ray_type == 1) {
            if (flipped) {
                Vector flatyellow (1.0, 1.0, 0.0);
                ret_rgb += aLight->getRgb() * flatyellow;
            }
            else
                ret_rgb += aLight->getRgb() * m->getDiffuse();
        }
        
        //ideal specular shading
        Vector km = m->getIdealSpec();
        if(km.getLen() > 0.0 and !flipped){
            //reflected ray
            Vector rfl = n * (2 * n.dot(i_e)) - i_e;
            rfl.normalize();
            Ray r_ray(p1, rfl);
            ret_rgb += km * rayColor_1(r_ray, 2, recurse_limit - 1, lights, aLight, objects);
        }
    }
    return move(ret_rgb);
}

Vector Camera::rayColor_NULL(const Ray &r, int ray_type, int recurse_limit,
                     const vector<Light*> lights,
                     const AmbientLight *aLight,
                     const vector<Surface*> &objects,
                     BVHNode &root){
    if(recurse_limit == 0)
        return move(Vector(0.0, 0.0, 0.0));
    
    //find closest intersection
    Material *m = NULL;
    Intersection it, tmp;
    
//    for(auto obj : objects){
//        if(obj->intersect(r, tmp, 1)){
//            if(tmp.getT1() > 0.0001 && tmp.getT1() < it.getT1()){
//                it = tmp;
//                m = obj->getMaterial();
//            }
//        }
//    }
    
    //color accumulator
    Vector ret_rgb(0.0, 0.0, 0.0);
    
//    if(it.intersect()){
    if (root.intersect(r, it, 0) && it.getT1() > 0.0001f) {
        
//        std::cout<<"Here"<<std::endl;
        Point p1 = it.getP1();
        
        m = it.get_Material();
//        std::cout<<m->getDiffuse()[0]<<","<<m->getDiffuse()[1]<<","<<m->getDiffuse()[2]<<std::endl;
        //Normal at intersection
        Vector n = it.getNormal();
        
        //Vector from intersection to camera
        Vector i_e = r.getDir();
        i_e *= -1.0;
        
#define NEW_WAY
        
        // if it's flipped, flip the normal, and only consider lights on
        // that side of the
        bool flipped = false;
        if (i_e.dot(n) < 0.0) {
#ifdef NEW_WAY
            n *= -1.0;
#endif
            flipped = true;
        }
        
        for(auto li : lights){
            //bling-phong shading
            if (li->getType() == 'p'){
                //Vector from intersection to light position
                Vector i_l = Vector(p1, li->getPos());
                
                //t should be less than the distance from intersection to light position
                double max_t = i_l.getLen();
                double lightdistsq = max_t * max_t;
                i_l.normalize();
                
                //check shadow
                Ray s_ray(p1, i_l);
                bool inShadow = false;
                
//                for(auto obj : objects){
//                    if(obj->intersect(s_ray, tmp, 0)){
//                        if(tmp.getT1() > 0.0001 && tmp.getT1() < max_t){
//                            inShadow = true;
//                            break;
//                        }
//                    }
//                }
                if (root.intersect(s_ray, tmp, 0) && tmp.getT1() > 0.0001f) {
                    inShadow = true;
                }
                
                // not in shadow - the light is visible to the point on
                // the surface.
                if(!inShadow) {
                    Vector tmp_rgb;
                    
                    //Two sided shading
#ifdef NEW_WAY
                    if (flipped) {
                        // we are looking at the back side of it - only consider
                        // lights on this side
                        tmp_rgb = Material::backShading (i_l, i_e, n, li->getRgb());
                    }
                    
#else
                    if (i_e.dot(n) < 0.0) {
                        // we are looking at the back side of it - only consider
                        // lights on this side
                        Vector flippednorm = n;
                        flipped = true;
                        flippednorm *= -1;
                        tmp_rgb = Material::backShading (i_l, i_e, flippednorm, li->getRgb());
                    }
#endif
                    else
                        tmp_rgb = m->phongShading(i_e, n, i_l, li->getRgb());
                    
                    ret_rgb += tmp_rgb * (1.0 / lightdistsq);
                    
                }
            }
        }
        
        //add ambient if needed
        if(aLight && ray_type == 1) {
            if (flipped) {
                Vector flatyellow (1.0, 1.0, 0.0);
                ret_rgb += aLight->getRgb() * flatyellow;
            }
            else
                ret_rgb += aLight->getRgb() * m->getDiffuse();
        }
        
        //ideal specular shading
        Vector km = m->getIdealSpec();
        if(km.getLen() > 0.0 and !flipped){
            //reflected ray
            Vector rfl = n * (2 * n.dot(i_e)) - i_e;
            rfl.normalize();
            Ray r_ray(p1, rfl);
            ret_rgb += km * rayColor_NULL(r_ray, 2, recurse_limit - 1, lights, aLight, objects, root);
        }
    }
    return move(ret_rgb);
}

//Write result to output file
void Camera::writeFile(const char outfile[]){
    cout << "writing output image." << endl;
    RgbaOutputFile file (outfile, _pw, _ph, WRITE_RGBA);
    file.setFrameBuffer (&_pixels[0][0], 1, _pw);
    file.writePixels (_ph);
    cout << "done." << endl;
}
