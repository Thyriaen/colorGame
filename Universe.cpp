//
// Created by thyriaen on 08.10.18.
//

#include "Universe.h"

#include <iostream>

Universe::Universe(unsigned int initWidth, unsigned int initHeight)
    : width(initWidth)
    , height(initHeight) {
    pixels.resize(initHeight);
    for(int i = 0; i < initHeight; i++) {
        pixels[i] = std::vector<Point>(initWidth);
    }
}

// empty universe
Universe::Universe()
    : width(0)
    , height(0) {
}

void Universe::init(unsigned int initWidth, unsigned int initHeight) {
    width = initWidth;
    height = initHeight;
    pixels.resize(initHeight);
    for(int i = 0; i < initHeight; i++) {
        pixels[i] = std::vector<Point>(initWidth);
    }
}

void Universe::setPixel(int x, int y, Point p) {
    pixels[y][x] = p;
}

void Universe::setPixels(unsigned char* rawPixels) {
    int size = width * height * 4;
    int x = 0;
    int y = 0;
    for(auto i = 0; i < size; i+=4) {
        setPixel(x,y,Point(rawPixels[i+2], rawPixels[i+1], rawPixels[i]));
        if(++x >= getWidth()) {
            x = 0;
            y++;
        }
    }
}

unsigned int Universe::getHeight() {
    return height;
};

unsigned int Universe::getWidth() {
    return width;
};


/**
 * @return right format: blue, green, red, alpha
 */
std::vector<unsigned char> Universe::getRaw() {

    std::vector<unsigned char> rawPixels(width * height * 4, 0);
    unsigned int x = 0;
    unsigned int y = 0;

    for(auto it = rawPixels.begin(); it != rawPixels.end(); it+=4) {
        *(it) = pixels[y][x].getBlue();
        *(it+1) = pixels[y][x].getGreen();
        *(it+2) = pixels[y][x].getRed();

        if(++x == width) {
            x = 0;
            y++;
        }
     }

    return rawPixels;
}
