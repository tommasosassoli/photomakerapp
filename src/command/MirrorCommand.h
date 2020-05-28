//
// Created by tommaso on 27/05/20.
//

#ifndef PHOTOMAKERAPP_MIRRORCOMMAND_H
#define PHOTOMAKERAPP_MIRRORCOMMAND_H


#include "Command.h"

class MirrorCommand : public Command {
public:
    MirrorCommand(shared_ptr<Image<>> img) : Command(img){
    }

    void execute() override {
        Image<> tmp = ImageProcessor::mirror(*(this->previousImg.get()));
        this->parsedImg = std::make_shared<Image<>>(tmp);
    }

    std::string toString() override {
        return "Mirror";
    }

};


#endif //PHOTOMAKERAPP_MIRRORCOMMAND_H
