#include <QtWidgets>

void make_fixed(QWidget *w) {
    w->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

void set_no_spacing(QBoxLayout *layout) {
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
}

std::unique_ptr<QMainWindow> render() {
    auto window = std::make_unique<QMainWindow>();
    window->setMinimumSize(300, 200);
    window->resize(600, 400);

    auto container = new QWidget();

    auto vbox = new QVBoxLayout(container);
    set_no_spacing(vbox);

    auto line_edit = new QLineEdit();
    line_edit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    line_edit->setFrame(false);

    auto rows = 5;
    QStringList table_headers("File");

    auto table = new QTreeWidget();
    table->setColumnCount(1);

    table->setHeaderLabels(table_headers);
    table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    vbox->addWidget(line_edit);
    vbox->addWidget(table);

    window->setCentralWidget(container);
    window->show();

    return std::move(window);
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    auto w1 = render();

    return a.exec();
}
