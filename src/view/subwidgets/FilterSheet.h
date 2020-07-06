//
// Created by tommaso on 12/05/20.
//

#ifndef PHOTOMAKERAPP_FILTERSHEET_H
#define PHOTOMAKERAPP_FILTERSHEET_H

#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include "AbstractSheet.h"

class FilterSheet : public AbstractSheet {
public:
    FilterSheet(QWidget* parent) {
        setupUi(parent);
    }

    void setupUi(QWidget* parent) {
        sheet = new QGroupBox(parent);

        QPushButton* blurButton = new QPushButton("Blur", sheet);
        QPushButton* sharpenButton = new QPushButton("Sharpen", sheet);
        QPushButton* laplacianButton = new QPushButton("Edge detection", sheet);
        QPushButton* grayscale = new QPushButton("Grayscale", sheet);
        QPushButton* binary = new QPushButton("Binary", sheet);
        QPushButton* negative = new QPushButton("Negative", sheet);
        QPushButton* cartoon = new QPushButton("Cartoon", sheet);

        QObject::connect(blurButton, SIGNAL(clicked()), parent, SLOT(applyBlur()));
        QObject::connect(sharpenButton, SIGNAL(clicked()), parent, SLOT(applySharpen()));
        QObject::connect(laplacianButton, SIGNAL(clicked()), parent, SLOT(applyLaplacian()));
        QObject::connect(grayscale, SIGNAL(clicked()), parent, SLOT(applyGrayscale()));
        QObject::connect(binary, SIGNAL(clicked()), parent, SLOT(applyBinary()));
        QObject::connect(negative, SIGNAL(clicked()), parent, SLOT(applyNegative()));
        QObject::connect(cartoon, SIGNAL(clicked()), parent, SLOT(applyCartoon()));

        QVBoxLayout* layout = new QVBoxLayout(sheet);
        layout->addWidget(blurButton);
        layout->addWidget(sharpenButton);
        layout->addWidget(laplacianButton);
        layout->addWidget(grayscale);
        layout->addWidget(binary);
        layout->addWidget(negative);
        layout->addWidget(cartoon);

        layout->setAlignment(Qt::AlignCenter);

        sheet->setLayout(layout);
        sheet->setMaximumWidth(200);
    }
};


#endif //PHOTOMAKERAPP_FILTERSHEET_H
