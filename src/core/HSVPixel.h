//
// Created by tommaso on 18/04/20.
//

#ifndef PHOTOMAKERAPP_HSVPIXEL_H
#define PHOTOMAKERAPP_HSVPIXEL_H

#include "Pixel.h"

class Pixel;

class HSVPixel {
private:
    Pixel *pixel;
    int hue;
    int saturation;
    int value;

public:
    HSVPixel(Pixel *pixel, int maxVal = 255);

    HSVPixel(int h, int s, int v);

    int getHue() const;

    void setHue(int hue);

    int getSaturation() const;

    void setSaturation(int saturation);

    int getValue() const;

    void setValue(int value);

    friend bool operator==(const HSVPixel& p1, const HSVPixel& p2);
};


#endif //PHOTOMAKERAPP_HSVPIXEL_H
