#include "./window.hpp"
#include "file_list.hpp"

#include <QtCore/qdir.h>
#include <QtCore/qlogging.h>
#include <QtCore/qnamespace.h>
#include <QtCore/qsettings.h>
#include <QtGui/qaction.h>
#include <QtGui/qfilesystemmodel.h>
#include <QtGui/qicon.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qtoolbutton.h>
#include <QtWidgets/qtreeview.h>

Window::Window() {
    currentPath = QDir::homePath();
    setup();
}

Window::Window(QString path) {
    currentPath = path;
    setup();
}

void Window::updatePath(QString path) {
    QDir p(path);
    if (p.exists()) {
        currentPath = path;
        treeView->setRootIndex(fileModel->index(currentPath));
        pathEdit->setText(currentPath);
    }
}

void Window::setup() {
    // start preamble
    QSettings settings;

    setAttribute(Qt::WA_DeleteOnClose); // Super important, it's what makes windows delete themselves.
    setMinimumSize(300, 200);
    resize(600, 400);

    int toolSize = settings.value("settings/toolbarIconSize", 20).toInt();

    // start actions
    auto homeAction = new QAction("Home", this);
    homeAction->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::GoHome));

    auto upAction = new QAction("Up", this);
    upAction->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::GoUp));

    // init widgets
    auto container = new QWidget();
    auto toolbar = new QToolBar();
    auto vbox = new QVBoxLayout(container);
    fileModel = new QFileSystemModel();
    treeView = new FileList();
    pathEdit = new QLineEdit();

    // layouts
    vbox->addWidget(toolbar);
    vbox->setContentsMargins(0, 5, 0, 5);
    vbox->addWidget(treeView);

    setCentralWidget(container);

    // configure widgets
    pathEdit->setText(currentPath);

    toolbar->setToolButtonStyle(Qt::ToolButtonIconOnly);
    toolbar->setIconSize(QSize(toolSize, toolSize));
    toolbar->addAction(homeAction);
    toolbar->addAction(upAction);
    toolbar->addWidget(pathEdit);

    fileModel->setRootPath(currentPath);

    treeView->setExpandsOnDoubleClick(false);
    treeView->setModel(fileModel);
    treeView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    treeView->setRootIndex(fileModel->index(currentPath));

    // setup slots
    connect(treeView, &FileList::doubleClicked, this, &Window::itemDoubleClicked);
    connect(treeView, &FileList::middleClicked, this, &Window::itemMiddleClicked);
    connect(pathEdit, &QLineEdit::returnPressed, this, &Window::pathEnter);

    // slot actions
    connect(upAction, &QAction::triggered, this, &Window::upTriggered);
    connect(homeAction, &QAction::triggered, this, &Window::homeTriggered);
}

void Window::itemDoubleClicked(const QModelIndex &index) {
    if (!index.isValid()) return;

    qDebug() << fileModel->filePath(index) << "is dir:" << fileModel->isDir(index);

    if (fileModel->isDir(index)) {
        updatePath(fileModel->filePath(index));
    }
}

void Window::itemMiddleClicked(const QModelIndex &index) {
    if (!index.isValid()) return;

    qDebug() << fileModel->filePath(index) << "is dir:" << fileModel->isDir(index);

    if (fileModel->isDir(index)) {
        (new Window(fileModel->filePath(index)))->show();
    }
}

void Window::pathEnter() {
    qDebug() << "enter pressed";

    QDir target(pathEdit->text());

    if (target.exists()) {
        updatePath(target.absolutePath());
    } else {
        // TODO: alerting
        qDebug() << "target" << target << "does not exist";
    }
}

void Window::upTriggered(bool checked) {
    QDir p(currentPath);

    p.cdUp();

    if (p.exists()) {
        updatePath(p.absolutePath());
    }
}

void Window::homeTriggered(bool checked) {
    updatePath(QDir::homePath());
}
