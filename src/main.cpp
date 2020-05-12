
#include <QApplication>
#include "view/MainView.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainView v;
    v.show();

    return app.exec();
}
