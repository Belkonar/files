#include "./window.hpp"

// Don't get rid of this, it fixes clangd and helps with finding the classes.
#include <QtCore/qdir.h>
#include <QtGui/qicon.h>
#include <QtWidgets>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    qInfo() << "path:" << QDir::homePath();

    (new Window())->show();

    return a.exec();
}
