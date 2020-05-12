//
// Created by tommaso on 12/05/20.
//

#ifndef PHOTOMAKERAPP_ABSTRACTSHEET_H
#define PHOTOMAKERAPP_ABSTRACTSHEET_H

#include <QtWidgets/QWidget>

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
};


#endif //PHOTOMAKERAPP_ABSTRACTSHEET_H
