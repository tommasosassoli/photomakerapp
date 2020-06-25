//
// Created by tommaso on 27/05/20.
//

#ifndef PHOTOMAKERAPP_LAPLACIANCOMMAND_H
#define PHOTOMAKERAPP_LAPLACIANCOMMAND_H


#include "Command.h"

class LaplacianCommand : public Command {
public:
    LaplacianCommand(shared_ptr<Image<>> img) : Command(img){
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
        return "Edge detection";
    }
};


#endif //PHOTOMAKERAPP_LAPLACIANCOMMAND_H
