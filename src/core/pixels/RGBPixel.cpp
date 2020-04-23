//
// Created by tommaso on 20/03/20.
//

#include <cmath>
#include "RGBPixel.h"

RGBPixel::RGBPixel(int R, int G, int B) {
    setR(R);
    setG(G);
    setB(B);
}

RGBPixel::RGBPixel(const HSVPixel &p){
    double c = p.getValue() * p.getSaturation();
    double x = c * (1 - abs((p.getHue() / 60) % 2 - 1));
    double m = p.getValue() - c;

    double r, g, b;
    int hue = p.getHue();
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

    //approximation to int
    this->setR((int)round((r + m) * 255));
    this->setG((int)round((g + m) * 255));
    this->setB((int)round((b + m) * 255));
}

RGBPixel::~RGBPixel(){
}

HSVPixel RGBPixel::toHSV() {
    return HSVPixel(*this);
}

int RGBPixel::getR() const {
    return R;
}

void RGBPixel::setR(int r) {
    if(r < 0)   r = 0;
    if(r > 255) r = 255;
    R = r;
}

int RGBPixel::getG() const {
    return G;
}

void RGBPixel::setG(int g) {
    if(g < 0)   g = 0;
    if(g > 255) g = 255;
    G = g;
}

int RGBPixel::getB() const {
    return B;
}

void RGBPixel::setB(int b) {
    if(b < 0)   b = 0;
    if(b > 255) b = 255;
    B = b;
}

std::ostream& RGBPixel::toOutputStream(std::ostream &os) {
    os << (int)this->R << " " << (int)this->G << " " << (int)this->B << " ";
    return os;
}

RGBPixel RGBPixel::operator*(const double lambda) {
    return RGBPixel(this->R * lambda, this->G * lambda, this->B * lambda);
}

RGBPixel RGBPixel::operator+(const RGBPixel &p) {
    return RGBPixel(this->R + p.getR(), this->G + p.getG(), this->B + p.getB());
}

std::istream &operator>>(std::istream &is, RGBPixel &pixel) {
    int r = 0;
    int g = 0;
    int b = 0;
    is >> r;
    is >> g;
    is >> b;
    pixel.setR(r);
    pixel.setG(g);
    pixel.setB(b);
    return is;
}

bool RGBPixel::isEqual(const AbstractPixel &p) const {
    const RGBPixel *rgb = static_cast<const RGBPixel*>(&p);
    return (this->R == rgb->R) && (this->G == rgb->G) && (this->B == rgb->B);
}

