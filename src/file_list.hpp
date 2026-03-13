#pragma once

#include <QtCore/qlogging.h>
#include <QtCore/qtclasshelpermacros.h>
#include <QtCore/qtmetamacros.h>
#include <QtGui/qevent.h>
#include <QtWidgets/qabstractitemview.h>
#include <QtWidgets/qtreeview.h>

class FileList : public QTreeView {

protected:
    void mouseReleaseEvent(QMouseEvent *event) override {
        qDebug() << event;
        // test if it's valid, and also a middle mouse. If it is send it, otherwise pass along.

        QPoint pos = event->position().toPoint();
        QPersistentModelIndex index = indexAt(pos);

        QTreeView::mouseReleaseEvent(event);
    }
};
