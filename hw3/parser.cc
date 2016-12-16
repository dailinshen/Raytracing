//
//  parser.cpp
//  hw3
//
//  Created by lindashen on 10/18/16.
//  Copyright © 2016 lindashen. All rights reserved.
//


#include <iostream>
#include <fstream>

#include "parser.h"

#include "material.h"
#include "vector.h"
#include "point.h"
#include "sphere.h"
#include "triangle.h"
#include "pointlight.h"
#include "light.h"
#include "plane.h"

using namespace std;


// In this code, you can see how Sphere and Camera are set up - you
// will need to do similar for the other classes.
//
// You will also need to keep track of the last material defined, so
// that you can connect it to any surfaces that are subsequently defined.
//
void Parser::parse (
                    const char *file,
                    std::vector< Surface * > &surfaceVector,
                    std::vector< Light * > &lightVector,
                    std::vector< Material * > &materialVector,
                    Camera &cam)
{
    
    ifstream in(file);
    char buffer[1025];
    string cmd;
    
    int num_cams = 0; // keep track of how many cameras we read in
    
    // this is the index of the current material - zero is the
    // default material.
    int currentMaterial = 0;
    
    for (int line=1; in.good(); line++) {
        in.getline(buffer,1024);
        buffer[in.gcount()]=0;
        
        Surface *thisSurface = 0;
        Light *thisLight = 0;
        cmd="";
        
        istringstream iss(buffer);
        
        iss >> cmd;
        
        if (cmd[0]=='/' or cmd.empty()) {
            // ignore comments or blank lines
            continue;
        }
        else if (cmd=="s") {
            // Sphere:
            
            // read in the parameters:
            Point pos;
            double r;
            iss >> pos >> r;
            
            // construct it:
            // at the end of this loop, we put any newly-constructed surfaces
            // into the surfaceVector.
            thisSurface = new Sphere(pos, r);
        }
        else if (cmd=="t") {
            // Triangle
            Point a, b, c;
            iss >> a >> b >> c;
            thisSurface = new Triangle(a, b, c);
        }
        else if (cmd=="p") {
            // Plane
            
            // read in the parameters:
            Vector n;
            double d;
            iss >> n >> d;
            
            // construct it:
            thisSurface = new Plane (n,d);
        }
        else if (cmd=="c") {
            // Camera:
            ++num_cams; // keep track of how many we read in
            // read in the parameters:
            Point pos;
            Vector dir;
            double d,iw,ih;
            int pw,ph;
            iss >> pos >> dir >> d >> iw >> ih >> pw >> ph;
            
            // construct it:
            cam.init (pos,dir,d,iw,ih,pw,ph);
        }
        else if (cmd=="l") {
            iss >> cmd;
            if (cmd=="p") {
                Point pos;
                Vector color;
                iss >> pos >> color;
                thisLight = new PointLight(pos, color);
            }
            else {
                cout << "Parser error: invalid light at line " << line << endl;
            }
        }
        else if (cmd=="m") {
            // Material:
            
            // read in the parameters:
            Vector diff,spec,refl;
            double r;
            iss >> diff >> spec >> r >> refl;
            
            // construct it, and put it in the materials list:
            Material *thismat = new Material (diff, spec, refl, r);
            materialVector.push_back (thismat);
            
            // geometry defined after this has to get the correct index
            // into the material list:
            ++currentMaterial;
        }
        else {
            std::cerr << "Parser error: invalid command at line " << line << endl;
        }
        
        // if we found a surface, add it to the list of surfaces:
        if (thisSurface) {
            surfaceVector.push_back (thisSurface);
            thisSurface->setMaterialIndex (currentMaterial);
        }
        if(thisLight) {
            lightVector.push_back(thisLight);
        }
    }
    
    in.close();
    
    // make sure we read in 1 camera, no more no less 8).
    if (num_cams != 1) {
        std::cerr << "scene file error: exactly ONE camera must be defined." << endl;
    }
}


