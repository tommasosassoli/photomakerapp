//
// Created by tommaso on 26/05/20.
//

#include "ImageWrapper.h"

ImageWrapper::ImageWrapper(Image<> *img) {
    setImage(img);
}

void ImageWrapper::setImage(Image<> *img) {
    delete img;
    this->img = img;
    notify();
}

Image<> *ImageWrapper::getImage() const {
    return this->img;
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
