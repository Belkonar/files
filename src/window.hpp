#pragma once

#include <QtCore/qabstractitemmodel.h>
#include <QtCore/qstring.h>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/qtreeview.h>

class Window : public QMainWindow {
public:
    QString currentPath;

    Window();
    Window(QString path);

private:
    QTreeView *treeView;
    // All the constructors call this cause I'm dumb and this makes it cleaner.
    void init();

private slots:
    void onItemClicked(const QModelIndex &index) {
        if (!index.isValid()) return;

        QString text = index.data(Qt::DisplayRole).toString();
        qDebug() << "Clicked:" << text << "(row" << index.row() << "col" << index.column() << ")";
    }
};
