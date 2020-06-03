//
// Created by tommaso on 26/05/20.
//

#ifndef PHOTOMAKERAPP_MAINVIEWCONTROLLER_H
#define PHOTOMAKERAPP_MAINVIEWCONTROLLER_H

#include "ImageWrapper.h"
#include "../command/CommandHandler.h"

//controller
class MainViewController {
public:
    explicit MainViewController(ImageWrapper* imageWrapper);

    // menu
    void openImage(std::string path);
    void saveImage(std::string path);

    void undo();
    void redo();
    bool isUndoPossible();
    bool isRedoPossible();

    // crop sheet
    void makeFlip();
    void makeMirror();

    // color sheet
    void adjustHue(double val);
    void adjustSaturation(double val);
    void adjustValue(double val);

private:
    shared_ptr<Image<>> originalImage;  //FIXME remove?
    ImageWrapper* imageWrapper;
    CommandHandler cmdHandler;

    int oldHue {0};
    int oldSaturation {0};
    int oldValue {0};
};


#endif //PHOTOMAKERAPP_MAINVIEWCONTROLLER_H
