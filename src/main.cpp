#include "./window.hpp"

// Don't get rid of this, it fixes clangd and helps with finding the classes.
#include <QtCore/qdir.h>
#include <QtCore/qlogging.h>
#include <QtCore/qsettings.h>
#include <QtGui/qicon.h>
#include <QtWidgets>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("Belkonar");
    QCoreApplication::setOrganizationDomain("belkonar.com");
    QCoreApplication::setApplicationName("Files");

    QSettings test;
    qDebug() << test.fileName() << test.value("hi/dave");
    test.setValue("hi/dave", 23);

    qInfo() << "path:" << QDir::homePath() << QDir::drives();

    (new Window())->show();

    return a.exec();
}
