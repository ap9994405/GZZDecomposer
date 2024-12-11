#include "graphmodeltreenode.h"

#include "graphmodelgraphicsitem.h"

#include <QDebug>


GraphModelTreeNode::GraphModelTreeNode(GraphModelGraphicsItem* graphitem, GraphModelTreeNode* parent):LayoutableTreeNode(parent)
{
    m_graphitem = graphitem;
    m_isHidden = false;
}

GraphModelGraphicsItem * GraphModelTreeNode::getGraphicsItem()
{
    return m_graphitem;
}

QList<GraphModel *> GraphModelTreeNode::getChildrenModels()
{
    QListIterator<LayoutableTreeNode*> it(LayoutableTreeNode::getAllChildren());
    QList<GraphModel *> res;
    while(it.hasNext())
    {
        GraphModelTreeNode* node = dynamic_cast<GraphModelTreeNode*>(it.next());
        if (node!=NULL)
        {
            res.append(node->getModel());
        }
    }
    return res;
}

QList<GraphModelTreeNode *> GraphModelTreeNode::getAllChildren()
{
    QListIterator<LayoutableTreeNode*> it(LayoutableTreeNode::getAllChildren());
    QList<GraphModelTreeNode *> res;
    while(it.hasNext())
    {
        GraphModelTreeNode* node = dynamic_cast<GraphModelTreeNode*>(it.next());
        if (node!=NULL)
        {
            res.append(node);
        }
    }
    return res;
}

bool GraphModelTreeNode::hasChildren()
{
    return !m_children.isEmpty();
}

GraphModel *GraphModelTreeNode::getModel()
{
    return m_graphitem->getModel();
}

double GraphModelTreeNode::getWidth()
{
    return m_graphitem->getWidth();
}

double GraphModelTreeNode::getHeight()
{
    return m_graphitem->getHeight();
}

bool GraphModelTreeNode::isHidden()
{
    return m_isHidden;
}

void GraphModelTreeNode::setPosition(const QPointF &point)
{
    m_graphitem->setPos(point);
    emit PositionChanged();

}

GraphModelTreeNode::~GraphModelTreeNode()
{
    delete m_graphitem;
}

QPointF GraphModelTreeNode::getPos()
{
    return m_graphitem->pos();
}
