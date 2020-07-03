//
// Created by tommaso on 27/05/20.
//

#ifndef PHOTOMAKERAPP_FLIPCOMMAND_H
#define PHOTOMAKERAPP_FLIPCOMMAND_H


#include "Command.h"

class FlipCommand : public Command {
public:
    FlipCommand(shared_ptr<Image<>> img) : Command(img){
    }

    FlipCommand(shared_ptr<Image<>> img, int x1, int y1, int x2, int y2) : Command(img, x1, y1, x2, y2){
    }

    void execute() override {
        Image<> tmp;

        if(x1 == 0 && y1 == 0 && x2 == 0 && y2 == 0)
            tmp = ImageProcessor::flip(*(this->previousImg.get()));
        else
            tmp = ImageProcessor::flip(*(this->previousImg.get()), x1, y1, x2, y2);

        this->parsedImg = std::make_shared<Image<>>(tmp);
    }

    std::string toString() override {
        return "Flip";
    }

};


#endif //PHOTOMAKERAPP_FLIPCOMMAND_H
