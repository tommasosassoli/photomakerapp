//
// Created by tommaso on 12/05/20.
//

#ifndef PHOTOMAKERAPP_LEFTMENUBAR_H
#define PHOTOMAKERAPP_LEFTMENUBAR_H


#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include "AbstractSheet.h"

class LeftMenuBar : public AbstractSheet {
public:
    LeftMenuBar(QWidget* parent, QMainWindow* mainView){
        this->mainView = mainView;
        this->setupUi(parent);
    }

    void setupUi(QWidget* parent){
        menu = new QGroupBox(parent);
        QPushButton* cropButton = createIconButton("crop", menu);
        QPushButton* colorButton = createIconButton("color", menu);
        QPushButton* filterButton = createIconButton("filter", menu);
        QPushButton* openButton = createIconButton("open", menu);
        QPushButton* saveButton = createIconButton("save", menu);

        QVBoxLayout* layout = new QVBoxLayout(menu);
        layout->addWidget(cropButton);
        layout->addWidget(colorButton);
        layout->addWidget(filterButton);
        layout->addSpacing(30);
        layout->addWidget(openButton);
        layout->addWidget(saveButton);

        layout->setAlignment(Qt::AlignCenter);

        menu->setLayout(layout);
        menu->setMaximumWidth(150);

        // events
        QObject::connect(cropButton, SIGNAL(clicked()), mainView, SLOT(setCropSheet()));
        QObject::connect(colorButton, SIGNAL(clicked()), mainView, SLOT(setColorSheet()));
        QObject::connect(filterButton, SIGNAL(clicked()), mainView, SLOT(setFilterSheet()));
    }

    ~LeftMenuBar(){
        delete menu;
    }

    QGroupBox* getWidget() const {
        return menu;
    }

private:
    QGroupBox* menu {nullptr};
    QMainWindow* mainView {nullptr};
};


#endif //PHOTOMAKERAPP_LEFTMENUBAR_H
