#include "./window.hpp"
#include "file_list.hpp"

#include <QtCore/qdir.h>
#include <QtCore/qnamespace.h>
#include <QtGui/qfilesystemmodel.h>
#include <QtGui/qicon.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qtoolbutton.h>
#include <QtWidgets/qtreeview.h>

Window::Window() {
    this->currentPath = QDir::homePath();
    this->init();
}

Window::Window(QString path) {
    this->currentPath = path;
    this->init();
}

void Window::updatePath(QString path) {
    this->currentPath = path;
    treeView->setRootIndex(fileModel->index(currentPath));
}

void Window::init() {
    this->setAttribute(Qt::WA_DeleteOnClose); // Super important, it's what makes windows delete themselves.;

    this->setMinimumSize(300, 200);

    this->resize(600, 400);

    auto container = new QWidget();

    auto vbox = new QVBoxLayout(container);
    vbox->setContentsMargins(0, 5, 0, 5);

    auto iconButton = new QToolButton();
    // iconButton->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::AddressBookNew));
    iconButton->setArrowType(Qt::UpArrow);
    vbox->addWidget(iconButton);

    auto lineEdit = new QLineEdit();
    lineEdit->setAttribute(Qt::WA_MacShowFocusRect, false);
    lineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    lineEdit->setFrame(false);
    lineEdit->setText(this->currentPath);

    auto rows = 5;
    QStringList tableHeaders("File");

    this->fileModel = new QFileSystemModel();

    this->fileModel->setRootPath(this->currentPath);

    this->treeView = new FileList();
    this->treeView->setExpandsOnDoubleClick(false);
    this->treeView->setModel(this->fileModel);
    this->treeView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->treeView->setRootIndex(this->fileModel->index(this->currentPath));

    vbox->addWidget(lineEdit);
    vbox->addWidget(this->treeView);

    this->setCentralWidget(container);

    // setup slots

    connect(this->treeView, &FileList::doubleClicked, this, &Window::itemDoubleClicked);
    connect(this->treeView, &FileList::middleClicked, this, &Window::itemMiddleClicked);
}

void Window::itemDoubleClicked(const QModelIndex &index) {
    if (!index.isValid()) return;

    qDebug() << fileModel->filePath(index) << "is dir:" << fileModel->isDir(index);

    if (this->fileModel->isDir(index)) {
        updatePath(fileModel->filePath(index));
    }
}

void Window::itemMiddleClicked(const QModelIndex &index) {
    if (!index.isValid()) return;

    qDebug() << this->fileModel->filePath(index) << "is dir:" << this->fileModel->isDir(index);

    if (this->fileModel->isDir(index)) {
        (new Window(this->fileModel->filePath(index)))->show();
    }
}
