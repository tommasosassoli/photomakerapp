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

    Command(shared_ptr<Image<>> img, int x1, int y1, int x2, int y2): x1(x1), y1(y1), x2(x2), y2(y2) {
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

    int x1 {0};
    int y1 {0};
    int x2 {0};
    int y2 {0};
};


#endif //PHOTOMAKERAPP_COMMAND_H
