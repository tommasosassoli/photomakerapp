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

        QObject::connect(blurButton, SIGNAL(clicked()), parent, SLOT(applyBlur()));
        QObject::connect(sharpenButton, SIGNAL(clicked()), parent, SLOT(applySharpen()));
        QObject::connect(laplacianButton, SIGNAL(clicked()), parent, SLOT(applyLaplatian()));

        QVBoxLayout* layout = new QVBoxLayout(sheet);
        layout->addWidget(blurButton);
        layout->addWidget(sharpenButton);
        layout->addWidget(laplacianButton);

        layout->setAlignment(Qt::AlignCenter);

        sheet->setLayout(layout);
        sheet->setMaximumWidth(200);
    }
};


#endif //PHOTOMAKERAPP_FILTERSHEET_H
