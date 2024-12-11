#include "QGraphicsTextItemWithBackgroundColor.h"
#include <QPainter>


QGraphicsTextItemWithBackgroundColor::QGraphicsTextItemWithBackgroundColor(const QString &text, QGraphicsItem *parent)
    : QGraphicsTextItem(text, parent)
{

}


void QGraphicsTextItemWithBackgroundColor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::white);
    painter->drawRect(boundingRect());
    QGraphicsTextItem::paint(painter, option, widget);
}
