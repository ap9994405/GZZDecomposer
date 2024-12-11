#include "mygraphicsitemgroup.h"

MyGraphicsItemGroup::MyGraphicsItemGroup( QGraphicsItem * parent) :QGraphicsItemGroup(parent)
{

}

QPainterPath MyGraphicsItemGroup::shape()
{
    return m_shape;
}

void MyGraphicsItemGroup::addToGroup(QGraphicsItem *item)
{
    QGraphicsItemGroup::addToGroup(item);
    m_shape.addPath(item->shape());
}

void MyGraphicsItemGroup::removeFromGroup(QGraphicsItem *item)
{
    m_shape -= item->shape();
    QGraphicsItemGroup::removeFromGroup(item);
}

QRectF MyGraphicsItemGroup::boundingRect()
{
    return m_shape.boundingRect();
}

void MyGraphicsItemGroup::moveBy(qreal dx, qreal dy)
{
    m_shape.translate(dx,dy);
    QGraphicsItemGroup::moveBy(dx,dy);
}
