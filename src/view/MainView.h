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

    void resizeEvent(QResizeEvent* event);

private slots:
    // menu
    void openImage();
    void saveImage();
    void closeApp();

    void undoCmd();
    void redoCmd();
    void setUndoRedoState();

    void setCropSheet();
    void setColorSheet();
    void setFilterSheet();

    // crop sheet
    void makeFlip();
    void makeMirror();

private:
    MainViewWindow* ui;
    ImageWrapper* imageWrapper;
    MainViewController* controller;
};


#endif //PHOTOMAKERAPP_MAINVIEW_H
