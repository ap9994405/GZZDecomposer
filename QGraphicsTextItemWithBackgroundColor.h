#ifndef QGRAPHICSTEXTITEMWITHBACKGROUNDCOLOR_H
#define QGRAPHICSTEXTITEMWITHBACKGROUNDCOLOR_H

#include <QGraphicsTextItem>

class QGraphicsTextItemWithBackgroundColor : public QGraphicsTextItem
{
public:
    QGraphicsTextItemWithBackgroundColor(const QString& text, QGraphicsItem *parent = 0);

    // QGraphicsItem interface
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // QGRAPHICSTEXTITEMWITHBACKGROUNDCOLOR_H
