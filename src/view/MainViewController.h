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
    std::string getUndoTopName() const;
    bool isRedoPossible();
    std::string getRedoTopName() const;

    // crop sheet
    void makeCrop(int x1, int y1, int x2, int y2);
    void makeFlip();
    void makeMirror();

    // color sheet
    void adjustHue(double val);
    void adjustSaturation(double val);
    void adjustValue(double val);

    // filter sheet
    void applyBlur();
    void applyBlur(int x1, int y1, int x2, int y2);
    void applySharpen();
    void applySharpen(int x1, int y1, int x2, int y2);
    void applyLaplacian();
    void applyLaplacian(int x1, int y1, int x2, int y2);

    // other method
    int getOldHue() const;
    int getOldSaturation() const;
    int getOldValue() const;

private:
    ImageWrapper* imageWrapper;
    CommandHandler cmdHandler;

    int oldHue {0};
    int oldSaturation {0};
    int oldValue {0};
};


#endif //PHOTOMAKERAPP_MAINVIEWCONTROLLER_H
