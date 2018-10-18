//
// Created by thyriaen on 08.10.18.
//

#ifndef VULTRI_UNIVERSE_H
#define VULTRI_UNIVERSE_H

#include <vector>

class Universe {
  private:
    unsigned int width;
    unsigned int height;

    std::vector<unsigned char> pixels;
    std::vector<int> forces;

  public:
    Universe();
    Universe(unsigned int width, unsigned int height);
    void init(unsigned int width, unsigned int height);
    void setPixel(unsigned int x, unsigned int y, unsigned char red, unsigned char green, unsigned char blue);
    void setPixels(unsigned char* rawPixels);
    unsigned int getHeight();
    unsigned int getWidth();
    std::vector<unsigned char> getPixels();
    void next();


    int getDistance(int x1, int y1, int x2, int y2);
    unsigned char getOrientation(int fromX, int fromY, int toX, int toY);


    void whitenessOnly();
};

#endif //VULTRI_UNIVERSE_H
