//
// Created by tommaso on 12/05/20.
//

#ifndef PHOTOMAKERAPP_ABSTRACTSHEET_H
#define PHOTOMAKERAPP_ABSTRACTSHEET_H

#include <QtWidgets/QWidget>
#include <QFile>

class AbstractSheet {
public:
    virtual void setupUi(QWidget* parent) = 0;

    QGroupBox* getSheet() const {
        return sheet;
    }

    virtual ~AbstractSheet() {
        delete sheet;
    }

protected:
    QGroupBox* sheet;

    QPushButton* createIconButton(QString buttonName, QWidget* parent) {
        QPushButton* button = new QPushButton(parent);
        QString path = "resources/" + buttonName + ".svg";

        if(QFile::exists(path)){
            button->setIcon(QIcon(path));
            button->setIconSize(QSize(30,30));
        } else
            button->setText(buttonName);

        //button->setWhatsThis()
        button->setMinimumSize(130, 40);
        button->setStyleSheet("background-color: rgba(255,255,255,0);");
        return button;
    }
};


#endif //PHOTOMAKERAPP_ABSTRACTSHEET_H
