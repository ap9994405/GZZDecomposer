#ifndef BASEGRAPHDELEGATE_H
#define BASEGRAPHDELEGATE_H

#include <QAbstractItemDelegate>
#include <QtWidgets>
#include "graphmodel.h"


#include <QHash>

template<typename X>
class BaseGraphDelegate : public QAbstractItemDelegate
{
public:
    BaseGraphDelegate(bool drawRect = true, QObject* parent = 0):QAbstractItemDelegate(parent)
    {
        m_drawRect = drawRect;
        m_scene = new QGraphicsScene();
    }
    void paint_impl(GraphModel* model, const QStyleOptionViewItem &option, QPainter *painter) const
    {

        if (model != NULL)
        {

            if(option.state & QStyle::State_Selected)
            {
                painter->fillRect(option.rect, option.palette.highlight());
            }

            X* item = NULL;
            if (m_items.contains(model))
            {
                //delete m_items[model];
                item = m_items[model];
                item->updateTag();
                item->updateBoundingRect();
            }
            else
            {
                item = new X(model);

                item->setShowTagWhenDisconnected(true);
                m_items[model] = item;
            }


            painter->setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing | QPainter::TextAntialiasing);
            m_scene->addItem(item);

            if (m_drawRect)
            {
                painter->drawRect(option.rect);
            }

            QRectF itemRect = item->boundingRect() ;
            QRectF targetRect = option.rect.adjusted(5,5,-5,-5);

            double shift = 0.0;
            if (itemRect.width() > itemRect.height())
            {
                shift = targetRect.height()/2.0 - (itemRect.height()*(targetRect.width()/itemRect.width()))/2.0;
                if (shift < 0)
                    shift = 0.0;
                m_scene->render(painter,targetRect.adjusted(0,shift,0,0), itemRect);

            }
            if (itemRect.height() >= itemRect.width())
            {
                shift = targetRect.width()/2.0 - (itemRect.width()*(targetRect.height()/itemRect.height()))/2.0;
                if (shift < 0)
                {
                    shift = 0.0;
                }
                m_scene->render(painter,targetRect.adjusted(shift,0,0,0), itemRect);

            }
            m_scene->removeItem(item);
        }
    }

    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        GraphModel* model = (GraphModel*)(index.model()->data(index,99).value<void*>());
        paint_impl(model, option, painter);
    }
    virtual QSize sizeHint(const QStyleOptionViewItem &, const QModelIndex &) const
    {
        return QSize(200,200);
    }
    virtual ~BaseGraphDelegate()
    {
        QHashIterator<GraphModel*, X*> it(m_items);
        while(it.hasNext())
        {
            it.next();
            delete it.value();
        }
        delete m_scene;
    }

public:
    void setDrawRect(bool drawRect)
    {
        m_drawRect = drawRect;
    }

private:
    bool m_drawRect;
    mutable QHash<GraphModel*, X*> m_items;
    QGraphicsScene *m_scene;
};

#endif // BASEGRAPHDELEGATE_H
