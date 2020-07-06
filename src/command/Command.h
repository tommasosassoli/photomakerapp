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
    explicit Command(shared_ptr<Image<>> img, int x1 = -1, int y1 = -1, int x2 = -1, int y2 = -1)
    : x1(x1), y1(y1), x2(x2), y2(y2) {
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

    bool isApplyToSubImage() {
        return !(x1 == -1 && y1 == -1 && x2 == -1 && y2 == -1);
    }

    int getX1() const {
        return x1;
    }

    int getY1() const {
        return y1;
    }

    int getX2() const {
        return x2;
    }

    int getY2() const {
        return y2;
    }

private:
    int x1;
    int y1;
    int x2;
    int y2;
};


#endif //PHOTOMAKERAPP_COMMAND_H
