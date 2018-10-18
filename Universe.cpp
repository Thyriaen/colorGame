//
// Created by thyriaen on 08.10.18.
//

#include "Universe.h"
#include <algorithm>
#include <iostream>

Universe::Universe(unsigned int initWidth, unsigned int initHeight)
    : width(initWidth)
    , height(initHeight) {
    pixels.resize(initHeight * initWidth * 4, 0);
}

// empty universe
Universe::Universe()
    : width(0)
    , height(0) {
}

void Universe::init(unsigned int initWidth, unsigned int initHeight) {
    width = initWidth;
    height = initHeight;
    pixels.resize(initHeight * initWidth * 4, 0);
}

void Universe::setPixel(unsigned int x, unsigned int y, unsigned char red, unsigned char green, unsigned char blue) {
    unsigned int offset = ( width * 4 * y ) + x * 4;
    pixels[offset] = blue;
    pixels[offset + 1] = green;
    pixels[offset + 2] = red;
}

void Universe::setPixels(unsigned char* rawPixels) {
    int size = width * height * 4;
    for(int i = 0; i < size; i++) {
       pixels[i] = *(rawPixels+i);
    }
}

unsigned int Universe::getHeight() {
    return height;
};

unsigned int Universe::getWidth() {
    return width;
};

std::vector<unsigned char> Universe::getPixels() {
    return pixels;
}

int Universe::getDistance(int x1, int y1, int x2, int y2) {
    return std::max(abs(x1-x2), abs(y1-y2));
}

unsigned char Universe::getOrientation(int fromX, int fromY, int toX, int toY) {
    int x = toX - fromX;
    int y = toY - fromY;

    unsigned char direction = 0;
    // todo
    return  direction;
}


void Universe::whitenessOnly() {
    for(auto it = pixels.begin(); it != pixels.end(); it+=4) {
        unsigned char whiteness = std::min({*(it), *(it+1), *(it+2)});
        *(it) = whiteness;
        *(it+1) = whiteness;
        *(it+2) = whiteness;
    }
}