//
// Created by tommaso on 27/05/20.
//

#ifndef PHOTOMAKERAPP_GRAYSCALECOMMAND_H
#define PHOTOMAKERAPP_GRAYSCALECOMMAND_H


#include "Command.h"

class GrayscaleCommand : public Command {
public:
    GrayscaleCommand(shared_ptr<Image<>> img) : Command(img) {
    }

    GrayscaleCommand(shared_ptr<Image<>> img, int x1, int y1, int x2, int y2) : Command(img, x1, y1, x2, y2) {
    }

    void execute() override {
        Image<> tmp;

        if(!isApplyToSubImage())
            tmp = ImageProcessor::adjustSaturation(*(this->previousImg.get()), -1);
        else
            tmp = ImageProcessor::adjustSaturation(*(this->previousImg.get()), -1,
                    getX1(), getY1(), getX2(), getY2());

        this->parsedImg = std::make_shared<Image<>>(tmp);
    }

    std::string toString() override {
        return "Grayscale";
    }
};


#endif //PHOTOMAKERAPP_GRAYSCALECOMMAND_H
