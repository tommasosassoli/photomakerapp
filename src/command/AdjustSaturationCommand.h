//
// Created by tommaso on 27/05/20.
//

#ifndef PHOTOMAKERAPP_ADJUSTSATURATIONCOMMAND_H
#define PHOTOMAKERAPP_ADJUSTSATURATIONCOMMAND_H


#include "Command.h"

class AdjustSaturationCommand : public Command {
public:
    AdjustSaturationCommand(shared_ptr<Image<>> img, double delta) : Command(img), delta(delta) {
    }

    void execute() override {
        Image<> tmp = ImageProcessor::adjustSaturation(*(this->previousImg.get()), delta / 100);
        this->parsedImg = std::make_shared<Image<>>(tmp);
    }

    std::string toString() override {
        return "Adjust Saturation";
    }

    double getDelta() const {
        return delta;
    }

private:
    double delta;
};


#endif //PHOTOMAKERAPP_ADJUSTSATURATIONCOMMAND_H
