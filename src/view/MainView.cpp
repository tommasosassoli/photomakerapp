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
    ui->setColorSheet(controller->getOldHue(), controller->getOldSaturation(), controller->getOldValue());
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
            ui->setPathToImage(url.path());
            ui->setSelectionActive(false);
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
                ui->setSavedState();
                ui->setSelectionActive(false);
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
    //undo
    if(controller->isUndoPossible())
        ui->enableUndoBtn(true, controller->getUndoTopName().c_str());
    else
        ui->enableUndoBtn(false);

    //redo
    if(controller->isRedoPossible())
        ui->enableRedoBtn(true, controller->getRedoTopName().c_str());
    else
        ui->enableRedoBtn(false);
}

void MainView::enableSelectionTool(bool enable) {
    ui->setSelectionActive(enable);
}

void MainView::makeCrop() {
    QRect rect = ui->getSelectedArea();
    if(!rect.isEmpty()) {
        ui->setApplyingChangesState();
        controller->makeCrop(rect.x(), rect.y(), rect.x()+rect.width(), rect.y()+rect.height());
    }
    ui->setSelectionActive(false);
}

void MainView::makeFlip() {
    ui->setApplyingChangesState();
    controller->makeFlip();
}

void MainView::makeMirror() {
    ui->setApplyingChangesState();
    controller->makeMirror();
}

void MainView::adjustHue(int val) {
    ui->setApplyingChangesState();
    controller->adjustHue(val);
}

void MainView::adjustSaturation(int val) {
    ui->setApplyingChangesState();
    controller->adjustSaturation(val);
}

void MainView::adjustValue(int val) {
    ui->setApplyingChangesState();
    controller->adjustValue(val);
}

void MainView::applyBlur() {
    QRect rect = ui->getSelectedArea();
    ui->setApplyingChangesState();
    if(rect.isEmpty())
        controller->applyBlur();
    else
        controller->applyBlur(rect.x(), rect.y(), rect.x()+rect.width(), rect.y()+rect.height());
    ui->setSelectionActive(false);
}

void MainView::applySharpen() {
    QRect rect = ui->getSelectedArea();
    ui->setApplyingChangesState();
    if(rect.isEmpty())
        controller->applySharpen();
    else
        controller->applySharpen(rect.x(), rect.y(), rect.x()+rect.width(), rect.y()+rect.height());
    ui->setSelectionActive(false);
}

void MainView::applyLaplacian() {
    QRect rect = ui->getSelectedArea();
    ui->setApplyingChangesState();
    if(rect.isEmpty())
        controller->applyLaplacian();
    else
        controller->applyLaplacian(rect.x(), rect.y(), rect.x()+rect.width(), rect.y()+rect.height());
    ui->setSelectionActive(false);
}

void MainView::update() {
    Image<>* img = imageWrapper->getImage().get();

    int width = img->getWidth();
    int height = img->getHeight();
    RGBPixel *buffer = img->getBuffer();

    // RGB image converted in unsigned char for compatibility with QImage (Qt5)
    uchar *arr = new uchar[height * width * 3];
    for(int i = 0; i < height * width; i++) {
        arr[i*3] = buffer[i].getR();
        arr[i*3 + 1] = buffer[i].getG();
        arr[i*3 + 2] = buffer[i].getB();
    }

    //Format_RGB888: RGB 24 bits per pixel
    QImage qImg(arr, width, height, width*3,QImage::Format_RGB888);

    ui->setImage(qImg);
    ui->setNormalStatus();

    delete[] arr;
}

void MainView::resizeEvent(QResizeEvent *event) {
    ui->setSelectionActive(false);
}
