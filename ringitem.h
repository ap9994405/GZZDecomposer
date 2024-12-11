#ifndef RINGITEM_H
#define RINGITEM_H

#include <QGraphicsPolygonItem>

class BondItem;

class RingItem : public QObject, public QGraphicsPolygonItem
{
    Q_OBJECT
public:
    RingItem(QPoint coord, QGraphicsItem *parent = 0);
    const QVector<BondItem*> getBonds();
signals:
    void clicked(RingItem*);
public slots:
    void addBondItem(BondItem*);
    void UnselectAllBonds();
    void SelectAllBonds();
    void hoverEnter();
    void hoverLeave();
    QPoint getCoord();
    void notify();
    int getNumOfBonds();
private:
    QVector<BondItem*> m_bonds;
    bool m_clicked;
    QPoint m_coord;
protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // RINGITEM_H
