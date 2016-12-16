//
//  main.cpp
//  hw0
//
//  Created by lindashen on 9/18/16.
//  Copyright © 2016 lindashen. All rights reserved.
//

#include "exr_header.h"

void writeRgba(const char fileName[], const Rgba *pixels, int width, int height){
    //Write an RGBA image using class RgbaOutputFile
    //
    // - open the file
    // - describe the memory layout of the pixels
    // - store the pixels in the file
    
    RgbaOutputFile file (fileName, width, height, WRITE_RGBA);
    file.setFrameBuffer(pixels, 1, width);
    file.writePixels(height);
}

void readRgba(const char fileName[], Array2D<Rgba> &pixels, int &width, int &height){
    //Read an RGBA image using class RgbaInputFile:
    // - open the file
    // - allocate memory for the pixels
    // - describe the memory layout of the pixels
    // - read the pixels from the file
    
    RgbaInputFile file (fileName);
    Box2i dw = file.dataWindow();
    
    width = dw.max.x - dw.min.x + 1;
    height = dw.max.y - dw.min.y + 1;
    pixels.resizeErase(height, width);
    
    file.setFrameBuffer(&pixels[0][0] - dw.min.x - dw.min.y * width, 1, width);
    file.readPixels(dw.min.y, dw.max.y);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    
    try{
        cout << "reading an image ... " << argv[1] << endl;
        
        int w, h;
        Array2D<Rgba> p;
        
        // You should test for file existence before this!
        
        
        readRgba(argv[1], p, w, h);
        //readRgba("/Users/lindashen/Downloads/stilllife.exr", p, w, h);
        
        cout << "Image width and height is: " << w << " and " << h << endl;
        
        // retain a single color
        for (int y = 0; y < h; ++y){
            for (int x = 0; x < w; ++x){
                Rgba &px = p[y][x];  //get the pixel we are interested in
                
                if ((x <= floor (w / 3)) && (y <= floor (h / 2))){
                    //px.r += (px.r + px.b + px.g) / 3.0;
                    //zero everything except the red channel
                    px.g = 0;
                    px.b = 0;
                    px.a = 1;
                }
                else if ((x > floor (w / 3)) && (y <= floor (h / 2))){
                    //px.g += (px.r + px.b + px.g) / 3.0;
                    //zero everything except the green channel
                    px.r = 0;
                    px.b = 0;
                    px.a = 1;
                }
                else if ((x <= floor (w / 3)) && (y > floor(h / 2))){
                    //px.b += (px.r + px.b + px.g) / 3.0;
                    //zero everything except the blue channel
                    px.r = 0;
                    px.g = 0;
                    px.a = 1;
                }
                else{
                    // stick to the relative luminance: l = 0.2126r + 0.7152g + 0.0722b.
                    // each channel should have the same value
                    float l;
                    l = 0.2126 * px.r + 0.7152 * px.g + 0.0722 * px.b;
                    px.r = l;
                    px.b = l;
                    px.g = l;
                    px.a = 1;
                }
            }
        }
        
        cout << "writing output image" << endl;
        
        writeRgba("hw0.exr", &p[0][0], w, h);
        
        cout << "done." << endl;
    }
    
    catch(const std:: exception &exc){
        std:: cerr << exc.what() << std:: endl;
        return 1;
    }
    
    return 0;
}
