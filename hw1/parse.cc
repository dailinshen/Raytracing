//
//  parse.cpp
//  hw1_ds3420
//
//  Created by lindashen on 9/28/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include "parse.h"

using namespace std;

//void Parser::start(const char *file) {
void Parser::start(const char *file, char *path_) {

    Camera camera;
    camera.path(path_);
    vector<Surface *> surface;
    parse(file, surface, camera);
    camera.render(surface);
}

void Parser::parse(const char *file, vector<Surface *> &surfaces, Camera &cameras) {
    ifstream in(file);
    char buffer[1025];
    string cmd;
    Material mm;
    for (int line=1; in.good(); line++) {
        in.getline(buffer,1024);
        buffer[in.gcount()]=0;
        
        cmd="";
        
        istringstream iss(buffer);
        
        iss >> cmd;
        if (cmd[0]=='/' or cmd.empty()) {
            continue;
        } else if (cmd=="s") {
            float3 pos; float r;
            iss >> pos >> r;
            
            Surface *temp = sphere(pos,r);
            temp->material(mm);
            surfaces.push_back(temp);
//            surfaces.push_back(temp);
        } else if (cmd=="t") {
//            float3 a,b,c;
//            iss >> a,b,c;
//            triangle(a,b,c);
        } else if (cmd=="p") {
            float3 n; float d;
            iss >> n >> d;
//            surfaces.push_back(plane(n,d));
//            surfaces.push_back(plane(n,d));
        } else if (cmd=="c") {
            float3 pos,dir; float d,iw,ih; int pw,ph;
            iss >> pos >> dir >> d >> iw >> ih >> pw >> ph;
            camera(pos,dir,d,iw,ih,pw,ph,cameras, surfaces);
        } else if (cmd=="l") {
            iss >> cmd;
            if (cmd=="p") {
//                float3 pos,rgb;
//                iss >> pos >> rgb;
//                pointLight(pos,rgb);
            } else if (cmd=="d") {
//                float3 dir,rgb;
//                iss >> dir >> rgb;
//                directionalLight(dir,rgb);
            } else if (cmd=="a") {
//                float3 rgb;
//                iss >> rgb;
//                ambientLight(rgb);
            } else {
                cout << "Parser error: invalid light at line " << line << endl;
            }
        } else if (cmd=="m") {
            float3 diff,spec,refl; float r;
            iss >> diff >> spec >> r >> refl;
            mm = material(diff,spec,r,refl);
        } else {
            cout << "Parser error: invalid command at line " << line << endl;
        }
    }
    
    in.close();
}
Surface *Parser::sphere(float3 pos, float r) {
    Point origin(pos.x, pos.y, pos.z);
    return new Sphere(origin, r);
}
Plane *Parser::plane(float3 n, float d) {
//    Vector normal(n.x, n.y, n.z);
//    return new Plane(normal, d);
    return NULL;
}
void Parser::camera(float3 pos, float3 dir, float d, float iw, float ih, int pw, int ph, Camera &cameras, vector<Surface *> &surfaces) {
    float e_x = pos.x, e_y = pos.y, e_z = pos.z, focal_length = d, dx = dir.x, dy = dir.y, dz = dir.z, iw_ = iw, ih_ = ih;
    cameras.configuration(e_x, e_y, e_z, focal_length, dx, dy, dz, pw, ph, iw_, ih_);
//    return cameras.configuration(e_x, e_y, e_z, focal_length, dx, dy, dz, pw, ph, iw_, ih_);
}
Material Parser::material(float3 diff, float3 spec, float r, float3 refl) {
    return Material(diff.x, diff.y, diff.z, spec.x, spec.y, spec.z,
                    r, refl.x, refl.y, refl.z);
}

