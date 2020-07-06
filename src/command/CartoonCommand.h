//
// Created by tommaso on 27/05/20.
//

#ifndef PHOTOMAKERAPP_CARTOONCOMMAND_H
#define PHOTOMAKERAPP_CARTOONCOMMAND_H


#include "Command.h"

class CartoonCommand : public Command {
public:
    CartoonCommand(shared_ptr<Image<>> img) : Command(img) {
    }

    CartoonCommand(shared_ptr<Image<>> img, int x1, int y1, int x2, int y2) : Command(img, x1, y1, x2, y2) {
    }

    void execute() override {
        Image<> tmp;

        if(!isApplyToSubImage())
            tmp = ImageProcessor::cartoonEffect(*(this->previousImg.get()));
        else
            tmp = ImageProcessor::cartoonEffect(*(this->previousImg.get()), getX1(), getY1(), getX2(), getY2());


        this->parsedImg = std::make_shared<Image<>>(tmp);
    }

    std::string toString() override {
        return "Cartoon effect";
    }
};


#endif //PHOTOMAKERAPP_CARTOONCOMMAND_H
