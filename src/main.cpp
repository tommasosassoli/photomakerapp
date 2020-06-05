
#include <QApplication>
#include "view/MainView.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Image<> i;
    i.setBuffer(new RGBPixel[1]);
    i.getBuffer()->setR(20);
    i.getBuffer()->getR();
    KernelMatrix k(nullptr, 3);
    k.getDim();

    ImageWrapper imageWrapper;
    MainViewController controller(&imageWrapper);
    MainView view(&imageWrapper, &controller);

    view.show();

    return app.exec();
}
