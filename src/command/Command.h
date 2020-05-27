//
// Created by tommaso on 25/05/20.
//

#ifndef PHOTOMAKERAPP_COMMAND_H
#define PHOTOMAKERAPP_COMMAND_H


#include <string>
#include <memory>
#include "../model/Image.h"
#include "../core/ImageProcessor.cpp"

class Command {
public:
    Command(shared_ptr<Image<>> img) {
        previousImg = std::move(img);
    }

    virtual ~Command() {
    }

    virtual void execute() = 0;

    virtual std::string toString() = 0;

    shared_ptr<Image<>> getPreviousImage() const {
        return std::move(previousImg);
    }

    shared_ptr<Image<>> getParsedImage() const {
        return std::move(parsedImg);
    }

protected:
    shared_ptr<Image<>> previousImg;

    shared_ptr<Image<>> parsedImg;
};


#endif //PHOTOMAKERAPP_COMMAND_H
