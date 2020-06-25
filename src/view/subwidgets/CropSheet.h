//
// Created by tommaso on 12/05/20.
//

#ifndef PHOTOMAKERAPP_CROPSHEET_H
#define PHOTOMAKERAPP_CROPSHEET_H

#include <QtWidgets/QGroupBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include "AbstractSheet.h"

class CropSheet : public AbstractSheet {
public:
    CropSheet(QWidget* parent) {
        setupUi(parent);
    }

    void setupUi(QWidget* parent) {
        sheet = new QGroupBox(parent);

        QPushButton* cropButton = new QPushButton("Crop", sheet);
        QPushButton* flipButton = new QPushButton("Flip", sheet);
        QPushButton* mirrorButton = new QPushButton("Mirror", sheet);

        QVBoxLayout* layout = new QVBoxLayout(sheet);
        layout->addWidget(cropButton);
        layout->addWidget(flipButton);
        layout->addWidget(mirrorButton);

        layout->setAlignment(Qt::AlignCenter);

        sheet->setLayout(layout);
        sheet->setMaximumWidth(200);

        QObject::connect(cropButton, SIGNAL(clicked()), parent, SLOT(makeCrop()));
        QObject::connect(flipButton, SIGNAL(clicked()), parent, SLOT(makeFlip()));
        QObject::connect(mirrorButton, SIGNAL(clicked()), parent, SLOT(makeMirror()));
    }
};


#endif //PHOTOMAKERAPP_CROPSHEET_H
