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

long Universe::getForcePart(int fromX, int fromY, int toX, int toY, int Value) {

    int distance = getDistance(fromX, fromY, toX, toY);
    return (Value / distance);

}


long Universe::getForce(int fromX, int fromY, int toX, int toY, int fromValue, int toValue) {

    int distance = getDistance(fromX, fromY, toX, toY);
    return (fromValue * toValue / distance) >> 8;

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

void Universe::makeStruct() {
    int i = 0;
    for(auto it = pixels.begin(); it != pixels.end(); it+=4) {
        unsigned char whiteness = std::min({*(it), *(it+1), *(it+2)});
        *(it) = whiteness;
        *(it+1) = whiteness;
        *(it+2) = whiteness;
        i++;
    }
}


// maybe use iterators
void Universe::calculateRepresentative(int startIndex, int* repValue, int* repX, int* repY) {

    std::vector<int> xWeights(fieldSize * 4);
    std::vector<int> yWeights(fieldSize * 4);

    for(int y = 0; y < fieldSize; y++) {
        for(int x = 0; x < fieldSize; x++) {
            int offset = startIndex + (( width * y +  x) << 2);

            *repValue += pixels[offset];
            *(repValue + 1) += pixels[offset+1];
            *(repValue + 2) += pixels[offset+2];

            xWeights[y] += pixels[offset];
            xWeights[y+1] += pixels[offset+1];
            xWeights[y+2] += pixels[offset+2];

            yWeights[x] += pixels[offset];
            yWeights[x+1] += pixels[offset+1];
            yWeights[x+2] += pixels[offset+2];
        }
    }

    for(int i = 1; i < xWeights.size(); i+=4) {
        int index = i >> 2;
        *repX += index * xWeights[i];
        *(repX+1) += index * xWeights[i];
        *(repX+2) += index * xWeights[i];

        *repY += index * yWeights[i];
        *(repY+1) += index * yWeights[i];
        *(repY+2) += index * yWeights[i];
    }

    for(int i = 0; i<3; i++) {
        if(*(repValue+i) == 0)  {
            *(repX+i) = 0;
            *(repY+i) = 0;
        } else {
            *(repX+i) /= *(repValue+i);
            *(repY+i) /= *(repValue+i);
        }
    }

}

void Universe::calculateForces(std::vector<int> repValues, std::vector<int> repX, std::vector<int> repY, std::vector<int> &forceX, std::vector<int> &forceY) {

    int aField = 0;
    int bField = 0;

    for(int aY = 0; aY < fieldSize; aY++) {
        for (int aX = 0; aX < fieldSize; aX++) {
            long forcePart = 0;
            for(int bY = 0; bY < fieldSize; bY++) {
                for (int bX = 0; bX < fieldSize; bX++) {
                    if(bX != aX || bY != aY) {
                        forcePart += getForcePart(repX[aField],repY[aField], repX[bField], repY[bField], repValues[bField]);
                    }


                    bField++;
                }
            }


            aField++;
        }
    }




}


void Universe::calculateRepresentatives(std::vector<int> &repValues, std::vector<int> &repX, std::vector<int> &repY) {

    int field = 0;
    for(int y = 0; y < yFields; y++) {
        for(int x = 0; x < xFields; x++) {
            int offset = ( x + y * width ) * fieldSize * 4;
            calculateRepresentative(offset, &repValues[field], &repX[field], &repY[field] );
            field++;
        }
    }

}

void Universe::next() {
    std::vector<unsigned char> newPixels(pixels);

    std::vector<int> repValues(fields * 4);
    std::vector<int> repX(fields * 4);
    std::vector<int> repY(fields * 4);

    //makeWorld();
    //calculateRepresentatives(repValues, repX, repY);
    makePixels();
    //makeStruct();



    pixels = newPixels;
}



/*
void Universe::next2() {
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
                forceX += int(1024.0 / distanceX) * (whiteness >> 5);
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
*/

void Universe::whitenessOnly() {
    for(auto it = pixels.begin(); it != pixels.end(); it+=4) {
        unsigned char whiteness = std::min({*(it), *(it+1), *(it+2)});
        *(it) = whiteness;
        *(it+1) = whiteness;
        *(it+2) = whiteness;
    }
}
