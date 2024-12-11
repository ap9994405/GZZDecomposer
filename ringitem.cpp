#include "ringitem.h"
#include <QBrush>

#include <QGraphicsSceneMouseEvent>
#include "bonditem.h"
#include <QDebug>
#include <QGraphicsScene>

RingItem::RingItem(QPoint coord, QGraphicsItem *parent) :
    QGraphicsPolygonItem(parent), m_coord(coord)
{
    this->setBrush(QBrush(QColor("white"),Qt::SolidPattern));
    this->setAcceptHoverEvents(true);
    this->m_clicked = false;
}

const QVector<BondItem *> RingItem::getBonds()
{
    return m_bonds;
}

void RingItem::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
    hoverEnter();
}

void RingItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    hoverLeave();
}

void RingItem::addBondItem(BondItem *bond)
{
    m_bonds << bond;
}

void RingItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
//    qDebug() << "RingItem::mousePressEvent";
    if ( event->button() == Qt::LeftButton )
    {
        this->m_clicked = true;
    }
    else
    {
        this->m_clicked = false;
    }
}

void RingItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
//    qDebug() << QString("(%1, %2)").arg(event->pos().x()).arg(event->pos().y());
//    qDebug() << "RingItem::mouseReleaseEvent";
    if ( event->button() == Qt::LeftButton && this->contains(event->pos()))
    {
        if ( this->m_clicked )
        {
            emit clicked(this);
        }
    }
    this->m_clicked = false;
}

void RingItem::UnselectAllBonds()
{
    QVectorIterator<BondItem*> it(m_bonds);
    while (it.hasNext())
    {
        BondItem* bi = it.next();
        bi->unselectBond(true);
    }
}

void RingItem::hoverEnter()
{
    QBrush brush = this->brush();
    brush.setColor(QColor("blue"));
    this->setBrush(brush);
}

void RingItem::hoverLeave()
{
    QBrush brush = this->brush();
    brush.setColor(QColor("white"));
    this->setBrush(brush);
}

QPoint RingItem::getCoord()
{
    return m_coord;
}

void RingItem::notify()
{
    emit clicked(this);
}

void RingItem::SelectAllBonds()
{
    QVectorIterator<BondItem*> it(m_bonds);
    while (it.hasNext())
    {
        BondItem* bi = it.next();
        bi->selectBond(true);
    }
}

int RingItem::getNumOfBonds()
{
    return m_bonds.size();
}
