//
// Created by tommaso on 27/05/20.
//

#ifndef PHOTOMAKERAPP_ADJUSTHUECOMMAND_H
#define PHOTOMAKERAPP_ADJUSTHUECOMMAND_H


#include "Command.h"

class AdjustHueCommand : public Command {
public:
    AdjustHueCommand(shared_ptr<Image<>> img, double delta) : Command(img), delta(delta) {
    }

    void execute() override {
        Image<> tmp = ImageProcessor::adjustHue(*(this->previousImg.get()), delta);
        this->parsedImg = std::make_shared<Image<>>(tmp);
    }

    std::string toString() override {
        return "Adjust Hue";
    }

    double getDelta() const {
        return delta;
    }

private:
    double delta;
};


#endif //PHOTOMAKERAPP_ADJUSTHUECOMMAND_H
