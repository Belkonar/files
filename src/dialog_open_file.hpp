#pragma once

#include <QDialog>
#include <QtCore/qhashfunctions.h>
#include <QtCore/qlogging.h>
#include <QtCore/qobject.h>
#include <QtGui/qaction.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qdialogbuttonbox.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qwidget.h>

class OpenFileDialog : public QDialog {
    Q_OBJECT

public:
    OpenFileDialog(QWidget *widget, QString path, QString ext);

private:
    QString path;
    QString ext;
};
