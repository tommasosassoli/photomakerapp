//
// Created by tommaso on 27/05/20.
//

#ifndef PHOTOMAKERAPP_BLURCOMMAND_H
#define PHOTOMAKERAPP_BLURCOMMAND_H


#include "Command.h"

class BlurCommand : public Command {
public:
    BlurCommand(shared_ptr<Image<>> img, double val = 9) : Command(img), value(val) {
    }

    void execute() override {
        double arr[9];

        for(int i = 0; i < 9; i++)
            arr[i] = 1 / value;

        KernelMatrix kernel(arr, 3);

        Image<> tmp = ImageProcessor::computeConvolution(*(this->previousImg).get(), kernel);
        this->parsedImg = std::make_shared<Image<>>(tmp);
    }

    std::string toString() override {
        return "Blur";
    }

    double getValue() const {
        return value;
    }

private:
    double value;
};


#endif //PHOTOMAKERAPP_BLURCOMMAND_H
