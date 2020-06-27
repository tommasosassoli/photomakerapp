//
// Created by tommaso on 27/05/20.
//

#ifndef PHOTOMAKERAPP_SHARPENCOMMAND_H
#define PHOTOMAKERAPP_SHARPENCOMMAND_H


#include "Command.h"

class SharpenCommand : public Command {
public:
    SharpenCommand(shared_ptr<Image<>> img, int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0) : Command(img), x1(x1),
    y1(y1), x2(x2), y2(y2){
    }

    void execute() override {
        double arr[9] {0, -1, 0,
                       -1, 5, -1,
                       0, -1, 0};

        KernelMatrix kernel(arr, 3);

        Image<> tmp;
        if(x1 == 0 && y1 == 0 && x2 == 0 && y2 == 0)
            tmp = ImageProcessor::computeConvolution(*(this->previousImg.get()), kernel);
        else
            tmp = ImageProcessor::computeConvolution(*(this->previousImg.get()), kernel, x1, y1, x2, y2);

        this->parsedImg = std::make_shared<Image<>>(tmp);
    }

    std::string toString() override {
        return "Laplatian";
    }

private:
    int x1;
    int y1;
    int x2;
    int y2;
};


#endif //PHOTOMAKERAPP_SHARPENCOMMAND_H
