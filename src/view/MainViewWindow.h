//
// Created by tommaso on 12/05/20.
//

#ifndef PHOTOMAKERAPP_MAINVIEWWINDOW_H
#define PHOTOMAKERAPP_MAINVIEWWINDOW_H

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QGroupBox>
#include "subwidgets/LeftMenuBar.h"
#include "subwidgets/AbstractSheet.h"
#include "subwidgets/CropSheet.h"
#include "subwidgets/ColorSheet.h"
#include "subwidgets/FilterSheet.h"

QT_BEGIN_NAMESPACE

class MainViewWindow {
public:
    void setupUi(QMainWindow* view){
        //global settings
        view->resize(500, 400);
        view->setWindowTitle(QStringLiteral("Photo Maker APP"));
        //view->setStyleSheet("background-color:rgb(60,60,60)");

        //widget creation
        mainWidget = new QWidget(view);

        //horizontal layout initialization
        hBox = new QHBoxLayout(mainWidget);

        //first column initialization
        firstCol = new LeftMenuBar(mainWidget, view);
        hBox->addWidget(firstCol->getWidget());

        //second column initialization
        secondCol = new CropSheet(mainWidget);
        hBox->addWidget(secondCol->getSheet());

        //setting layout
        mainWidget->setLayout(hBox);
        view->setCentralWidget(mainWidget);

        QMetaObject::connectSlotsByName(view);
    }

    ~MainViewWindow(){
        delete firstCol;
        delete secondCol;
    }

    void setCropSheet() {
        this->setSheet(new CropSheet(mainWidget));
    }

    void setColorSheet() {
        this->setSheet(new ColorSheet(mainWidget));
    }

    void setFilterSheet() {
        this->setSheet(new FilterSheet(mainWidget));
    }

private:
    QWidget* mainWidget {nullptr};

    //horizontal layout
    QHBoxLayout* hBox {nullptr};

    //first column (effect selection)
    LeftMenuBar* firstCol {nullptr};

    //second column (effect sheet)
    AbstractSheet* secondCol {nullptr};

    //third column (image)
    QImage* image {nullptr};


    void setSheet(AbstractSheet* sheet) {
        if(secondCol != nullptr)
            delete secondCol;
        secondCol = sheet;
        hBox->insertWidget(1, secondCol->getSheet());
    }
};

QT_END_NAMESPACE

#endif //PHOTOMAKERAPP_MAINVIEWWINDOW_H
