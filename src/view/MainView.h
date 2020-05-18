//
// Created by tommaso on 09/05/20.
//

#ifndef PHOTOMAKERAPP_MAINVIEW_H
#define PHOTOMAKERAPP_MAINVIEW_H

#include <QMainWindow>
#include <iostream>
#include "MainViewWindow.h"

class MainView : public QMainWindow {   //TODO implementa MVC (controller con CommandHandler ?)
    Q_OBJECT;
public:
    explicit MainView(QWidget *parent = 0);

    ~MainView();

private slots:
    void setCropSheet();
    void setColorSheet();
    void setFilterSheet();
    void openImage();
    void saveImage();

private:
    MainViewWindow* ui;
    //Image* img;   //TODO image
    //CommandHandler cmdHandler;    //TODO command pattern
};


#endif //PHOTOMAKERAPP_MAINVIEW_H
