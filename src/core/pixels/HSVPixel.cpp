//
// Created by tommaso on 18/04/20.
//

#include <cmath>
#include "HSVPixel.h"

HSVPixel::HSVPixel(double h, double s, double v) {
    setHue(h);
    setSaturation(s);
    setValue(v);
}

HSVPixel::HSVPixel(const RGBPixel &p) {
    double r = (double)p.getR() / 255;
    double g = (double)p.getG() / 255;
    double b = (double)p.getB() / 255;

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

RGBPixel HSVPixel::toRGB() {
    return RGBPixel(*this);
}

double HSVPixel::getHue() const {
    return hue;
}

void HSVPixel::setHue(double hue) {
    HSVPixel::hue = fmod(hue, 360);
}

double HSVPixel::getSaturation() const {
    return saturation;
}

void HSVPixel::setSaturation(double saturation) {
    if(saturation < 0) saturation = 0;
    else if (saturation > 1) saturation = 1;

    HSVPixel::saturation = saturation;
}

double HSVPixel::getValue() const {
    return value;
}

void HSVPixel::setValue(double value) {
    if(value < 0) value = 0;
    else if (value > 1) value = 1;

    HSVPixel::value = value;
}

std::ostream & HSVPixel::toOutputStream(std::ostream &os) {
    return  this->toRGB().toOutputStream(os);
}

bool HSVPixel::isEqual(AbstractPixel const &p) const {
    if(HSVPixel const *hsv = dynamic_cast<HSVPixel const*>(&p)) {
        return HSVPixel::checkval(this->hue, hsv->hue) &&
               HSVPixel::checkval(this->saturation, hsv->saturation) &&
               HSVPixel::checkval(this->value, hsv->value);
    }
    return false;
}

bool HSVPixel::checkval(double v1, double v2){
    double a1 = std::round(v1 * 100);
    double a2 = std::round(v2 * 100);
    return a1 == a2;
}


