//
// Created by thyriaen on 08.10.18.
//

#include "Universe.h"
#include <algorithm>
#include <iostream>
#include <cmath>

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

/*
 *  SOUTHWEST = 0
 *  WEST = 1
 *  NORTH = 2
 *  NORTHWEST = 3
 *  SOUTH = 4
 *  SOUTHEAST = 5
 *  NORTHEAST = 6 
 *  EAST = 7
 */
unsigned char Universe::getOrientation(int fromX, int fromY, int toX, int toY) {
    int x = toX - fromX;
    int y = toY - fromY;

    if(y == 0 && x > 0) {
        return 7;
    }
    if(x == 0 && y < 0) {
        return 4;
    }

    unsigned char direction = 0;
    if(x > 0) {
        direction += 4;
    }
    if(y > 0) {
        direction += 2;
    }
    if(abs(x) > abs(y) || (abs(x) == abs(y) && std::signbit(x) != std::signbit(y))) {
        direction += 1;
    }

    return  direction;
}

int Universe::getForce(int fromX, int fromY, int toX, int toY) {
    int distance = getDistance(fromX, fromY, toX, toY);
    if(distance >= 255) {
        return 0;
    }
    return distance >> 5;
}

void Universe::next() {
    std::vector<unsigned char> newPixels(pixels);
    int toX = 0;
    int toY = 0;

    for(int i = 0; i < pixels.size(); i+=4) {
        int forceX = 0;
        int forceY = 0;

        int fromX = 0;
        int fromY = 0;
        for(int j = 0; j < pixels.size(); j+=4) {
            if(i != j) {
                int distanceX = fromX - toX;
                int distanceY = fromY - toY;
                unsigned char whiteness = std::min({pixels[i], pixels[i+1], pixels[i+2]});
                forceX += int(1024.0 / distanceX * (whiteness >> 5);
                forceY += int(1024.0 / distanceY) * (whiteness >> 5);

                if( ++fromX > width ) {
                    fromX = 0;
                    fromY++;
                }
            }
        }


        if( ++toX > width ) {
            toX = 0;
            toY++;
        }
    }
    pixels = newPixels;
}

/*
 *  SOUTHWEST = 0
 *  NORTHEAST = 6

 *  NORTH = 2
 *  SOUTH = 4

 *  NORTHWEST = 3
 *  SOUTHEAST = 5

 *  WEST = 1
 *  EAST = 7
 */




void Universe::whitenessOnly() {
    for(auto it = pixels.begin(); it != pixels.end(); it+=4) {
        unsigned char whiteness = std::min({*(it), *(it+1), *(it+2)});
        *(it) = whiteness;
        *(it+1) = whiteness;
        *(it+2) = whiteness;
    }
}