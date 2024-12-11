#ifndef BUILDERSCENE_H
#define BUILDERSCENE_H

#include <QGraphicsScene>

class BondItem;

class BuilderScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit BuilderScene(QObject *parent = 0);
    virtual ~BuilderScene();
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
private:
    bool m_mousepressed;
    QLineF m_line;
    QGraphicsLineItem *m_lineitem;
    QList<QGraphicsItem*> m_tempitems;
signals:
    void onMouseMove(QPointF pos);
public slots:

};

#endif // BUILDERSCENE_H
