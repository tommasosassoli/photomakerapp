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
    void setCropSheet();
    void setColorSheet();
    void setFilterSheet();
    void openImage();
    void saveImage();
    void makeFlip();
    void makeMirror();
    void closeApp();

private:
    MainViewWindow* ui;
    ImageWrapper* imageWrapper;
    MainViewController* controller;
};


#endif //PHOTOMAKERAPP_MAINVIEW_H
