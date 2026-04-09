#include "./window.hpp"
#include "./file_list.hpp"

#include <QtCore/qcontainerfwd.h>
#include <QtCore/qdir.h>
#include <QtCore/qlogging.h>
#include <QtCore/qnamespace.h>
#include <QtCore/qprocess.h>
#include <QtCore/qsettings.h>
#include <QtGui/qaction.h>
#include <QtGui/qfilesystemmodel.h>
#include <QtGui/qicon.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qtoolbutton.h>
#include <QtWidgets/qtreeview.h>

Window::Window() : Window(QDir::homePath()) {}

Window::Window(QString path) {
    currentPath = path;

    // settings
    QSettings settings;

    // test settings
    settings.setValue("opener/mp4", QStringList{"open", "/Applications/VLC.app"});

    auto toolSize = settings.value("toolbarIconSize", 20).toInt();

    // internal attributes
    setAttribute(Qt::WA_DeleteOnClose); // Super important, it's what makes windows delete themselves.
    setMinimumSize(300, 200);
    resize(600, 400);

    // start actions
    auto homeAction = new QAction("Home", this);
    homeAction->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::GoHome));

    auto upAction = new QAction("Up", this);
    upAction->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::GoUp));

    // init widgets
    fileModel = new QFileSystemModel();
    treeView = new FileList();
    pathEdit = new QLineEdit();
    auto container = new QWidget();
    auto toolbar = new QToolBar();
    auto vbox = new QVBoxLayout();

    // layouts
    vbox->addWidget(toolbar);
    vbox->setContentsMargins(0, 5, 0, 5);
    vbox->addWidget(treeView);

    container->setLayout(vbox);

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

void Window::updatePath(QString path) {
    QDir p(path);
    if (p.exists()) {
        currentPath = path;
        treeView->setRootIndex(fileModel->index(currentPath));
        pathEdit->setText(currentPath);
    }
}

void Window::itemDoubleClicked(const QModelIndex &index) {
    if (!index.isValid()) return;

    if (fileModel->isDir(index)) {
        updatePath(fileModel->filePath(index));
        return;
    }

    QSettings settings;

    auto fileName = fileModel->fileName(index);
    auto filePath = fileModel->filePath(index);

    QString extension;

    if (!fileName.contains(".")) {
        // TODO: no extension
        extension = "none";
    } else {
        extension = fileName.split(".").last();
    }

    auto sKey = QString("opener/%1").arg(extension);
    auto openerSetting = settings.value(sKey);

    if (openerSetting.isNull()) {
        // Use the default system opener.
        openerSetting = QStringList({"open"});
    }

    auto opener = openerSetting.toStringList();

    qDebug() << opener;

    auto program = opener.first();
    QStringList args;

    if (opener.length() > 1) {
        args = opener.sliced(1);
    }

    args.append(filePath);

    QProcess proc;
    proc.setProgram(program);
    proc.setArguments(args);
    proc.startDetached();
}

void Window::itemMiddleClicked(const QModelIndex &index) {
    if (!index.isValid()) return;

    qDebug() << fileModel->filePath(index) << "is dir:" << fileModel->isDir(index);

    if (fileModel->isDir(index)) {
        (new Window(fileModel->filePath(index)))->show();
    }
}

void Window::pathEnter() {
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
