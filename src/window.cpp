#include "./window.hpp"

#include <QtCore/qdir.h>
#include <QtCore/qnamespace.h>
#include <QtGui/qfilesystemmodel.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qtreeview.h>

Window::Window() {
    this->currentPath = QDir::homePath();
    this->init();
}

Window::Window(QString path) {
    this->currentPath = path;
    this->init();
}

void Window::init() {
    this->setAttribute(Qt::WA_DeleteOnClose); // Super important;

    this->setMinimumSize(300, 200);

    this->resize(600, 400);

    auto container = new QWidget();

    auto vbox = new QVBoxLayout(container);
    vbox->setContentsMargins(0, 5, 0, 5);

    auto lineEdit = new QLineEdit();
    lineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    lineEdit->setFrame(false);
    lineEdit->setText(this->currentPath);

    auto rows = 5;
    QStringList tableHeaders("File");

    auto model = new QFileSystemModel();

    model->setRootPath(this->currentPath);
    auto tree = new QTreeView();
    tree->setModel(model);
    tree->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    tree->setRootIndex(model->index(this->currentPath));

    vbox->addWidget(lineEdit);
    vbox->addWidget(tree);

    this->setCentralWidget(container);
}
