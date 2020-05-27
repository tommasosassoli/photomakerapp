//
// Created by tommaso on 26/05/20.
//

#ifndef PHOTOMAKERAPP_IMAGEWRAPPER_H
#define PHOTOMAKERAPP_IMAGEWRAPPER_H

#include <list>
#include <memory>
#include "../model/Image.h"
#include "Subject.h"

//model
class ImageWrapper : public Subject {
public:
    void setImage(shared_ptr<Image<>> img);

    shared_ptr<Image<>> getImage() const;

    void notify() override;

    void addObserver(Observer* o) override;

    void removeObserver(Observer* o) override;

private:
    shared_ptr<Image<>> img;

    std::list<Observer*> observers;
};


#endif //PHOTOMAKERAPP_IMAGEWRAPPER_H
