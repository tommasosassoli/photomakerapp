//
// Created by tommaso on 26/05/20.
//

#ifndef PHOTOMAKERAPP_MAINVIEWCONTROLLER_H
#define PHOTOMAKERAPP_MAINVIEWCONTROLLER_H

#include "ImageWrapper.h"

//controller
class MainViewController {
public:
    explicit MainViewController(ImageWrapper* imageWrapper);

    void openImage(std::string path);

    void saveImage(std::string path);

private:
    ImageWrapper* imageWrapper;
    //CommandHandler cmdHandler;
};


#endif //PHOTOMAKERAPP_MAINVIEWCONTROLLER_H
