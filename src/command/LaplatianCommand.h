//
// Created by tommaso on 27/05/20.
//

#ifndef PHOTOMAKERAPP_LAPLATIANCOMMAND_H
#define PHOTOMAKERAPP_LAPLATIANCOMMAND_H


#include "Command.h"

class LaplatianCommand : public Command {
public:
    LaplatianCommand(shared_ptr<Image<>> img) : Command(img){
    }

    void execute() override {
        double arr[9] {-1,  -1,  -1,
                       -1,   8,  -1,
                       -1,  -1,  -1};

        KernelMatrix kernel(arr, 3);

        Image<> tmp = ImageProcessor::computeConvolution(*(this->previousImg.get()), kernel);
        this->parsedImg = std::make_shared<Image<>>(tmp);
    }

    std::string toString() override {
        return "Sharpen";
    }
};


#endif //PHOTOMAKERAPP_LAPLATIANCOMMAND_H
