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

    LaplacianCommand(shared_ptr<Image<>> img, int x1, int y1, int x2, int y2) : Command(img, x1, y1, x2, y2){
    }

    void execute() override {
        double arr[9] {-1,  -1,  -1,
                       -1,   8,  -1,
                       -1,  -1,  -1};

        KernelMatrix kernel(arr, 3);

        Image<> tmp;
        if(x1 == 0 && y1 == 0 && x2 == 0 && y2 == 0)
            tmp = ImageProcessor::computeConvolution(*(this->previousImg.get()), kernel);
        else
            tmp = ImageProcessor::computeConvolution(*(this->previousImg.get()), kernel, x1, y1, x2, y2);

        this->parsedImg = std::make_shared<Image<>>(tmp);
    }

    std::string toString() override {
        return "Edge detection";
    }
};


#endif //PHOTOMAKERAPP_LAPLACIANCOMMAND_H
