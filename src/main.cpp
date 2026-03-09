#include "./window.hpp"

// Don't get rid of this, it fixes clangd and helps with finding the classes.
#include <QtWidgets>

void make_fixed(QWidget *w) {
    w->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

void set_no_spacing(QBoxLayout *layout) {
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
}

std::unique_ptr<QMainWindow> render() {
    auto home = QDir::homePath();
    auto window = std::make_unique<QMainWindow>();

    return std::move(window);
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    auto w = new Window();
    w->show();

    return a.exec();
}
