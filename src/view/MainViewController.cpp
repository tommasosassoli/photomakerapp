//
// Created by tommaso on 26/05/20.
//

#include <fstream>
#include "MainViewController.h"
#include "../command/CropCommand.h"
#include "../command/FlipCommand.h"
#include "../command/MirrorCommand.h"
#include "../command/AdjustHueCommand.h"
#include "../command/AdjustSaturationCommand.h"
#include "../command/AdjustValueCommand.h"
#include "../command/BlurCommand.h"
#include "../command/SharpenCommand.h"
#include "../command/LaplacianCommand.h"

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

std::string MainViewController::getUndoTopName() const {
    return cmdHandler.getUndoTop()->toString();
}

bool MainViewController::isRedoPossible() {
    return cmdHandler.isRedoPossible();
}

std::string MainViewController::getRedoTopName() const {
    return cmdHandler.getRedoTop()->toString();
}

void MainViewController::makeCrop(int x1, int y1, int x2, int y2) {
    shared_ptr<Image<>> img = imageWrapper->getImage();
    if(img) {
        std::shared_ptr<CropCommand> crop = std::make_shared<CropCommand>(img, x1, y1, x2, y2);
        cmdHandler.registerAndExecute(crop);
        imageWrapper->setImage(crop->getParsedImage());
    }
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
    shared_ptr<Image<>> img = imageWrapper->getImage();
    if(img) {
        //int delta = val - oldSaturation;
        //oldSaturation = val;
        std::shared_ptr<AdjustSaturationCommand> sat = std::make_shared<AdjustSaturationCommand>(img, val);
        cmdHandler.registerAndExecute(sat);
        imageWrapper->setImage(sat->getParsedImage());
    }
}

void MainViewController::adjustValue(double val) {
    shared_ptr<Image<>> img = imageWrapper->getImage();
    if(img) {
        int delta = val - oldValue;
        oldValue = val;
        std::shared_ptr<AdjustValueCommand> value = std::make_shared<AdjustValueCommand>(img, delta);
        cmdHandler.registerAndExecute(value);
        imageWrapper->setImage(value->getParsedImage());
    }
}

void MainViewController::applyBlur() {
    shared_ptr<Image<>> img = imageWrapper->getImage();
    if(img) {
        std::shared_ptr<BlurCommand> blur = std::make_shared<BlurCommand>(img);
        cmdHandler.registerAndExecute(blur);
        imageWrapper->setImage(blur->getParsedImage());
    }
}

void MainViewController::applySharpen() {
    shared_ptr<Image<>> img = imageWrapper->getImage();
    if(img) {
        std::shared_ptr<SharpenCommand> sharp = std::make_shared<SharpenCommand>(img);
        cmdHandler.registerAndExecute(sharp);
        imageWrapper->setImage(sharp->getParsedImage());
    }
}

void MainViewController::applyLaplacian() {
    shared_ptr<Image<>> img = imageWrapper->getImage();
    if(img) {
        std::shared_ptr<LaplacianCommand> lap = std::make_shared<LaplacianCommand>(img);
        cmdHandler.registerAndExecute(lap);
        imageWrapper->setImage(lap->getParsedImage());
    }
}

void MainViewController::applyLaplacian(int x1, int y1, int x2, int y2) {
    shared_ptr<Image<>> img = imageWrapper->getImage();
    if(img) {
        std::shared_ptr<LaplacianCommand> lap = std::make_shared<LaplacianCommand>(img, x1, y1, x2, y2);
        cmdHandler.registerAndExecute(lap);
        imageWrapper->setImage(lap->getParsedImage());
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
