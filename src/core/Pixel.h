//
// Created by tommaso on 20/03/20.
//

#ifndef IMAGEPARSER_PIXEL_H
#define IMAGEPARSER_PIXEL_H

#include <istream>
#include "HSVPixel.h"

class HSVPixel;

/**
 * Class that represent 3-channel pixel.
 * @attention INT -> PIXEL: This class provide a constructor with a single argument (the value of every channel) to
 * enable the conversion from int to pixel to ease the initialization of an array of pixel.
 * */
class Pixel {
private:
    int R;
    int G;
    int B;

public:
    /**
     * Constructor that enable the conversion from an int value to a Pixel value INT -> PIXEL.
     * It's provide to ease the initialization of an array of pixel.
     * @param v the value to assign to every channel of the pixel.
     * @attention Every channel of the pixel
     * will initialize with the value of the single int.
     * */
    Pixel(int v = 0);

    Pixel(int R, int G, int B);

    int getR() const;

    void setR(int r);

    int getG() const;

    void setG(int g);

    int getB() const;

    void setB(int b);

    HSVPixel toHSV();

    std::string toString();

    friend std::ostream &operator<<(std::ostream &os, const Pixel &pixel);

    friend std::istream &operator>>(std::istream &is, Pixel &pixel);

    friend Pixel operator*(const Pixel& p1,const Pixel& p2);

    friend Pixel operator+(const Pixel& p1, const Pixel& p2);

    friend bool operator==(const Pixel& p1, const Pixel& p2);
};


#endif //IMAGEPARSER_PIXEL_H
