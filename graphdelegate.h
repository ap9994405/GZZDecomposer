#ifndef GRAPHDELEGATE_H
#define GRAPHDELEGATE_H

#include "basegraphdelegate.h"

#include <QAbstractItemDelegate>
#include <QGraphicsScene>


class QAbstractItemView;
template<typename X>
class GraphDelegate : public BaseGraphDelegate<X>
{
public:
    GraphDelegate(QAbstractItemView* view, bool drawRect = true, QObject* parent = 0):BaseGraphDelegate<X>(drawRect, parent), m_view(view)
    {
//        qDebug() << "GraphDelegate::ctor" ;
    }
    virtual ~GraphDelegate()
    {
//        qDebug() << "GraphDelegate::dtor" ;
    }

    QSize sizeHint(const QStyleOptionViewItem &, const QModelIndex &) const
    {
        int width = (m_view->width()-25)/3;
        return QSize(std::max(200, width),200);
    }
private:
    QAbstractItemView* m_view;

};


#endif // GRAPHDELEGATE_H
