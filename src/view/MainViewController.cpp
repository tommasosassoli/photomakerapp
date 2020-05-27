//
// Created by tommaso on 26/05/20.
//

#include <fstream>
#include "MainViewController.h"
#include "../command/FlipCommand.h"

MainViewController::MainViewController(ImageWrapper *imageWrapper) : imageWrapper(imageWrapper) {
}

void MainViewController::openImage(std::string path) {
    std::ifstream imgFile(path);

    if(imgFile.is_open()) {
        try {
            Image<> i;
            imgFile >> i;

            shared_ptr<Image<>> shrImg = std::make_shared<Image<>>(i);

            imageWrapper->setImage(shrImg);

            imgFile.close();
        } catch (ImageException &e) {
            throw runtime_error("Cannot open file");
        }
    }
}

void MainViewController::saveImage(std::string path) {
    std::ofstream outFile(path);
    Image<>* img = imageWrapper->getImage().get();

    if(outFile.is_open()){
        if(img != nullptr) {
            outFile << *img;
            outFile.close();
        } else
            throw runtime_error("No image opened");
    } else
        throw runtime_error("Cannot save the file");
}

void MainViewController::makeFlip() {
    shared_ptr<Image<>> img = imageWrapper->getImage();
    std::shared_ptr<FlipCommand> flip = std::make_shared<FlipCommand>(img);
    cmdHandler.registerAndExecute(flip);
    imageWrapper->setImage(flip->getParsedImage());
}
