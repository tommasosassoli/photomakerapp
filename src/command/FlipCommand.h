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

    void execute() override {
        Image<> tmp = ImageProcessor::flip(*(this->previousImg.get()));
        this->parsedImg = std::make_shared<Image<>>(tmp);
    }

    std::string toString() override {
        return "Flip";
    }

};


#endif //PHOTOMAKERAPP_FLIPCOMMAND_H
