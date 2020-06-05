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

    void execute() override {
        double arr[9] {0, -1, 0,
                       -1, 5, -1,
                       0, -1, 0};

        KernelMatrix kernel(arr, 3);

        Image<> tmp = ImageProcessor::computeConvolution(*(this->previousImg.get()), kernel);
        this->parsedImg = std::make_shared<Image<>>(tmp);
    }

    std::string toString() override {
        return "Sharpen";
    }
};


#endif //PHOTOMAKERAPP_SHARPENCOMMAND_H
