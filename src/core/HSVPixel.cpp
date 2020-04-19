//
// Created by tommaso on 18/04/20.
//

#include <cmath>
#include "HSVPixel.h"

HSVPixel::HSVPixel(Pixel *p, int maxVal) : pixel(p), maxVal(maxVal){
    double r = (double)p->getR() / this->maxVal;
    double g = (double)p->getG() / this->maxVal;
    double b = (double)p->getB() / this->maxVal;

    double cmax = fmax(r, fmax(g, b));
    double cmin = fmin(r, fmin(g, b));

    double delta = cmax - cmin;

    // Hue calculation
    if(delta == 0)
        hue = 0;
    else if (cmax == r)
        hue = 60 * ((g - b) / delta);
    else if (cmax == g)
        hue = 60 * (((b - r) / delta) + 2);
    else
        hue = 60 * (((r - g) / delta) + 4);
    if(hue < 0)
        hue += 360;

    // Saturation calculation
    if(cmax == 0)
        saturation = 0;
    else
        saturation = delta / cmax;

    // Value calculation
    value = cmax;
}

HSVPixel::HSVPixel(int h, int s, int v) {
    setHue(h);
    setSaturation(s);
    setValue(v);
}

int HSVPixel::getHue() const {
    return hue;
}

void HSVPixel::setHue(int hue) {
    HSVPixel::hue = (double)(hue % 360);
    this->updateRGBPixel();
}

int HSVPixel::getSaturation() const {
    return saturation * 100;
}

void HSVPixel::setSaturation(int saturation) {
    HSVPixel::saturation = (double)saturation / 100;
    this->updateRGBPixel();
}

int HSVPixel::getValue() const {
    return value * 100;
}

void HSVPixel::setValue(int value) {
    HSVPixel::value = (double)value / 100;
    this->updateRGBPixel();
}

bool operator==(const HSVPixel& p1, const HSVPixel& p2){
    return HSVPixel::checkval(p1.hue, p2.hue) &&
    HSVPixel::checkval(p1.saturation, p2.saturation) &&
    HSVPixel::checkval(p1.value, p2.value);
}

bool HSVPixel::checkval(double v1, double v2){
    int a1 = std::round(v1 * 100);
    int a2 = std::round(v2 * 100);
    return a1 == a2;
}

void HSVPixel::updateRGBPixel() {
    if(pixel != nullptr){
        double c = value * saturation;
        double x = c * (1 - fabs(fmod((hue / 60), 2) - 1));
        double m = value - c;

        double r, g, b;
        if (0 <= hue && hue < 60){
            r = c;
            g = x;
            b = 0;
        } else if (60 <= hue && hue < 120){
            r = x;
            g = c;
            b = 0;
        } else if (120 <= hue && hue < 180){
            r = 0;
            g = c;
            b = x;
        } else if (180 <= hue && hue < 240){
            r = 0;
            g = x;
            b = c;
        } else if (240 <= hue && hue < 300){
            r = x;
            g = 0;
            b = c;
        } else {    // if (300 <= hue < 360)
            r = c;
            g = 0;
            b = x;
        }

        pixel->setR((r + m) * maxVal);
        pixel->setG((g + m) * maxVal);
        pixel->setB((b + m) * maxVal);
    }
}
