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
            ui->setLoadingState();
            controller->openImage(url.path().toStdString());
        } catch (runtime_error &e) {
            QMessageBox::information(this, "Photo Maker APP", e.what());
        }
    }
}

void MainView::saveImage() {
    if(imageWrapper->getImage() != nullptr) {
        QString filter = "ppm file (*.ppm)";
        QUrl url = QFileDialog::getSaveFileUrl(this, "Save file", QUrl(), filter, &filter);
        if (!url.isEmpty()) {
            try {
                controller->saveImage(url.path().toStdString());
            } catch (runtime_error &e) {
                QMessageBox::information(this, "Photo Maker APP", e.what());
            }
        }
    } else
        QMessageBox::information(this, "Photo Maker APP", "No image opened");
}

void MainView::closeApp() {
    QWidget::close();
}

void MainView::undoCmd() {
    controller->undo();
}

void MainView::redoCmd() {
    controller->redo();
}

void MainView::setUndoRedoState() {
    ui->enableUndoBtn(controller->isUndoPossible());
    ui->enableRedoBtn(controller->isRedoPossible());
}

void MainView::makeFlip() {
    controller->makeFlip();
}

void MainView::makeMirror() {
    controller->makeMirror();
}

void MainView::adjustHue(int val) {
    controller->adjustHue(val);
}

void MainView::adjustSaturation(int val) {
    controller->adjustSaturation(val);
}

void MainView::adjustValue(int val) {
    controller->adjustValue(val);
}

void MainView::update() {
    Image<>* img = imageWrapper->getImage().get();

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

    QImage qImg(arr, width, height, QImage::Format_RGB888);  //Format_RGB888: RGB 24 bits per pixel
    ui->setImage(qImg);
    delete arr;
}

void MainView::resizeEvent(QResizeEvent *event) {
    ui->adjustImageSize();
}
