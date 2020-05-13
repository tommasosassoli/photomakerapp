//
// Created by tommaso on 09/05/20.
//

#include "MainView.h"

MainView::MainView(QWidget *parent) : QMainWindow(parent), ui(new MainViewWindow()) {
    ui->setupUi(this);
}

MainView::~MainView() {
    delete ui;
    //delete img;
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

void MainView::openImage() {
    //TODO open image
    //ui->setImage( QImage );
}

void MainView::saveImage() {
    //TODO save image
}
