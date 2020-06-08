//
// Created by tommaso on 12/05/20.
//

#ifndef PHOTOMAKERAPP_MAINVIEWWINDOW_H
#define PHOTOMAKERAPP_MAINVIEWWINDOW_H

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QStatusBar>
#include "subwidgets/AbstractSheet.h"
#include "subwidgets/CropSheet.h"
#include "subwidgets/ColorSheet.h"
#include "subwidgets/FilterSheet.h"
#include "subwidgets/TopMenuBar.h"
#include "subwidgets/RenderArea.h"

QT_BEGIN_NAMESPACE

class MainViewWindow {
public:
    void setupUi(QMainWindow* view){
        superParent = view;
        //global settings
        view->resize(900, 600);
        view->setWindowTitle(QStringLiteral("Photo Maker APP"));
        //view->setStyleSheet("background-color:rgb(60,60,60)");

        //widget creation
        mainWidget = new QWidget(superParent);

        //horizontal layout initialization
        hBox = new QHBoxLayout(mainWidget);

        menuBar = new TopMenuBar(superParent);
        view->setMenuWidget(menuBar->getMenu());

        //effect sheet
        effectSheet = new CropSheet(superParent);
        hBox->insertWidget(1, effectSheet->getSheet());

        //image
        renderArea = new RenderArea(superParent);
        hBox->insertWidget(0, renderArea);

        //setting layout
        mainWidget->setLayout(hBox);
        view->setCentralWidget(mainWidget);

        //status bar
        statusBar = new QStatusBar(superParent);
        statusBar->showMessage("Open an image to start");

        pathToImg = new QLabel(statusBar);
        statusBar->addPermanentWidget(pathToImg);

        view->setStatusBar(statusBar);

        QMetaObject::connectSlotsByName(view);
    }

    ~MainViewWindow(){
        delete menuBar;
        delete effectSheet;
    }

    void setLoadingState() {
        statusBar->showMessage("Load in progress");
        statusBar->repaint();
    }

    void setNormalStatus() {
        statusBar->clearMessage();
    }

    void setApplyingChangesState() {
        statusBar->showMessage("Applying changes");
        statusBar->repaint();
    }

    void setSavedState() {
        statusBar->showMessage("The image has been saved");
    }

    void setPathToImage(QString path) {
        pathToImg->setText("Path: " + path);
    }

    void setImage(QImage& img) {
        renderArea->setImage(img);
    }

    void enableUndoBtn(bool v, QString txt = "Undo") {
        QAction* act = menuBar->getUndoAct();
        act->setEnabled(v);
        act->setText(txt);
        if(txt != "Undo")
            act->setStatusTip("Undo the " + txt + " command");
        else
            act->setStatusTip("Undo the last command");
    }

    void enableRedoBtn(bool v, QString txt = "Redo") {
        QAction* act = menuBar->getRedoAct();
        act->setEnabled(v);
        act->setText(txt);
        if(txt != "Redo")
            act->setStatusTip("Redo the " + txt + " command");
        else
            act->setStatusTip("Redo the last command");
    }

    void setSelectionActive(bool active) {
        renderArea->setSelectionActive(active);
        if(!active)
            menuBar->deactivateSelection();
    }

    void setCropSheet() {
        this->setSheet(new CropSheet(superParent));
    }

    void setColorSheet(int h, int s, int v) {
        this->setSheet(new ColorSheet(superParent, h, s, v));
    }

    void setFilterSheet() {
        this->setSheet(new FilterSheet(superParent));
    }

private:
    QMainWindow* superParent {nullptr};
    QWidget* mainWidget {nullptr};

    //horizontal layout
    QHBoxLayout* hBox {nullptr};

    //top menu bar
    TopMenuBar* menuBar {nullptr};

    //effect sheet
    AbstractSheet* effectSheet {nullptr};

    //image
    RenderArea* renderArea {nullptr};

    //status bar
    QStatusBar* statusBar {nullptr};
    QLabel* pathToImg {nullptr};


    void setSheet(AbstractSheet* sheet) {
        if(effectSheet != nullptr)
            delete effectSheet;
        effectSheet = sheet;
        hBox->insertWidget(1, effectSheet->getSheet());
    }
};

QT_END_NAMESPACE

#endif //PHOTOMAKERAPP_MAINVIEWWINDOW_H
