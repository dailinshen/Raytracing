//
//  main.cpp
//  hw1.5_ds3420
//
//  Created by lindashen on 11/17/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#include "parser.h"

int main (int argc, char *argv[])
{
    
    if (argc != 5) {
        cerr << "useage: raytra scenefilename output_path pRayNum sRayNum" << endl;
        return -1;
    }
    
    Readscene rs;
    clock_t tStart = clock();
    rs.parseSceneFile (argv[1], argv[2], argv[3], argv[4]);
    double tend =(double)(clock() - tStart)/CLOCKS_PER_SEC;
    cout<<"Done!" <<endl;
    cout<<"Time taken: " << tend <<endl;
    return 0;
}


