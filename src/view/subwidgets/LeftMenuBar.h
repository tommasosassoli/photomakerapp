//
// Created by tommaso on 12/05/20.
//

#ifndef PHOTOMAKERAPP_LEFTMENUBAR_H
#define PHOTOMAKERAPP_LEFTMENUBAR_H


#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

class LeftMenuBar {
public:
    LeftMenuBar(QWidget* parent, QMainWindow* mainView){
        this->mainView = mainView;
        this->setupUi(parent);
    }

    void setupUi(QWidget* parent){
        menu = new QGroupBox(parent);
        QPushButton* cropButton = new QPushButton("Crop", menu);
        QPushButton* colorButton = new QPushButton("Colors", menu);
        QPushButton* filterButton = new QPushButton("Filters", menu);
        QPushButton* openButton = new QPushButton("Open", menu);
        QPushButton* saveButton = new QPushButton("Save", menu);

        QVBoxLayout* layout = new QVBoxLayout(menu);
        layout->addWidget(cropButton);
        layout->addWidget(colorButton);
        layout->addWidget(filterButton);
        layout->addSpacing(30);
        layout->addWidget(openButton);
        layout->addWidget(saveButton);

        layout->setAlignment(Qt::AlignCenter);

        menu->setLayout(layout);
        menu->setMaximumWidth(100);

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
