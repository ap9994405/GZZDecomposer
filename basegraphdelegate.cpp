#include "basegraphdelegate.h"

#include <QPainter>
#include <QtGui>

#include "graphmodelgraphicsitem.h"
#include <QAbstractItemView>

BaseGraphDelegate::BaseGraphDelegate():
{
}

void BaseGraphDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    GraphModel* model = (GraphModel*)(index.model()->data(index,99).value<void*>());
    if (model != NULL)
    {
        QGraphicsScene *m_scene = new QGraphicsScene();
        if(option.state & QStyle::State_Selected)
        {
            painter->fillRect(option.rect, option.palette.highlight());
        }
        GraphModelGraphicsItem* item = new GraphModelGraphicsItem(model);

        if (!m_tagVisible)
        {
            qDebug() << item->boundingRect2();
            item->setTagVisible(m_tagVisible);
            qDebug() << item->boundingRect2();
        }
        painter->setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing | QPainter::TextAntialiasing);
        m_scene->addItem(item);

        painter->drawRect(option.rect);
        m_scene->render(painter,option.rect.adjusted(5,5,-5,-5));
    }
}

QSize BaseGraphDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(200,200);
}
