//
// Created by tommaso on 09/05/20.
//

#include <QFileDialog>
#include <QMessageBox>
#include "MainView.h"

MainView::MainView(ImageWrapper* imgWrap, MainViewController* controller, QWidget *parent)
: QMainWindow(parent), ui(new MainViewWindow()), imageWrapper(imgWrap), controller(controller) {
    imageWrapper->addObserver(this);
    ui->setupUi(this);
}

MainView::~MainView() {
    imageWrapper->removeObserver(this);
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

void MainView::openImage() {
    QUrl url = QFileDialog::getOpenFileUrl(this, "Open a file", QUrl(), "ppm file (*.ppm)");
    if(!url.isEmpty()) {
        try {
            controller->openImage(url.path().toStdString());
        } catch (runtime_error &e) {
            QMessageBox::information(this, "Photo Maker APP", e.what());
        }
    }
}

void MainView::saveImage() {
    QString filter = "ppm file (*.ppm)";
    QUrl url = QFileDialog::getSaveFileUrl(this, "Save file", QUrl(), filter, &filter);
    if(!url.isEmpty()) {
        try {
            controller->saveImage(url.path().toStdString());
        } catch (runtime_error &e) {
            QMessageBox::information(this, "Photo Maker APP", e.what());
        }
    }
}

void MainView::update() {
    Image<>* img = imageWrapper->getImage();

    int width = img->getWidth();
    int height = img->getHeight();
    RGBPixel *buffer = img->getBuffer();

    // RGB image converted in unsigned char for compatibility with QImage (Qt5)
    uchar *arr = new uchar[height * width * 3];
    for(int i = 0, j = 0; i < height * width; i++, j += 3) {
        arr[j] = buffer[i].getR();
        arr[j + 1] = buffer[i].getG();
        arr[j + 2] = buffer[i].getB();
    }

    QImage *qImg = new QImage(arr, width, height, QImage::Format_RGB888);  //Format_RGB888: RGB 24 bits per pixel
    ui->setImage(qImg);
}

void MainView::closeApp() {
    QWidget::close();
}
