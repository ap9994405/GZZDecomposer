#include "layoutabletreenode.h"

#include "ITreeNodeVistor.h"

LayoutableTreeNode::LayoutableTreeNode(LayoutableTreeNode* parent)
{
    setParent(parent);
}

void LayoutableTreeNode::setParent(LayoutableTreeNode *parent)
{
    m_parent = parent;
}

LayoutableTreeNode * LayoutableTreeNode::getParent()
{
    return m_parent;
}

int LayoutableTreeNode::numOfShownChildren()
{
    int total = 0;
    for(int i=0; i<m_children.size();++i)
    {
        if (!m_children[i]->isHidden())
            ++total;
    }
    return total;
}

int LayoutableTreeNode::numOfAllChildren()
{
    return m_children.size();
}

LayoutableTreeNode * LayoutableTreeNode::getShownChildAt(int index)
{
    int curIndex = 0;
    for(int i=0; i<m_children.size();++i)
    {
        if (!m_children.at(i)->isHidden())
        {
            if (curIndex == index)
                return m_children[i];
            ++curIndex;
        }
    }
//    qCritical() << "something wrong";
    return NULL;
}

QList<LayoutableTreeNode *> LayoutableTreeNode::getAllChildren()
{
    return m_children;
}

QList<LayoutableTreeNode *> LayoutableTreeNode::getShownChildren()
{
    QList<LayoutableTreeNode *> res;
    for(int i=0; i<m_children.size();++i)
    {
        if (!m_children[i]->isHidden())
        {
            res.append(m_children[i]);
        }
    }
    return res;
}

double LayoutableTreeNode::getChildrenCenter()
{
    LayoutableTreeNode* node = this->m_children.first();
    for(int i=0; i<m_children.size();++i)
    {
        if (!m_children[i]->isHidden())
        {
            node = m_children[i];
            break;
        }
    }

    LayoutableTreeNode* node1 = this->m_children.last();
    for(int i=m_children.size()-1; i>=0; --i)
    {
        if (!m_children[i]->isHidden())
        {
            node1 = m_children[i];
            break;
        }
    }
    return (node->m_prelim + ((node1->m_prelim - node->m_prelim) + node1->getWidth()) / 2.0) ;
}

void LayoutableTreeNode::initLayoutParameter()
{
    m_XPosition = m_YPosition = m_prelim = m_modifier = 0.0;
    m_leftNeighbor = m_rightNeighbor = NULL;
}

LayoutableTreeNode * LayoutableTreeNode::getLeftSibling()
{
    if ( m_parent == NULL )
        return NULL;
    int index = m_parent->m_children.indexOf(this);

    if ( index == 0 )
    {
        return NULL;
    }
    else
    {
        for(int i=index-1; i>=0; --i)
        {
            if (!m_parent->m_children[i]->isHidden())
            {
                return m_parent->m_children[i];
            }
        }
        return NULL;
    }
}

LayoutableTreeNode * LayoutableTreeNode::getRightSiling()
{
    if ( m_parent == NULL )
        return NULL;
    int index = m_parent->m_children.indexOf(this);

    if ( this == m_parent->m_children.last() )
    {
        return NULL;
    }
    else
    {
        for(int i=index+1; i<m_parent->m_children.size();++i)
        {
            if (!m_parent->m_children[i]->isHidden())
                return m_parent->m_children[i];
        }
        return NULL;

    }
}

void LayoutableTreeNode::visit(ITreeNodeVistor *vistor)
{
    int size = this->numOfShownChildren();
    vistor->visit(this);
    for(int i=0; i<size;++i)
    {
        LayoutableTreeNode* child = this->getShownChildAt(i);
        child->visit(vistor);
    }
}

void LayoutableTreeNode::appendChild(LayoutableTreeNode *child)
{
    m_children.append(child);
}

void LayoutableTreeNode::removeChild(LayoutableTreeNode *child)
{
    m_children.removeOne(child);
}
LayoutableTreeNode::~LayoutableTreeNode()
{
    QListIterator<LayoutableTreeNode*> it(m_children);
    while(it.hasNext())
    {
        delete it.next();
    }
}
