#include <QtWidgets/qlabel.h>
#include <QtWidgets/qmainwindow.h>
#include <QtWidgets/qwidget.h>
#include <QtWidgets>
#include <memory>

std::shared_ptr<QMainWindow> render(const char *text) {

    auto window = std::make_shared<QMainWindow>();

    QWidget *container = new QWidget();
    QLabel *label = new QLabel(container);

    label->setText(text);

    window->setCentralWidget(container);

    window->show();

    return window;
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    auto w1 = render("Hi");
    auto w2 = render("Dave");

    return a.exec();
}
