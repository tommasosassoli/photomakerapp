//
// Created by tommaso on 09/05/20.
//

#ifndef PHOTOMAKERAPP_MAINVIEW_H
#define PHOTOMAKERAPP_MAINVIEW_H

#include <QMainWindow>
#include <iostream>
#include "MainViewWindow.h"

class MainView : public QMainWindow {
    Q_OBJECT;
public:
    explicit MainView(QWidget *parent = 0);

    ~MainView();

private slots:
    void setCropSheet();
    void setColorSheet();
    void setFilterSheet();

private:
    MainViewWindow* ui;
};


#endif //PHOTOMAKERAPP_MAINVIEW_H
