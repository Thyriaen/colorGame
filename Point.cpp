//
// Created by thyriaen on 08.10.18.
//

#include "Point.h"
#include <algorithm>
#include <assert.h>
#include <stdexcept>

Point::Point() {
    red = 0;
    green = 0;
    blue = 0;
}

Point::Point(unsigned char red, unsigned char green, unsigned char blue) {
    this->red = red;
    this->green = green;
    this->blue = blue;
}

unsigned char Point::getRed() {
    return red;
}
unsigned char Point::getGreen() {
    return green;
}
unsigned char Point::getBlue() {
    return blue;
}


void Point::setRed(unsigned char value) {
    red = value;
}
void Point::setGreen(unsigned char value) {
    green = value;
}
void Point::setBlue(unsigned char value) {
    blue = value;
}

unsigned char Point::redness() {
    return red - whiteness();
}
unsigned char Point::greeness() {
    return green - whiteness();
}
unsigned char Point::blueness() {
    return blue - whiteness();
}
unsigned char Point::whiteness() {
    return std::min({red, green, blue});
}
