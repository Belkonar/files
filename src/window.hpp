#pragma once

#include <QtCore/qabstractitemmodel.h>
#include <QtCore/qstring.h>
#include <QtGui/qfilesystemmodel.h>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/qtreeview.h>

class Window : public QMainWindow {
public:
    QString currentPath;

    Window();
    Window(QString path);

private:
    QTreeView *treeView;
    QFileSystemModel *fileModel;

    // All the constructors call this cause I'm dumb and this makes it cleaner.
    void init();

private slots:
    void itemDoubleClicked(const QModelIndex &index) {
        if (!index.isValid()) return;

        qDebug() << this->fileModel->filePath(index) << "is dir:" << this->fileModel->isDir(index);

        if (this->fileModel->isDir(index)) {
            (new Window(this->fileModel->filePath(index)))->show();
        }
    }
};
