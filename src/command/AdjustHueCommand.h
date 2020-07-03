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

    AdjustHueCommand(shared_ptr<Image<>> img, double delta, int x1, int y1, int x2, int y2) :
    Command(img, x1, y1 ,x2, y2), delta(delta) {
    }

    void execute() override {
        Image<> tmp;

        if(x1 == 0 && y1 == 0 && x2 == 0 && y2 == 0)
            tmp = ImageProcessor::adjustHue(*(this->previousImg.get()), delta);
        else
            tmp = ImageProcessor::adjustHue(*(this->previousImg.get()), delta, x1, y1, x2, y2);

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
