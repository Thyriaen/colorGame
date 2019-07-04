#include "Universe.h"
#include <algorithm>
#include <iostream>
#include <cmath>

#define FS 40
// calculation will be easy if this is a power of two

// requires width and height divisible by 40
Universe::Universe(unsigned int initWidth, unsigned int initHeight)
    : width(initWidth)
    , height(initHeight) {
    pixels.resize(initHeight * initWidth * 4, 0);
    fieldSize = FS;
    xFields = width / fieldSize;
    yFields = height / fieldSize;
    fields = xFields * yFields;
    world.resize(initHeight * initWidth);
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
    world.resize(initHeight * initWidth);
    fieldSize = FS;
    xFields = width / fieldSize;
    yFields = height / fieldSize;
    fields = xFields * yFields;
}

void Universe::setPixels(const unsigned char* rawPixels) {
    int size = width * height * 4;
    for(int i = 0; i < size; i++) {
       pixels[i] = *(rawPixels+i);
    }
}

unsigned int Universe::getHeight() {
    return height;
}

unsigned int Universe::getWidth() {
    return width;
}

std::vector<unsigned char> Universe::getPixels() {
    return pixels;
}

int Universe::getDistance(int x1, int y1, int x2, int y2) {
    return std::max(abs(x1-x2), abs(y1-y2));
}

// blue, green ,red
void Universe::makeWorld() {
    int i = 0;
    for(auto it = pixels.begin(); it != pixels.end(); it+=4) {
        unsigned char whiteness = std::min({*(it), *(it+1), *(it+2)});
        world[i].whiteness = whiteness;
        world[i].blue = *(it) - whiteness;
        world[i].green = *(it+1) - whiteness;
        world[i].red = *(it+2) - whiteness;
        i++;
    }
}

void Universe::makePixels() {
    int i = 0;
    for(auto it = pixels.begin(); it != pixels.end(); it+=4) {
        unsigned char whiteness = world[i].whiteness;
        *(it) = whiteness + world[i].blue;
        *(it+1) = whiteness + world[i].green;
        *(it+2) = whiteness + world[i].red;
        i++;
    }
}

void Universe::next() {
    //std::vector<unsigned char> newPixels(pixels);

    std::vector<int> repValues(fields * 4);
    std::vector<int> repX(fields * 4);
    std::vector<int> repY(fields * 4);

    //drawGrid();
    //makeWorld();
    //makePixels();

    //pixels = newPixels;
}

void Universe::whitenessOnly() {
    for(auto it = pixels.begin(); it != pixels.end(); it+=4) {
        unsigned char whiteness = std::min({*(it), *(it+1), *(it+2)});
        *(it) = whiteness;
        *(it+1) = whiteness;
        *(it+2) = whiteness;
    }
}

void Universe::drawGrid() {
    for(auto it = pixels.begin(); it != pixels.end(); it+=4*FS) {
        *(it) = 0;
        *(it+1) = 0;
        *(it+2) = 255;
    }

}
