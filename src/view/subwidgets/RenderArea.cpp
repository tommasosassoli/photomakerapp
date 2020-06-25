//
// Created by tommaso on 07/06/20.
//

#include <QtGui/QPainter>
#include <QMouseEvent>
#include <QtWidgets/QToolTip>
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
    if(h > this->height() || w > this->width()) {
        pixmapScaled = pixmap.scaled(this->width(), this->height(),Qt::KeepAspectRatio);
        painter.drawPixmap(p0, pixmapScaled);
    } else {
        painter.drawPixmap(p0, pixmap);
        pixmapScaled = QPixmap();
    }
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
    if(selectionActive) {
        this->setCursor(QCursor(Qt::CrossCursor));
        if (mousePress) {
            rubberBand->setGeometry(QRect(origSelection, event->pos()).normalized());
            QToolTip::showText(event->globalPos(), QString("%1, %2")
                    .arg(rubberBand->size().width())
                    .arg(rubberBand->size().height()), this);
        }
    } else
        this->setCursor(QCursor(Qt::ArrowCursor));
}

void RenderArea::mouseReleaseEvent(QMouseEvent *event) {
    if(selectionActive) {
        QRect rubberGeometry = rubberBand->geometry();
        QRect imageGeometry;
        if(pixmapScaled.isNull())
            imageGeometry = QRect(p0, pixmap.size());
        else
            imageGeometry = QRect(p0, pixmapScaled.size());

        QRect intersect = imageGeometry.intersected(rubberGeometry);
        rubberBand->setGeometry(intersect);

        mousePress = false;
    }
}

QRect RenderArea::getSelectedArea() {
    if(selectionActive) {
        QRect rubberGeometry = rubberBand->geometry();
        QPoint a, b;

        a.setX(rubberGeometry.x() - p0.x());
        a.setY(rubberGeometry.y() - p0.y());
        b.setX(a.x() + rubberGeometry.width() - 1);
        b.setY(a.y() + rubberGeometry.height() - 1);

        if(!pixmapScaled.isNull()) {
            double sx = pixmapScaled.width();
            double sy = pixmapScaled.height();
            sx = pixmap.width() / sx;
            sy = pixmap.height() / sy;

            a.setX(int(a.x() * sx));
            a.setY(int(a.y() * sy));
            b.setX(int(b.x() * sx));
            b.setY(int(b.y() * sy));
        }

        QRect result = QRect(a,b);
        return (result.width() > 2 && result.height() > 2)? result.normalized() : QRect();
    }
    return QRect();
}
