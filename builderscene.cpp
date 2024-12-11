#include "builderscene.h"

#include <QGraphicsSceneEvent>

#include "bonditem.h"
#include "ringitem.h"

BuilderScene::BuilderScene(QObject *parent) :
    QGraphicsScene(parent)
{
    m_lineitem = new QGraphicsLineItem(m_line);
    m_lineitem->setVisible(false);
    this->addItem(m_lineitem);
    m_mousepressed = false;
}

BuilderScene::~BuilderScene()
{
}

void BuilderScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF pos = event->scenePos();
    emit onMouseMove(pos);
    if (m_mousepressed)
    {
        m_line.setP2(pos);
        m_lineitem->setLine(m_line);

        for(int i=0; i<m_tempitems.size(); ++i)
        {
            RingItem *r = dynamic_cast<RingItem*>(m_tempitems.at(i));
            if (r)
            {
                r->hoverLeave();
            }
        }
        m_tempitems = this->collidingItems(m_lineitem);
        for(int i=0; i<m_tempitems.size(); ++i)
        {
            RingItem *r = dynamic_cast<RingItem*>(m_tempitems.at(i));
            if (r)
            {
                r->hoverEnter();
            }

        }
    }
    QGraphicsScene::mouseMoveEvent(event);
}

void BuilderScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_mousepressed = true;
        m_line.setP1(event->scenePos());
    }
    QGraphicsScene::mousePressEvent(event);
}

void BuilderScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_tempitems.size() > 1)
    {
        for(int i=0; i<m_tempitems.size(); ++i)
        {
            RingItem *r = dynamic_cast<RingItem*>(m_tempitems.at(i));
            if (r)
            {
                r->hoverLeave();
                r->notify();
            }
        }
    }
    m_tempitems.clear();
    m_mousepressed = false;
    QGraphicsScene::mouseReleaseEvent(event);
}
