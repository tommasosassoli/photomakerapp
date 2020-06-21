//
// Created by tommaso on 25/05/20.
//

#ifndef PHOTOMAKERAPP_CROPCOMMAND_H
#define PHOTOMAKERAPP_CROPCOMMAND_H


#include "Command.h"
#include "../core/ImageProcessor.cpp"

class CropCommand : public Command {
public:
    CropCommand(shared_ptr<Image<>> img, int x1, int y1, int x2, int y2) : Command(img), x1(x1), y1(y1), x2(x2), y2(y2){
    }

    void execute() {
        try {
            Image<> tmp = ImageProcessor::crop(*(this->previousImg.get()), y1, x1, y2, x2);
            this->parsedImg = std::make_shared<Image<>>(tmp);
        } catch (ImageException& e) {
            this->parsedImg = this->previousImg;
        }
    }

    std::string toString() {
        return "Crop";
    }

private:
    int x1, y1, x2, y2;
};


#endif //PHOTOMAKERAPP_CROPCOMMAND_H
