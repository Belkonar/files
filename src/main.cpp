#include "./window.hpp"

// Don't get rid of this, it fixes clangd and helps with finding the classes.
#include <QtCore/qdir.h>
#include <QtGui/qicon.h>
#include <QtWidgets>

void make_fixed(QWidget *w) {
    w->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

void set_no_spacing(QBoxLayout *layout) {
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
}

auto render() -> std::unique_ptr<QMainWindow> {
    auto home = QDir::homePath();
    auto window = std::make_unique<QMainWindow>();

    return std::move(window);
}

auto main(int argc, char *argv[]) -> int {
    QApplication a(argc, argv);

    qInfo("path %s", qUtf8Printable(QDir::homePath()));

    (new Window())->show();

    return a.exec();
}
