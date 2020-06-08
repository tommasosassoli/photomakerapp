//
// Created by tommaso on 20/05/20.
//

#ifndef PHOTOMAKERAPP_TOPMENUBAR_H
#define PHOTOMAKERAPP_TOPMENUBAR_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QMenu>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QMainWindow>
#include "AbstractSheet.h"
#include "../../utils/ViewUtils.cpp"

class TopMenuBar {
public:
    TopMenuBar(QMainWindow* parent) {
        setupUi(parent);
    }

    ~TopMenuBar() {
        delete menuBar;
    }

    void setupUi(QWidget* parent) {
        menuBar = new QMenuBar(parent);

        QMenu* fileMenu = new QMenu("File", menuBar);
        QMenu* editMenu = new QMenu("Edit", menuBar);
        QMenu* selectionMenu = new QMenu("Selection", menuBar);
        QMenu* sheetMenu = new QMenu("View", menuBar);

        // file
        QAction* openAct = ViewUtils::createIconAction("open", fileMenu);
        QAction* saveAct = ViewUtils::createIconAction("save", fileMenu);
        QAction* closeAct = new QAction("Close", fileMenu);

        openAct->setStatusTip("Open an image");
        saveAct->setStatusTip("Save an image");
        closeAct->setStatusTip("Close the app");

        fileMenu->addAction(openAct);
        fileMenu->addAction(saveAct);
        fileMenu->addSeparator();
        fileMenu->addAction(closeAct);

        // edit
        undoAct = ViewUtils::createIconAction("undo", editMenu);
        redoAct = ViewUtils::createIconAction("redo", editMenu);
        undoAct->setEnabled(false);
        redoAct->setEnabled(false);

        undoAct->setStatusTip("Undo the last action");
        redoAct->setStatusTip("Redo the last action");

        editMenu->addAction(undoAct);
        editMenu->addAction(redoAct);

        // selection
        selectionAct = ViewUtils::createIconAction("Select", selectionMenu);
        selectionAct->setCheckable(true);

        selectionAct->setStatusTip("Enable the selection tool");

        selectionMenu->addAction(selectionAct);

        // sheet
        //QAction* cropAct = new QAction("Crop", sheetMenu);
        QAction* cropAct = ViewUtils::createIconAction("crop", sheetMenu);
        QAction* colorAct = ViewUtils::createIconAction("color", sheetMenu);
        QAction* filterAct = ViewUtils::createIconAction("filters", sheetMenu);

        cropAct->setStatusTip("Show the crop tab");
        colorAct->setStatusTip("Show the color tab");
        filterAct->setStatusTip("Show the filter tab");

        sheetMenu->addAction(cropAct);
        sheetMenu->addAction(colorAct);
        sheetMenu->addAction(filterAct);

        menuBar->addMenu(fileMenu);
        menuBar->addMenu(editMenu);
        menuBar->addMenu(selectionMenu);
        menuBar->addMenu(sheetMenu);

        // events
        QObject::connect(openAct, SIGNAL(triggered()), parent, SLOT(openImage()));
        QObject::connect(saveAct, SIGNAL(triggered()), parent, SLOT(saveImage()));
        QObject::connect(closeAct, SIGNAL(triggered()), parent, SLOT(closeApp()));

        QObject::connect(undoAct, SIGNAL(triggered()), parent, SLOT(undoCmd()));
        QObject::connect(redoAct, SIGNAL(triggered()), parent, SLOT(redoCmd()));
        QObject::connect(editMenu, SIGNAL(aboutToShow()), parent, SLOT(setUndoRedoState()));

        QObject::connect(selectionAct, SIGNAL(toggled(bool)), parent, SLOT(enableSelectionTool(bool)));

        QObject::connect(cropAct, SIGNAL(triggered()), parent, SLOT(setCropSheet()));
        QObject::connect(colorAct, SIGNAL(triggered()), parent, SLOT(setColorSheet()));
        QObject::connect(filterAct, SIGNAL(triggered()), parent, SLOT(setFilterSheet()));
    }

    QWidget* getMenu() const {
        return menuBar;
    }

    QAction* getUndoAct() {
        return undoAct;
    }

    QAction* getRedoAct() {
        return redoAct;
    }

    void deactivateSelection() {
        selectionAct->setChecked(false);
    }

private:
    QMenuBar* menuBar {nullptr};

    QAction* undoAct;

    QAction* redoAct;

    QAction* selectionAct;
};


#endif //PHOTOMAKERAPP_TOPMENUBAR_H
