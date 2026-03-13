#pragma once

#include <QtCore/qabstractitemmodel.h>
#include <QtCore/qstring.h>
#include <QtGui/qfilesystemmodel.h>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qtreeview.h>

#include "./file_list.hpp"

class Window : public QMainWindow {
public:
    QString currentPath;

    Window();
    Window(QString path);

    void updatePath(QString path);

private:
    FileList *treeView;
    QFileSystemModel *fileModel;
    QLineEdit *pathEdit;

    // All the constructors call this cause I'm dumb and this makes it cleaner.
    void init();

private slots:
    void itemDoubleClicked(const QModelIndex &index);
    void itemMiddleClicked(const QModelIndex &index);

    void pathEnter();
};
