//
// Created by tommaso on 18/04/20.
//

#ifndef PHOTOMAKERAPP_HSVPIXEL_H
#define PHOTOMAKERAPP_HSVPIXEL_H

#include "Pixel.h"

class Pixel;

class HSVPixel {
private:
    Pixel *pixel {nullptr};
    double maxVal {255};
    double hue;
    double saturation;
    double value;

    bool static checkval(double v1, double v2);

public:
    HSVPixel(Pixel *pixel, int maxVal = 255);

    /**
    * @param h: degrees (eg. 120 (°))
    * @param s: percentage (eg. 100 (%))
    * @param v: percentage (eg. 50 (%))*/
    HSVPixel(int h, int s, int v);

    /**
     * @return degrees (between 0° and 360°)*/
    int getHue() const;

    /**
     * @param hue: degrees (between 0° and 360°)*/
    void setHue(int hue);

    /**
     * @return percentage (eg. 100 (%))*/
    int getSaturation() const;

    /**
     * @param saturation: percentage (eg. 100 (%))*/
    void setSaturation(int saturation);

    /**
     * @return percentage (eg. 100 (%))*/
    int getValue() const;

    /**
     * @param saturation: percentage (eg. 100 (%))*/
    void setValue(int value);

    void updateRGBPixel();

    friend bool operator==(const HSVPixel& p1, const HSVPixel& p2);
};


#endif //PHOTOMAKERAPP_HSVPIXEL_H
