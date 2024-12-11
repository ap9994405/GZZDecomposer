#ifndef MYGRAPHICSITEMGROUP_H
#define MYGRAPHICSITEMGROUP_H

#include <QGraphicsItemGroup>

class MyGraphicsItemGroup : public QGraphicsItemGroup
{
public:
    explicit MyGraphicsItemGroup( QGraphicsItem * parent = 0 );
    virtual QPainterPath shape();
    virtual void addToGroup(QGraphicsItem *item);
    virtual void removeFromGroup(QGraphicsItem *item);
    virtual QRectF boundingRect();
    virtual void moveBy(qreal dx, qreal dy);

private:
    QPainterPath m_shape;
};

#endif // MYGRAPHICSITEMGROUP_H
