//
// Created by tommaso on 26/05/20.
//

#ifndef PHOTOMAKERAPP_IMAGEWRAPPER_H
#define PHOTOMAKERAPP_IMAGEWRAPPER_H

#include <list>
#include "../model/Image.h"
#include "Subject.h"

//model
class ImageWrapper : public Subject {
public:
    ImageWrapper(Image<>* img = 0);

    void setImage(Image<>* img);

    Image<>* getImage() const;

    void notify() override;

    void addObserver(Observer* o) override;

    void removeObserver(Observer* o) override;

private:
    Image<>* img {nullptr};

    std::list<Observer*> observers;
};


#endif //PHOTOMAKERAPP_IMAGEWRAPPER_H
