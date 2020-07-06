//
// Created by tommaso on 27/05/20.
//

#ifndef PHOTOMAKERAPP_BINARYCOMMAND_H
#define PHOTOMAKERAPP_BINARYCOMMAND_H


#include "Command.h"

class BinaryCommand : public Command {
public:
    BinaryCommand(shared_ptr<Image<>> img) : Command(img) {
    }

    BinaryCommand(shared_ptr<Image<>> img, int x1, int y1, int x2, int y2) : Command(img, x1, y1, x2, y2) {
    }

    void execute() override {
        Image<> tmp;

        if(!isApplyToSubImage()) {
            tmp = ImageProcessor::cartoonEffect(*(this->previousImg.get()));
            tmp = ImageProcessor::adjustSaturation(tmp, -1);
        }else {
            tmp = ImageProcessor::cartoonEffect(*(this->previousImg.get()), getX1(), getY1(), getX2(), getY2());
            tmp = ImageProcessor::adjustSaturation(tmp, -1, getX1(), getY1(), getX2(), getY2());
        }

        this->parsedImg = std::make_shared<Image<>>(tmp);
    }

    std::string toString() override {
        return "Binary effect";
    }
};


#endif //PHOTOMAKERAPP_BINARYCOMMAND_H
