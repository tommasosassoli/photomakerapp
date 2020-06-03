//
// Created by tommaso on 26/05/20.
//

#include <fstream>
#include "MainViewController.h"
#include "../command/FlipCommand.h"
#include "../command/MirrorCommand.h"
#include "../command/AdjustHueCommand.h"
#include "../command/AdjustSaturationCommand.h"
#include "../command/AdjustValueCommand.h"

MainViewController::MainViewController(ImageWrapper *imageWrapper) : imageWrapper(imageWrapper) {
}

void MainViewController::openImage(std::string path) {
    std::ifstream imgFile(path);

    if(imgFile.is_open()) {
        try {
            Image<> i;
            imgFile >> i;

            shared_ptr<Image<>> shrImg = std::make_shared<Image<>>(i);

            originalImage =  shrImg;
            imageWrapper->setImage(shrImg);
            cmdHandler.resetAll();  // reset the stacks from the old images

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

void MainViewController::undo() {
    if(cmdHandler.isUndoPossible()){
        shared_ptr<Command> cmd = cmdHandler.undo();
        imageWrapper->setImage(cmd->getPreviousImage());
    }
}

void MainViewController::redo() {
    if(cmdHandler.isRedoPossible()){
        shared_ptr<Command> cmd = cmdHandler.redo();
        imageWrapper->setImage(cmd->getParsedImage());
    }
}

bool MainViewController::isUndoPossible() {
    return cmdHandler.isUndoPossible();
}

bool MainViewController::isRedoPossible() {
    return cmdHandler.isRedoPossible();
}


void MainViewController::makeFlip() {
    shared_ptr<Image<>> img = imageWrapper->getImage();
    if(img) {
        std::shared_ptr<FlipCommand> flip = std::make_shared<FlipCommand>(img);
        cmdHandler.registerAndExecute(flip);
        imageWrapper->setImage(flip->getParsedImage());
    }
}

void MainViewController::makeMirror() {
    shared_ptr<Image<>> img = imageWrapper->getImage();
    if(img) {
        std::shared_ptr<MirrorCommand> mirror = std::make_shared<MirrorCommand>(img);
        cmdHandler.registerAndExecute(mirror);
        imageWrapper->setImage(mirror->getParsedImage());
    }
}

void MainViewController::adjustHue(double val) {
    shared_ptr<Image<>> img = imageWrapper->getImage();
    if(img) {
        int delta = val - oldHue;
        oldHue = val;
        std::shared_ptr<AdjustHueCommand> hue = std::make_shared<AdjustHueCommand>(img, delta);
        cmdHandler.registerAndExecute(hue);
        imageWrapper->setImage(hue->getParsedImage());
    }
}

void MainViewController::adjustSaturation(double val) {
    shared_ptr<Image<>> img = imageWrapper->getImage(); //FIXME
    if(img) {
        //int delta = val - oldSaturation;
        //oldSaturation = val;
        std::shared_ptr<AdjustSaturationCommand> sat = std::make_shared<AdjustSaturationCommand>(img, val);
        cmdHandler.registerAndExecute(sat);
        imageWrapper->setImage(sat->getParsedImage());
    }
}

void MainViewController::adjustValue(double val) {
    shared_ptr<Image<>> img = originalImage;    //FIXME
    if(img) {
        int delta = val - oldValue;
        oldValue = val;
        std::shared_ptr<AdjustValueCommand> value = std::make_shared<AdjustValueCommand>(img, delta);
        cmdHandler.registerAndExecute(value);
        imageWrapper->setImage(value->getParsedImage());
    }
}

int MainViewController::getOldHue() const {
    return oldHue;
}

int MainViewController::getOldSaturation() const {
    return oldSaturation;
}

int MainViewController::getOldValue() const {
    return oldValue;
}
