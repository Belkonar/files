#pragma once

#include <QtCore/qstring.h>
#include <QtWidgets/QMainWindow>

class Window : public QMainWindow {
public:
    QString currentPath;

    Window();
};
