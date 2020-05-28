//
// Created by tommaso on 12/05/20.
//

#ifndef PHOTOMAKERAPP_MAINVIEWWINDOW_H
#define PHOTOMAKERAPP_MAINVIEWWINDOW_H

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include "subwidgets/AbstractSheet.h"
#include "subwidgets/CropSheet.h"
#include "subwidgets/ColorSheet.h"
#include "subwidgets/FilterSheet.h"
#include "subwidgets/TopMenuBar.h"

QT_BEGIN_NAMESPACE

class MainViewWindow {
public:
    void setupUi(QMainWindow* view){
        superParent = view;
        //global settings
        view->resize(900, 600);
        view->setWindowTitle(QStringLiteral("Photo Maker APP"));
        //view->setStyleSheet("background-color:rgb(60,60,60)");

        //widget creation
        mainWidget = new QWidget(superParent);

        //horizontal layout initialization
        hBox = new QHBoxLayout(mainWidget);

        menuBar = new TopMenuBar(superParent);
        view->setMenuWidget(menuBar->getMenu());

        //effect sheet
        effectSheet = new CropSheet(superParent);
        hBox->insertWidget(1, effectSheet->getSheet());

        //image
        imgLabel = new QLabel(mainWidget);
        imgLabel->setText("Open an image to start");
        imgLabel->setAlignment(Qt::AlignCenter);
        hBox->insertWidget(0, imgLabel);

        //setting layout
        mainWidget->setLayout(hBox);
        view->setCentralWidget(mainWidget);

        QMetaObject::connectSlotsByName(view);
    }

    ~MainViewWindow(){
        delete menuBar;
        delete effectSheet;
    }

    void setLoadingState() {
        imgLabel->setText("Just a moment...");
        imgLabel->repaint();
    }

    void setImage(QImage& img) {
        qpixmap = QPixmap::fromImage(img);
        adjustImageSize();
    }

    void adjustImageSize() {
        if(qpixmap.height() > imgLabel->height() || qpixmap.width() > imgLabel->width())
            imgLabel->setPixmap(qpixmap.scaled(imgLabel->width(), imgLabel->height(),
                    Qt::KeepAspectRatio));
        else
            imgLabel->setPixmap(qpixmap);
    }

    void enableUndoBtn(bool v) {
        menuBar->getUndoAct()->setEnabled(v);
    }

    void enableRedoBtn(bool v) {
        menuBar->getRedoAct()->setEnabled(v);
    }

    void setCropSheet() {
        this->setSheet(new CropSheet(superParent));
    }

    void setColorSheet() {
        this->setSheet(new ColorSheet(superParent));
    }

    void setFilterSheet() {
        this->setSheet(new FilterSheet(superParent));
    }

private:
    QMainWindow* superParent {nullptr};
    QWidget* mainWidget {nullptr};

    //horizontal layout
    QHBoxLayout* hBox {nullptr};

    //top menu bar
    TopMenuBar* menuBar {nullptr};

    //effect sheet
    AbstractSheet* effectSheet {nullptr};

    //image
    QLabel* imgLabel {nullptr};
    QPixmap qpixmap;


    void setSheet(AbstractSheet* sheet) {
        if(effectSheet != nullptr)
            delete effectSheet;
        effectSheet = sheet;
        hBox->insertWidget(1, effectSheet->getSheet());
    }
};

QT_END_NAMESPACE

#endif //PHOTOMAKERAPP_MAINVIEWWINDOW_H
