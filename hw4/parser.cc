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
#include "ambientlight.h"
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
    
    unsigned long n;
    std::vector<int> tris;
    std::vector<float> verts;
    Point aa, bb, cc;
    
    
    Vector diffuse{1,1,0}, specular{0,0,0}, reflective{0,0,0};
    double exponent = 0;
    Material *thismat = new Material (diffuse, specular, reflective, exponent);
    materialVector.push_back (thismat);
    currentMaterial += 1;
    
    
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
            } else if (cmd=="a") {
                Vector rgb;
                iss >> rgb;
                thisLight = new AmbientLight(rgb);
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
        else if (cmd=="w") {
            //Read OBJ file
            string file_path;
            iss >> file_path;
            read_wavefront_file(file_path.c_str(), tris, verts);
            n = tris.size() / 3;
            for (unsigned long i = 0; i < n; ++i) {
                aa.x(verts[3 * tris[3 * i]]);
                aa.y(verts[3 * tris[3 * i] + 1]);
                aa.z(verts[3 * tris[3 * i] + 2]);
                bb.x(verts[3 * tris[3 * i + 1]]);
                bb.y(verts[3 * tris[3 * i + 1] + 1]);
                bb.z(verts[3 * tris[3 * i + 1] + 2]);
                cc.x(verts[3 * tris[3 * i + 2]]);
                cc.y(verts[3 * tris[3 * i + 2] + 1]);
                cc.z(verts[3 * tris[3 * i + 2] + 2]);
                thisSurface = new Triangle(aa, bb, cc);
                surfaceVector.push_back(thisSurface);
                thisSurface->setMaterialIndex(currentMaterial);
            }
        }
        else {
            std::cerr << "Parser error: invalid command at line " << line << endl;
        }
        
        // if we found a surface, add it to the list of surfaces:
        if (thisSurface && cmd != "w") {
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





// Given the name of a wavefront (OBJ) file that consists JUST of
// vertices, triangles, and comments, read it into the tris and verts
// vectors.
//
// tris is a vector of ints that is 3*n long, where n is the number of
// triangles. The ith triangle has vertex indexes 3*i, 3*i+1, and 3*i+2.
//
// The ith triangle has vertices:
//
//     verts[3*tris[3*i]], verts[3*tris[3*i]+1], verts[3*tris[3*i]+2],
//     verts[3*tris[3*i+1]], verts[3*tris[3*i+1]+1], verts[3*tris[3*i+1]+2],
//     verts[3*tris[3*i+2]], verts[3*tris[3*i+2]+1], verts[3*tris[3*i+2]+2]
//
// given in counterclockwise order with respect to the surface normal
//
// If you are using the supplied Parser class, you should probably make this
// a method on it: Parser::read_wavefront_file().
//
void Parser::read_wavefront_file (
                          const char *file,
                          std::vector< int > &tris,
                          std::vector< float > &verts){
    
    // clear out the tris and verts vectors:
    tris.clear ();
    verts.clear ();
    
    ifstream in(file);
    char buffer[1025];
    string cmd;
    
    
    for (int line=1; in.good(); line++) {
        in.getline(buffer,1024);
        buffer[in.gcount()]=0;
        
        cmd="";
        
        istringstream iss (buffer);
        
        iss >> cmd;
        
        if (cmd[0]=='#' or cmd.empty()) {
            // ignore comments or blank lines
            continue;
        }
        else if (cmd=="v") {
            // got a vertex:
            
            // read in the parameters:
            double pa, pb, pc;
            iss >> pa >> pb >> pc;
            
            verts.push_back (pa);
            verts.push_back (pb);
            verts.push_back (pc);
        }
        else if (cmd=="f") {
            // got a face (triangle)
            
            // read in the parameters:
            int i, j, k;
            iss >> i >> j >> k;
            
            // vertex numbers in OBJ files start with 1, but in C++ array
            // indices start with 0, so we're shifting everything down by
            // 1
            tris.push_back (i-1);
            tris.push_back (j-1);
            tris.push_back (k-1);
        }
        else {
            std::cerr << "Parser error: invalid command at line " << line << std::endl;
        }
        
    }
    
    in.close();
    
    //   std::cout << "found this many tris, verts: " << tris.size () / 3.0 << "  " << verts.size () / 3.0 << std::endl;
}





