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

    AdjustValueCommand(shared_ptr<Image<>> img, double delta, int x1, int y1, int x2, int y2) :
    Command(img, x1, y1 ,x2, y2), delta(delta) {
    }

    void execute() override {Image<> tmp;

        if(!isApplyToSubImage())
            tmp = ImageProcessor::adjustValue(*(this->previousImg.get()), delta/100);
        else
            tmp = ImageProcessor::adjustValue(*(this->previousImg.get()), delta/100,
                    getX1(), getY1(), getX2(), getY2());

        this->parsedImg = std::make_shared<Image<>>(tmp);
    }

    std::string toString() override {
        return "Adjust Value: " + std::to_string(getDelta());
    }

    double getDelta() const {
        return delta;
    }

private:
    double delta;
};


#endif //PHOTOMAKERAPP_ADJUSTVALUECOMMAND_H
