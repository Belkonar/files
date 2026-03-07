#include <QtWidgets/qlabel.h>
#include <QtWidgets/qwidget.h>
#include <QtWidgets>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QMainWindow window;

    QWidget *container = new QWidget();
    QLabel *label = new QLabel(container);

    label->setText("Hi.");

    window.setCentralWidget(container);

    window.show();

    return a.exec();
}
