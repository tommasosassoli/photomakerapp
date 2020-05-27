//
// Created by tommaso on 26/05/20.
//

#include "ImageWrapper.h"

void ImageWrapper::setImage(shared_ptr<Image<>> img) {
    this->img = std::move(img);
    notify();
}

shared_ptr<Image<>> ImageWrapper::getImage() const {
    return img;
}

void ImageWrapper::notify() {
    for (Observer* observer : observers)
        observer->update();
}

void ImageWrapper::addObserver(Observer *o) {
    observers.push_back(o);
}

void ImageWrapper::removeObserver(Observer *o) {
    observers.remove(o);
}
