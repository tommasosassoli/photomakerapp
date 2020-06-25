//
// Created by tommaso on 07/06/20.
//

#ifndef PHOTOMAKERAPP_RENDERAREA_H
#define PHOTOMAKERAPP_RENDERAREA_H


#include <QtWidgets/QWidget>
#include <QtWidgets/QRubberBand>

class RenderArea : public QWidget {
    Q_OBJECT
public:
    RenderArea(QWidget* parent = 0);

    void setImage(QImage& img) {
        pixmap = QPixmap::fromImage(img);
        update();
    }

    void setSelectionActive(bool active);

    QRect getSelectedArea();

    QSize minimumSizeHint() const override {
        return QSize(700, 400);
    }

protected:
    void paintEvent(QPaintEvent* event) override;

    void mousePressEvent(QMouseEvent* event) override;

    void mouseMoveEvent(QMouseEvent* event) override;

    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    // image
    QPixmap pixmap;
    QPoint p0;

    QPixmap pixmapScaled;

    // selection area
    bool selectionActive {false};
    QRubberBand* rubberBand;
    QPoint origSelection;
    bool mousePress {false};

    QPoint calcCenter() const;
};


#endif //PHOTOMAKERAPP_RENDERAREA_H
