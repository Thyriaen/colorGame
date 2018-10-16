//
// Created by thyriaen on 08.10.18.
//

#ifndef VULTRI_UNIVERSE_H
#define VULTRI_UNIVERSE_H

#include "Point.h"

class Universe {
  private:
    unsigned int width;
    unsigned int height;

    std::vector<std::vector<Point>> pixels;

  public:
    Universe();
    Universe(unsigned int width, unsigned int height);
    void init(unsigned int width, unsigned int height);
    void setPixel(int x, int y, Point p);
    void setPixels(unsigned char* rawPixels);
    unsigned int getHeight();
    unsigned int getWidth();
    std::vector<unsigned char> getRaw();
};

#endif //VULTRI_UNIVERSE_H
