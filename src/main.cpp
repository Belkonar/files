#include <QtWidgets>

std::unique_ptr<QMainWindow> render(const char *text) {
    auto window = std::make_unique<QMainWindow>();

    QWidget *container = new QWidget();
    QLabel *label = new QLabel(container);

    label->setText(text);

    window->setCentralWidget(container);

    window->show();

    return std::move(window);
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    auto w1 = render("Hi");
    auto w2 = render("Dave");

    return a.exec();
}
