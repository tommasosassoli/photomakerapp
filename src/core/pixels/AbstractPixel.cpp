//
// Created by tommaso on 22/04/20.
//

#include "AbstractPixel.h"

AbstractPixel::~AbstractPixel() {
}

std::ostream &operator<<(std::ostream &os, AbstractPixel &p) {
    return p.toOutputStream(os);
}

bool AbstractPixel::operator==(AbstractPixel const &p) const {
    return this->isEqual(p);
}

