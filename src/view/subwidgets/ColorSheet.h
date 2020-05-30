//
// Created by tommaso on 12/05/20.
//

#ifndef PHOTOMAKERAPP_COLORSHEET_H
#define PHOTOMAKERAPP_COLORSHEET_H

#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QLocale>
#include "AbstractSheet.h"

class ColorSheet : public AbstractSheet {
public:
    ColorSheet(QWidget* parent) {
        setupUi(parent);
    }

    void setupUi(QWidget* parent) {
        sheet = new QGroupBox(parent);

        QString hueSlider = "qlineargradient(x1:0, y1:0, x2:1, y2:0, "
                                               "       stop: 0 rgb(255,0,0), "
                                               "       stop: 0.16 rgb(255,255,0),"
                                               "       stop: 0.33 rgb(0,255,0), "
                                               "       stop: 0.48 rgb(0,255,255),"
                                               "       stop: 0.64 rgb(0,0,255),"
                                               "       stop: 0.8 rgb(255,0,255),"
                                               "       stop: 1 rgb(255,0,0));";

        QString satSlider = "qlineargradient(x1:0, y1:0, x2:1, y2:0, "
                                            "   stop: 0 rgb(255,240,240),"
                                            "   stop: 1 rgb(255,0,0));";

        QString briSlider = "qlineargradient(x1:0, y1:0, x2:1, y2:0, "
                            "   stop: 0 rgb(180,180,180),"
                            "   stop: 1 rgb(214,214,214));";


        QVBoxLayout* layout = new QVBoxLayout(sheet);
        layout->addWidget(createGroup("Hue", hueSlider, 0, 360, 180));
        //layout->addWidget(createSlider(hueSlider, 0, 360, 180));

        layout->addWidget(createGroup("Saturation", satSlider, -100, 100));
        //layout->addWidget(createSlider(satSlider, -100, 100));

        layout->addWidget(createGroup("Brightness", briSlider, -100, 100));
        //layout->addWidget(createSlider(briSlider, -100, 100));

        resetBtn = new QPushButton("Reset", sheet);
        resetBtn->setDisabled(true);

        QObject::connect(resetBtn, SIGNAL(clicked()), parent, SLOT(setColorSheet()));

        layout->addSpacing(50);
        layout->addWidget(resetBtn);

        layout->setAlignment(Qt::AlignCenter);

        sheet->setLayout(layout);
        sheet->setMaximumWidth(200);
    }

private:
    QPushButton* resetBtn;

    QString baseStyle
            {"QSlider {"
             "   min-height: 40px;"
             "   selection-background-color: transparent;"
             "}"
             "QSlider::groove:horizontal {"
             "   height: 5px;"
             "   margin: 0 12px;"
             "   background-color: %1"
             "}"
             "QSlider::handle:horizontal {"
             "   background-color: #e3e3e3;"
             "   border: 1px solid black;"
             "   border-radius: 5px;"
             "   width: 10px;"
             "   margin: -12px -12px;"
             "}"};

    QGroupBox* createGroup(QString labelName, QString &backgroundStyle, int minRange, int maxRange, int pos = 0) {
        QGroupBox *box = new QGroupBox(sheet);
        QVBoxLayout *vLayout = new QVBoxLayout(box);

        // first line: label, line edit
        QGroupBox *topGroup = new QGroupBox(sheet);
        QHBoxLayout *hLayout = new QHBoxLayout(topGroup);

        QLabel* label = new QLabel(labelName, topGroup);
        QSpinBox* field = new QSpinBox(topGroup);
        field->setMaximumWidth(50);
        field->setRange(minRange, maxRange);
        field->setValue(pos);

        hLayout->addWidget(label);
        hLayout->addWidget(field);
        topGroup->setLayout(hLayout);

        // second line: slider
        QSlider *slider = createSlider(backgroundStyle, minRange, maxRange, pos);

        vLayout->addWidget(topGroup);
        vLayout->addWidget(slider);
        box->setLayout(vLayout);

        // connect slider - spinBox
        QObject::connect(slider, &QSlider::sliderMoved, field, &QSpinBox::setValue);
        QObject::connect(field, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
                slider, &QSlider::setValue);

        // connect slider and spinBox - reset button
        QObject::connect(slider, &QSlider::sliderReleased, [this]() {resetBtn->setEnabled(true);});
        QObject::connect(field, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
                [this]() { resetBtn->setEnabled(true); });

        return box;
    }

    QSlider* createSlider(QString &backgroundStyle, int minRange, int maxRange, int pos) {
        QSlider* slider = new QSlider(Qt::Horizontal, sheet);
        slider->setRange(minRange, maxRange);
        slider->setSliderPosition(pos);
        slider->setStyleSheet(baseStyle.arg(backgroundStyle));
        return slider;
    }
};


#endif //PHOTOMAKERAPP_COLORSHEET_H
