//
// Created by tommaso on 20/05/20.
//

#ifndef PHOTOMAKERAPP_VIEWUTILS_CPP
#define PHOTOMAKERAPP_VIEWUTILS_CPP

#include <QtWidgets/QPushButton>
#include <QtWidgets/QAction>
#include <QtCore/QFile>

namespace ViewUtils {

    inline QAction* createIconAction(QString buttonName, QWidget* parent) {
        QAction* act = new QAction(parent);
        QString path = "resources/" + buttonName + ".svg";

        if(QFile::exists(path)){
            act->setIcon(QIcon(path));
        }
        buttonName = buttonName.replace(0, 1, buttonName[0].toUpper()); //capitalize
        act->setText(buttonName);
        return act;
    }
}

#endif //PHOTOMAKERAPP_VIEWUTILS_CPP