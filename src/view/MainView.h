//
// Created by tommaso on 09/05/20.
//

#ifndef PHOTOMAKERAPP_MAINVIEW_H
#define PHOTOMAKERAPP_MAINVIEW_H

#include <QMainWindow>
#include "MainViewWindow.h"
#include "ImageWrapper.h"
#include "MainViewController.h"

//view
class MainView : public QMainWindow, Observer {
    Q_OBJECT;
public:
    explicit MainView(ImageWrapper* imgWrap, MainViewController* controller, QWidget *parent = 0);

    ~MainView();

    void update() override;

protected:
    void resizeEvent(QResizeEvent* event) override;

private slots:
    // menu
    void openImage();
    void saveImage();
    void closeApp();

    void undoCmd();
    void redoCmd();
    void setUndoRedoState();

    void enableSelectionTool(bool enable);

    void setCropSheet();
    void setColorSheet();
    void setFilterSheet();

    // crop sheet
    void makeFlip();
    void makeMirror();

    // color sheet
    void adjustHue(int val);
    void adjustSaturation(int val);
    void adjustValue(int val);

    // filter sheet
    void applyBlur();
    void applySharpen();
    void applyLaplatian();

private:
    MainViewWindow* ui;
    ImageWrapper* imageWrapper;
    MainViewController* controller;
};


#endif //PHOTOMAKERAPP_MAINVIEW_H
