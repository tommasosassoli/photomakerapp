//
// Created by tommaso on 25/05/20.
//

#ifndef PHOTOMAKERAPP_CROPCOMMAND_H
#define PHOTOMAKERAPP_CROPCOMMAND_H


#include "Command.h"
#include "../core/ImageProcessor.cpp"

class CropCommand : public Command {
public:
    CropCommand(Image<>* img, int x1, int y1, int x2, int y2) : oldimg(img), x1(x1), y1(y1), x2(x2), y2(y2) {
    }

    void execute() {
        Image<> i = ImageProcessor::crop(*oldimg, x1, y1, x2, y2);
        newimg = &i;
    }

    std::string toString() {
        return "Crop";
    }

private:
    Image<>* newimg {nullptr};
    Image<>* oldimg {nullptr};
    int x1, y1, x2, y2;
};


#endif //PHOTOMAKERAPP_CROPCOMMAND_H
