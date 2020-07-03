//
// Created by tommaso on 27/05/20.
//

#ifndef PHOTOMAKERAPP_BLURCOMMAND_H
#define PHOTOMAKERAPP_BLURCOMMAND_H


#include "Command.h"

class BlurCommand : public Command {
public:
    BlurCommand(shared_ptr<Image<>> img) : Command(img) {
    }

    BlurCommand(shared_ptr<Image<>> img, int x1, int y1, int x2, int y2) : Command(img, x1, y1, x2, y2) {
    }

    void execute() override {
        double arr[9] = {0.111, 0.111, 0.111,
                         0.111, 0.111, 0.111,
                         0.111, 0.111, 0.111};

        KernelMatrix kernel(arr, 3);

        Image<> tmp;
        if(x1 == 0 && y1 == 0 && x2 == 0 && y2 == 0)
            tmp = ImageProcessor::computeConvolution(*(this->previousImg.get()), kernel);
        else
            tmp = ImageProcessor::computeConvolution(*(this->previousImg.get()), kernel, x1, y1, x2, y2);

        this->parsedImg = std::make_shared<Image<>>(tmp);
    }

    std::string toString() override {
        return "Blur";
    }
};


#endif //PHOTOMAKERAPP_BLURCOMMAND_H
