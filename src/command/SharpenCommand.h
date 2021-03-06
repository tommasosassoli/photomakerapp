//
// Created by tommaso on 27/05/20.
//

#ifndef PHOTOMAKERAPP_SHARPENCOMMAND_H
#define PHOTOMAKERAPP_SHARPENCOMMAND_H


#include "Command.h"

class SharpenCommand : public Command {
public:
    SharpenCommand(shared_ptr<Image<>> img) : Command(img){
    }

    SharpenCommand(shared_ptr<Image<>> img, int x1, int y1, int x2, int y2) : Command(img, x1, y1, x2, y2) {
    }

    void execute() override {
        double arr[9] {0, -1, 0,
                       -1, 5, -1,
                       0, -1, 0};

        KernelMatrix kernel(arr, 3);

        Image<> tmp;
        if(!isApplyToSubImage())
            tmp = ImageProcessor::computeConvolution(*(this->previousImg.get()), kernel);
        else
            tmp = ImageProcessor::computeConvolution(*(this->previousImg.get()), kernel,
                    getX1(), getY1(), getX2(), getY2());

        this->parsedImg = std::make_shared<Image<>>(tmp);
    }

    std::string toString() override {
        return "Sharpen";
    }
};


#endif //PHOTOMAKERAPP_SHARPENCOMMAND_H
