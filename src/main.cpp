#include <QtWidgets>
#include <iostream>

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
    window->setMinimumSize(300, 200);
    window->resize(600, 400);

    auto container = new QWidget();

    auto vbox = new QVBoxLayout(container);
    set_no_spacing(vbox);

    auto line_edit = new QLineEdit();
    line_edit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    line_edit->setFrame(false);
    line_edit->setText(home);

    auto rows = 5;
    QStringList table_headers("File");

    QFileSystemModel *model = new QFileSystemModel();
    std::cout << QDir::homePath().toStdString() << "\n";
    model->setRootPath(home);
    QTreeView *tree = new QTreeView();
    tree->setModel(model);
    tree->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    tree->setRootIndex(model->index(home));

    vbox->addWidget(line_edit);
    vbox->addWidget(tree);

    window->setCentralWidget(container);
    window->show();

    return std::move(window);
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    auto w1 = render();

    return a.exec();
}
