//
// Created by tommaso on 12/05/20.
//

#ifndef PHOTOMAKERAPP_COLORSHEET_H
#define PHOTOMAKERAPP_COLORSHEET_H

#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include "AbstractSheet.h"

class ColorSheet : public AbstractSheet {
public:
    ColorSheet(QWidget* parent) {
        setupUi(parent);
    }

    void setupUi(QWidget* parent) {
        sheet = new QGroupBox(parent);

        QPushButton* hueButton = new QPushButton("Hue", sheet);
        QPushButton* saturationButton = new QPushButton("Saturation", sheet);
        QPushButton* brightnessButton = new QPushButton("Brightness", sheet);

        QVBoxLayout* layout = new QVBoxLayout(sheet);
        layout->addWidget(hueButton);
        layout->addWidget(saturationButton);
        layout->addWidget(brightnessButton);

        layout->setAlignment(Qt::AlignCenter);

        sheet->setLayout(layout);
        sheet->setMaximumWidth(200);
    }
};


#endif //PHOTOMAKERAPP_COLORSHEET_H
