#pragma once

#include <QtCore/qstring.h>
#include <QtWidgets/QMainWindow>

class Window : public QMainWindow {
public:
    QString currentPath;

    Window();
    Window(QString path);

private:
    // All the constructors call this cause I'm dumb and this makes it cleaner.
    void init();
};
