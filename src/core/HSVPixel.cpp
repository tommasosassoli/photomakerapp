//
// Created by tommaso on 18/04/20.
//

#include "HSVPixel.h"
#include "../utils/PixelUtil.h"

HSVPixel::HSVPixel(Pixel *p, int maxVal) : pixel(p){
    int r = p->getR() / maxVal;
    int g = p->getG() / maxVal;
    int b = p->getB() / maxVal;

    int cmax = PixelUtil::maxRGB(r,g,b);
    int cmin = PixelUtil::maxRGB(r,g,b);

    int delta = cmax - cmin;

    // Hue calculation
    if(delta == 0)
        hue = 0;
    else if (cmax == r)
        hue = 60 * (((g - b) / delta) % 6);
    else if (cmax == g)
        hue = 60 * (((b - r) / delta) + 2);
    else
        hue = 60 * (((r - g) / delta) + 4);

    // Saturation calculation
    if(cmax == 0)
        saturation = 0;
    else
        saturation = delta / cmax;

    // Value calculation
    value = cmax;
}

HSVPixel::HSVPixel(int h, int s, int v) : hue(h), saturation(s), value(v) {
}

int HSVPixel::getHue() const {
    return hue;
}

void HSVPixel::setHue(int hue) {
    HSVPixel::hue = hue;
}

int HSVPixel::getSaturation() const {
    return saturation;
}

void HSVPixel::setSaturation(int saturation) {
    HSVPixel::saturation = saturation;
}

int HSVPixel::getValue() const {
    return value;
}

void HSVPixel::setValue(int value) {
    HSVPixel::value = value;
}

bool operator==(const HSVPixel& p1, const HSVPixel& p2){
    return (p1.hue == p2.hue) && (p1.saturation == p2.saturation) && (p1.value == p2.value);
}