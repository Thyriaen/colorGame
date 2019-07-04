//
// Created by thyriaen on 08.10.18.
//

#ifndef VULTRI_UNIVERSE_H
#define VULTRI_UNIVERSE_H

#include <vector>

typedef struct {
    unsigned char whiteness;
    unsigned char red;
    unsigned char blue;
    unsigned char green;
} point;


class Universe {
  private:
    unsigned int width;
    unsigned int height;
    unsigned int xFields;
    unsigned int yFields;
    unsigned int fields;
    unsigned int fieldSize;

    std::vector<unsigned char> pixels;
    std::vector<point> world;

  public:
    Universe();
    Universe(unsigned int width, unsigned int height);
    void init(unsigned int width, unsigned int height);
    void setPixels(const unsigned char* rawPixels);
    unsigned int getHeight();
    unsigned int getWidth();
    std::vector<unsigned char> getPixels();
    void next();
    void makePixels();
    void makeWorld();

    void drawGrid();

    // make const inputs
    int getDistance(int x1, int y1, int x2, int y2);
    void whitenessOnly();
};

#endif //VULTRI_UNIVERSE_H
