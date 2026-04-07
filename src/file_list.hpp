#pragma once

#include <QtCore/qlogging.h>
#include <QtCore/qnamespace.h>
#include <QtCore/qtclasshelpermacros.h>
#include <QtCore/qtmetamacros.h>
#include <QtGui/qevent.h>
#include <QtWidgets/qabstractitemview.h>
#include <QtWidgets/qtreeview.h>

// NOTE: This is currently a single header due simply to it being tiny. I may rework a bunch of it later.
// and If I do it'll be split apart.
class FileList : public QTreeView {
    Q_OBJECT

public:
    FileList() : QTreeView() {
        setSelectionMode(QAbstractItemView::ExtendedSelection);
    }

protected:
    void mouseReleaseEvent(QMouseEvent *event) override {
        QPoint pos = event->position().toPoint();
        QPersistentModelIndex index = indexAt(pos);

        if (event->button() == Qt::MiddleButton && isValidIndex(&index)) {
            emit middleClicked(index);
        }

        QTreeView::mouseReleaseEvent(event);
    }

private:
    bool isValidIndex(QPersistentModelIndex *index) {
        bool isValid = (index->row() >= 0) && (index->column() >= 0) && (index->model() == model());

        return isValid;
    }

signals:
    void middleClicked(const QModelIndex &index);
};
