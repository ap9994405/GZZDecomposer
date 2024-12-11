#include "graphitemconnectingline.h"
#include "graphmodeltreenode.h"
#include "graphmodelgraphicsitem.h"
#include "graphmodel.h"

#include <QGraphicsPathItem>

GraphItemConnectingLine::GraphItemConnectingLine(
        GraphModelTreeNode* parent, GraphModelTreeNode* child): m_parent(parent), m_child(child)
{
    setParentItem(child->getGraphicsItem());
    m_path_item = new QGraphicsPathItem(this);
    this->addToGroup(m_path_item);
    connect(m_parent,SIGNAL(PositionChanged()),this, SLOT(PositionChanged()));
    connect(m_child,SIGNAL(PositionChanged()),this, SLOT(PositionChanged()));
    m_textRect = new QGraphicsRectItem(m_path_item);
    m_textRect->setBrush(QBrush(QColor(Qt::white)));
    m_text = new QGraphicsTextItem(m_textRect);


    GraphModel::DecompositionType type = child->getGraphicsItem()->getModel()->getType();
    //the following if decided the labels of Decompose type
    if (type == GraphModel::Single)
    {
        m_text->setPlainText(tr("S"));
    }
    else if (type == GraphModel::Double)
    {
        m_text->setPlainText(tr("D"));
    }
    else if (type == GraphModel::Ring)
    {
        m_text->setPlainText(tr("A"));
    }
    else if (type == GraphModel::BisRing)
    {
        m_text->setPlainText(tr("B"));
    }
    else if (type == GraphModel::Fragment)
    {
        m_text->setPlainText(tr("F"));
    }
    QFont font;
    font.setFamily("Times New Roman");
    font.setPixelSize(40.0);
    m_text->setFont(font);
    m_textRect->setRect(m_text->boundingRect());

}


void GraphItemConnectingLine::PositionChanged()
{
    QPointF parent_mid(m_parent->getPos().x() + m_parent->getGraphicsItem()->boundingRect().center().x(),
                       m_parent->getPos().y() + m_parent->getGraphicsItem()->boundingRect().bottom() + 5.0);
    QPointF child_mid(m_child->getPos().x() + m_child->getGraphicsItem()->boundingRect().center().x(),
                      m_child->getPos().y() + m_child->getGraphicsItem()->boundingRect().top() - 5.0);
    double height = std::abs(parent_mid.y()-child_mid.y());
    QPainterPath path;
    path.moveTo(parent_mid);
    path.lineTo(parent_mid.x(),parent_mid.y()+(height/4.0));
    path.lineTo(child_mid.x(),parent_mid.y()+(height/4.0));
    path.lineTo(child_mid);

    m_path_item->setPath(mapFromScene(path));
    m_textRect->setPos(mapFromScene(child_mid.x()-m_textRect->rect().center().x(),parent_mid.y()+(height/3.0)));
}
