//
// Created by tommaso on 20/03/20.
//

#include "Pixel.h"

Pixel::Pixel(int R, int G, int B) : R(R), G(G), B(B) {
}

Pixel::Pixel(int v) : Pixel(v, v, v) {
}

int Pixel::getR() const {
    return R;
}

void Pixel::setR(int r) {
    R = r;
}

int Pixel::getG() const {
    return G;
}

void Pixel::setG(int g) {
    G = g;
}

int Pixel::getB() const {
    return B;
}

void Pixel::setB(int b) {
    B = b;
}

std::string Pixel::toString() {
    return "  " + std::to_string(this->R) + " " + std::to_string(this->G) + " " + std::to_string(this->B);
}

std::ostream &operator<<(std::ostream &os, const Pixel &pixel) {
    os << pixel.R << " " << pixel.G << " " << pixel.B;
    return os;
}

std::istream &operator>>(std::istream &is, Pixel &pixel) {
    is >> pixel.R;
    is >> pixel.G;
    is >> pixel.B;
    return is;
}

Pixel operator*(const Pixel &p1, const Pixel &p2) {
    return Pixel(p1.R * p2.R, p1.G * p2.G, p1.B * p2.B);
}

Pixel operator+(const Pixel &p1, const Pixel& p2) {
    return Pixel(p1.R + p2.R, p1.G + p2.G, p1.B + p2.B);
}

bool operator==(const Pixel &p1, const Pixel &p2) {
    return (p1.R == p2.R) && (p1.G == p2.G) && (p1.B == p2.B);
}
