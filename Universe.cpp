//
// Created by thyriaen on 08.10.18.
//

#include "Universe.h"

#include <iostream>

Universe::Universe(unsigned int initWidth, unsigned int initHeight)
    : width(initWidth)
    , height(initHeight) {
    std::vector<std::vector<Point>> pixels(initHeight);
    for(int i = 0; i < initHeight; i++) {
        pixels[i] = std::vector<Point>(initWidth);
    }
}


std::vector<unsigned char> Universe::getRaw() {
    std::vector<unsigned char> rawPixels(width * height * 4, 0);




    unsigned int x = 0;
    unsigned int y = 0;

    for(auto it = rawPixels.begin(); it != rawPixels.end(); it+=4) {

        std::cout << "(" << x << "," << y << ")" << std::endl;

        /*
            const unsigned int x = ( i / 4 ) % width;
            const unsigned int y = i / ( 4 * width );

            std::vector<unsigned char> rawPoint = pixels[x][y].getRaw();
            rawPixels.insert(it, rawPoint.begin(), rawPoint.end());

            i++;

         */
        if(++x == width) {
            x = 0;
            y++;
        }

     }

    return rawPixels;
}
