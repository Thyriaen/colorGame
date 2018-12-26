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
    void makeWorld();
    void makePixels();
    void makeStruct();

    // make const inputs
    long getForcePart(int fromX, int fromY, int toX, int toY, int Value);
    void calculateForces(std::vector<int> repValues, std::vector<int> repX, std::vector<int> repY, std::vector<int> &forceX, std::vector<int> &forceY);
    void calculateRepresentative(int startIndex, int* repValue, int* repX, int* repY);
    void calculateRepresentatives(std::vector<int> &repValues, std::vector<int> &repX, std::vector<int> &repY);
    int getDistance(int x1, int y1, int x2, int y2);
    long getForce(int fromX, int fromY, int toX, int toY, int fromValue, int toValue);
    unsigned char getOrientation(int fromX, int fromY, int toX, int toY);

    void whitenessOnly();
};

#endif //VULTRI_UNIVERSE_H
