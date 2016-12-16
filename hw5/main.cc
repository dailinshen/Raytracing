//
//  main.cc
//  Raytra
//
//  Created by Qi Wang on 2/5/16.
//  Copyright © 2016 Wang Qi. All rights reserved.
//
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "Light.h"
#include "Surface.h"
#include "Camera.h"

void parseSceneFile (char *filnam, Camera **myCam, vector<Surface*> &objects,
                     vector<Light*> &lights, AmbientLight **aLight,
                     vector<Material*> &materials);

int main(int argc, char * argv[]) {
//    if (argc != 3) {
//        cerr << "useage: raytra scenefilename" << endl;
//        return -1;
//    }
    char *scenefile = argv[1];
    char *outfile = argv[2];
    
    clock_t start = clock();
    
    std::vector<Surface*> objects;
    Camera *myCam = NULL;
    std::vector<Material*> materials;
    AmbientLight *aLight = NULL;
    std::vector<Light*> lights;
    
    parseSceneFile(scenefile, &myCam, objects, lights, &aLight, materials);

    
    std::cout<<objects.size()<<" objects."<<std::endl;
//    char *file = argv[3];
    int mode = -1;
    if (argv[3] != NULL) {
        mode = int(*argv[3]) - 48;
    }
    int AXIS = 0;
    BVHNode root(objects, AXIS);
//    if (mode == -1){
//        if (!(root = dynamic_cast<BVHNode *>(
//                                             create_bvh_tree(objects.begin(), objects.end()))))
//        {
//            root = new BVHNode(objects.begin(), objects.end());
//            root->_left = objects[0];
//        }
//        BVHNode(<#std::vector<Surface *> &objects#>, <#int &AXIS#>)
//    }
    
    
    myCam->render(objects, lights, aLight, mode, root);
    myCam->writeFile(outfile);
    
    delete myCam; delete aLight;
    
    for(auto obj : objects)
        delete obj;
    objects.clear();
    
    for(auto m : materials)
        delete m;
    materials.clear();
    
    for(auto li : lights)
        delete li;
    lights.clear();
    
    double duration = (clock() - start) / (double) CLOCKS_PER_SEC;
    cout<< duration << "s" << endl;
    return 0;
}
