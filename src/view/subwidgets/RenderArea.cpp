//
// Created by tommaso on 07/06/20.
//

#include <QtGui/QPainter>
#include <QMouseEvent>
#include "RenderArea.h"

RenderArea::RenderArea(QWidget* parent) : QWidget(parent) {
        setMouseTracking(true);
        rubberBand = new QRubberBand(QRubberBand::Rectangle, this);

        QPalette palette;
        palette.setBrush(QPalette::Highlight, QBrush(Qt::white));

        rubberBand->setPalette(palette);
}

void RenderArea::paintEvent(QPaintEvent* event) {
    QPainter painter(this);

    // points
    p0 = calcCenter();
    int w = pixmap.width();
    int h = pixmap.height();

    // print pixmap
    if(h > this->height() || w > this->width())
        painter.drawPixmap(p0, pixmap.scaled(this->width(), this->height(),
                Qt::KeepAspectRatio));
    else
        painter.drawPixmap(p0, pixmap);
}

void RenderArea::setSelectionActive(bool active) {
    selectionActive = active;

    if(selectionActive) {
        rubberBand->setGeometry(QRect(p0, pixmap.size()));
        rubberBand->show();
    } else {
        rubberBand->hide();
    }
    update();
}

QPoint RenderArea::calcCenter() const {
    int w = (this->width() / 2) - (pixmap.width() / 2);
    int h = (this->height() / 2) - (pixmap.height() / 2);
    w = (w < 0) ? 0 : w;
    h = (h < 0) ? 0 : h;
    return QPoint(w, h);
}

void RenderArea::mousePressEvent(QMouseEvent *event) {
    if(selectionActive) {
        origSelection = event->pos();
        rubberBand->setGeometry(QRect(origSelection, QSize()));
        rubberBand->show();
        mousePress = true;
    }
}

void RenderArea::mouseMoveEvent(QMouseEvent *event) {
    if(selectionActive && mousePress){
        rubberBand->setGeometry(QRect(origSelection, event->pos()).normalized());
    }
}

void RenderArea::mouseReleaseEvent(QMouseEvent *event) {
    if(selectionActive) {
        QRect rubberGeometry = rubberBand->geometry();
        QRect imageGeometry = QRect(p0, pixmap.size());

        QRect intersect = imageGeometry.intersected(rubberGeometry);
        rubberBand->setGeometry(intersect);

        mousePress = false;
    }
}

QRect RenderArea::getSelectionAreaPosition() {
    if(selectionActive){
        QRect imageGeometry = QRect(p0, pixmap.size());
        return QRect(imageGeometry.x() - rubberBand->x(),
                imageGeometry.y() - rubberBand->y(),
                imageGeometry.size().width() - pixmap.size().width(),
                imageGeometry.size().height() - pixmap.size().height());
    }
    return QRect();
}

void RenderArea::repaintSelectionArea(QRect rect) {
    if(selectionActive){
        rubberBand->setGeometry(rect);
    }
}