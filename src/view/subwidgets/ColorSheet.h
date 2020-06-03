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
#include "AbstractSheet.h"
#include "../MainView.h"

class ColorSheet : public AbstractSheet {
public:
    ColorSheet(QWidget* parent, int h = 0, int s = 0, int v = 0) : hue(h), saturation(s), value(v) {
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
        layout->addWidget(createGroup(parent, "Hue",
                hueSlider, -180, 180, hue));
        QObject::connect(sliders[0], SIGNAL(valueChanged(int)), parent, SLOT(adjustHue(int)));

        layout->addWidget(createGroup(parent,"Saturation",
                satSlider, -100, 100, saturation));
        QObject::connect(sliders[1], SIGNAL(valueChanged(int)), parent, SLOT(adjustSaturation(int)));

        layout->addWidget(createGroup(parent, "Brightness",
                briSlider, -100, 100, value));
        QObject::connect(sliders[2], SIGNAL(valueChanged(int)), parent, SLOT(adjustValue(int)));

        resetBtn = new QPushButton("Reset", sheet);
        if(hue == 0 && saturation == 0 && value == 0)
            resetBtn->setDisabled(true);

        QObject::connect(resetBtn, SIGNAL(clicked()), parent, SLOT(setColorSheet()));

        layout->addSpacing(50);
        layout->addWidget(resetBtn);

        layout->setAlignment(Qt::AlignCenter);

        sheet->setLayout(layout);
        sheet->setMaximumWidth(200);
    }

private:
    int hue {0};
    int saturation {0};
    int value {0};

    QPushButton* resetBtn;

    std::vector<QSlider*> sliders;

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

    QGroupBox* createGroup(QWidget* parent, QString labelName, QString &backgroundStyle,
            int minRange, int maxRange, int pos = 0) {
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
//        QObject::connect(field, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
//                slider, &QSlider::setValue);
        QObject::connect(field, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
                [slider](int val){
            if(!slider->isSliderDown())
                slider->setValue(val);
        });

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
        slider->setTracking(false);
        slider->setStyleSheet(baseStyle.arg(backgroundStyle));

        sliders.push_back(slider);

        return slider;
    }
};


#endif //PHOTOMAKERAPP_COLORSHEET_H
