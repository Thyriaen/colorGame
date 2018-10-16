#ifndef VULTRI_POINT_H
#define VULTRI_POINT_H

#include <vector>

class Point {
  private:
    unsigned char red;
    unsigned char green;
    unsigned char blue;
  public:

    Point();
    Point(unsigned char red, unsigned char green, unsigned char blue);

    unsigned char getRed();
    unsigned char getGreen();
    unsigned char getBlue();

    void setRed(unsigned char value);
    void setGreen(unsigned char value);
    void setBlue(unsigned char value);

    unsigned char redness();
    unsigned char greeness();
    unsigned char blueness();
    unsigned char whiteness();
};

#endif //VULTRI_POINT_H
