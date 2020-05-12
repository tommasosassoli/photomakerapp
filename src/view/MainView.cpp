//
// Created by tommaso on 09/05/20.
//

#include "MainView.h"

MainView::MainView(QWidget *parent) : QMainWindow(parent), ui(new MainViewWindow()) {
    ui->setupUi(this);
}

MainView::~MainView() {
    delete ui;
}

void MainView::setCropSheet() {
    ui->setCropSheet();
}

void MainView::setColorSheet() {
    ui->setColorSheet();
}

void MainView::setFilterSheet() {
    ui->setFilterSheet();
}
