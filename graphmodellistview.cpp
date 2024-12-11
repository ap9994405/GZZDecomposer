#include "graphmodellistview.h"

#include <QMouseEvent>
#include <QDebug>
#include <QtWidgets>

GraphModelListView::GraphModelListView(QWidget *parent) :
    QListView(parent)
{
}

void GraphModelListView::mouseReleaseEvent(QMouseEvent *)
{
//    qDebug() << e->button();
//    if (e->button() == Qt::RightButton)
//    {
//        QModelIndex index = this->indexAt(e->pos());
//        this->setCurrentIndex(index);
//        qDebug() << e->pos();
//    }
}
