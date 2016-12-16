//
//  main.cpp
//  hw3
//
//  Created by lindashen on 10/18/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#include <iostream>
#include <vector>

#include "surface.h"
#include "material.h"
#include "light.h"
#include "camera.h"
#include "parser.h"
#include "pointlight.h"


int main (int argc, const char * argv[])
{
    
    if (argc != 3) {
        // error condition:
        std::cout << "usage: raytra scenefile outputimage" << std::endl;
        return -1;
    }
    
    std::vector< Surface * > surfaces;
    std::vector< Material * > materials;
    std::vector< Light * > lights;
    

    // make a default material, which objects get if they are defined
    // before any material is. the default material is material 0.
    Material *default_material = new Material;
    materials.push_back (default_material);
    
    Camera cam;
    Parser parser;
 //   parser.parse ("/Users/lindashen/Desktop/Columbia University/2016 Fall/Computer Science/Computer Graphics/Assignments/04_10_27/scene_file.txt", surfaces, lights, materials, cam);
    parser.parse (argv[1], surfaces, lights, materials, cam);
    
//    assert (surfaces.size () != 0); // mae sure there are some surfaces
    
    std:: cout << "read in: " << surfaces.size () << " surfaces, " <<
    lights.size () << " lights, " << materials.size () - 1 << " materials."
    << std::endl;
    
    // if there is no light defined in the scene file, just make one
    // colocated with the camera, and white:
    if(lights.size() == 0) {
        Vector lightcolor (1., 1., 1.);
        PointLight *defaultlight = new PointLight (cam.position (), lightcolor);
        lights.push_back(defaultlight);
        std::cout << "note: no lights! using default light." << std::endl;
    }
    
    
    cam.renderScene (surfaces, lights, materials);
    cam.writeImage (argv[2]);
 //   cam.writeImage ("/Users/lindashen/Desktop/image.exr");
    
    for (Surface * s : surfaces)
        delete s;
    
    for (Light * l: lights)
        delete l;

    for (Material * m : materials)
        delete m;
}









