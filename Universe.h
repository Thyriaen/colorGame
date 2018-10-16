//
// Created by thyriaen on 08.10.18.
//

#ifndef VULTRI_UNIVERSE_H
#define VULTRI_UNIVERSE_H

class Universe {
  private:
    unsigned int width;
    unsigned int height;

    std::vector<unsigned char> pixels;

  public:
    Universe();
    Universe(unsigned int width, unsigned int height);
    void init(unsigned int width, unsigned int height);
    void setPixel(unsigned int x, unsigned int y, unsigned char red, unsigned char green, unsigned char blue);
    void setPixels(unsigned char* rawPixels);
    unsigned int getHeight();
    unsigned int getWidth();
    std::vector<unsigned char> getPixels();

    void whitenessOnly();
};

#endif //VULTRI_UNIVERSE_H
