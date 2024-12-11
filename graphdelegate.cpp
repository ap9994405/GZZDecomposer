#include "graphdelegate.h"
#include "graphmodel.h"

#include <QPainter>
#include <QtGui>

#include "graphmodelgraphicsitem.h"
#include <QAbstractItemView>

GraphDelegate::GraphDelegate(QAbstractItemView* view):m_view(view)
{
}

QSize GraphDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int width = (m_view->width()-25)/3;
    return QSize(std::max(200, width),200);
}

