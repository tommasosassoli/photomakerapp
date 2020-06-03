//
// Created by tommaso on 27/05/20.
//

#ifndef PHOTOMAKERAPP_ADJUSTVALUECOMMAND_H
#define PHOTOMAKERAPP_ADJUSTVALUECOMMAND_H


#include "Command.h"

class AdjustValueCommand : public Command {
public:
    AdjustValueCommand(shared_ptr<Image<>> img, double delta) : Command(img), delta(delta) {
    }

    void execute() override {
        Image<> tmp = ImageProcessor::adjustValue(*(this->previousImg.get()), delta / 100);
        this->parsedImg = std::make_shared<Image<>>(tmp);
    }

    std::string toString() override {
        return "Adjust Value";
    }

    double getDelta() const {
        return delta;
    }

private:
    double delta;
};


#endif //PHOTOMAKERAPP_ADJUSTVALUECOMMAND_H
