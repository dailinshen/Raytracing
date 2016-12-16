//
//  main.cpp
//  hw2
//
//  Created by lindashen on 10/13/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#include <iostream>

#include <vector>

#include "surface.h"
#include "camera.h"
#include "parser.h"
#include "material.h"
#include "light.h"
int main (int argc, const char * argv[])
{
    
    if (argc != 3) {
        // error condition:
        std::cout << "usage: raytra scenefile outputimage" << std::endl;
    }
    
    std::vector< Surface * > surfaces;
    std::vector< Light * > lights;
    std::vector< Material * > materials;
    Camera cam;
    
    // make a default material, which objects get if they are defined
    // before any material is. the default material is material 0.
    Material *default_material = new Material;
    materials.push_back (default_material);
    
    Parser parser;
    
//    parser.parse (argv[1], surfaces, lights, materials, cam);
    parser.parse ("/Users/lindashen/Desktop/Columbia University/2016 Fall/Computer Science/Computer Graphics/Assignments/02_10_13/scene_file.txt", surfaces, lights, materials, cam);
    
    std:: cout << "read in: " << surfaces.size () << " surfaces, " <<
    materials.size () - 1 << " materials." << std::endl;
    
//    assert (surfaces.size () != 0); // make sure there are some surfaces
    
//    cam.renderScene (surfaces, lights, materials);
    cam.writeImage ("/Users/lindashen/Desktop/image.exr");
    cam.writeImage (argv[2]);
    for (Surface *s : surfaces)
        delete s;
    for (Light *l : lights)
        delete l;
    
    for (Material * m : materials)
        delete m;
    
    
}
