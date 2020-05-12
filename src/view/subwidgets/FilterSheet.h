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

        QPushButton* laplatianButton = new QPushButton("Laplatian", sheet);
        QPushButton* sharpenButton = new QPushButton("Sharpen", sheet);

        QVBoxLayout* layout = new QVBoxLayout(sheet);
        layout->addWidget(laplatianButton);
        layout->addWidget(sharpenButton);

        layout->setAlignment(Qt::AlignCenter);

        sheet->setLayout(layout);
        sheet->setMaximumWidth(200);
    }
};


#endif //PHOTOMAKERAPP_FILTERSHEET_H
