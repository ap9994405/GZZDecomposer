#include "layoutabletree.h"
#include "layoutabletreenode.h"

#include <QQueue>
#include "ITreeNodeVistor.h"

LayoutableTree::LayoutableTree(LayoutableTreeNode *root) :m_root(root)
{
}

void LayoutableTree::reposition()
{
    m_rootYOffset = 0.0;
    m_rootXOffset = 0.0;
    m_config["LevelSeparation"] = 120.0 ; /*80.0 + std::min(120.0, m_root->getHeight() / 2.0 );*/
    m_config["SiblingSeparation"] = 80.0 ;//std::max(40.0, m_root->getWidth() / 3.0 );
    m_config["SubtreeSeparation"] = 120.0; // std::max(80.0, m_root->getWidth());
    m_config["topXAdjustment"] = 0;
    m_config["topYAdjustment"] = 0;
    this->m_maxLevelHeight.clear();
    this->m_maxLevelWidth.clear();
    this->m_previousLevelNode.clear();


    int level = 0;
    firstWalk(m_root, level);
    this->m_rootXOffset = this->m_config["topXAdjustment"].toDouble() + this->m_root->m_XPosition;
    this->m_rootYOffset = this->m_config["topYAdjustment"].toDouble() + this->m_root->m_YPosition;
    secondWalk(m_root, 0, 0, 0);

    shift_position(m_root->m_XPosition);

    updatePosition(m_root);
}

LayoutableTreeNode *LayoutableTree::getRootNode()
{
    return m_root;
}

void LayoutableTree::visitTreeNodes(ITreeNodeVistor *vistor)
{
    if (m_root)
    {
        m_root->visit(vistor);
    }
}

void LayoutableTree::firstWalk(LayoutableTreeNode *node, int level)
{
    LayoutableTreeNode* leftSibling = NULL;
    node->m_XPosition = 0;
    node->m_YPosition = 0;
    node->m_prelim = 0;
    node->m_modifier = 0;
    node->m_leftNeighbor = NULL;
    node->m_rightNeighbor = NULL;
    this->setLevelHeight(node, level);
    this->setLevelWidth(node, level);
    this->setNeighbors(node, level);


    if ( node->numOfShownChildren() == 0 )
    {
        leftSibling = node->getLeftSibling();
        if (leftSibling != NULL)
        {
            node->m_prelim = leftSibling->m_prelim +
                    leftSibling->getWidth() +
                    this->m_config["SiblingSeparation"].toDouble();
        }
        else
        {
            node->m_prelim = 0;
        }
    }
    else
    {
        int n = node->numOfShownChildren();
        for(int i=0; i<n; ++i)
        {
            LayoutableTreeNode* child = node->getShownChildAt(i);
            firstWalk(child, level+1);
        }

        double midPoint = node->getChildrenCenter();
        midPoint -= (node->getWidth() / 2.0) ;
        leftSibling = node->getLeftSibling() ;
        if (leftSibling != NULL)
        {
            node->m_prelim = leftSibling->m_prelim +
                    leftSibling->getWidth() +
                    this->m_config["SiblingSeparation"].toDouble();
            node->m_modifier = node->m_prelim - midPoint;
            apportion(node, level);
        }
        else
        {
            node->m_prelim = midPoint;
        }
    }
}

void LayoutableTree::setLevelHeight(LayoutableTreeNode *node, int level)
{
    if ( this->m_maxLevelHeight[level] < node->getHeight())
        this->m_maxLevelHeight[level] = node->getHeight();
}

void LayoutableTree::setLevelWidth(LayoutableTreeNode *node, int level)
{
    if ( this->m_maxLevelWidth[level] < node->getWidth())
        this->m_maxLevelWidth[level] = node->getWidth();
}

void LayoutableTree::setNeighbors(LayoutableTreeNode *node, int level)
{
    if (this->m_previousLevelNode.contains(level))
    {
        node->m_leftNeighbor = this->m_previousLevelNode[level];
        node->m_leftNeighbor->m_rightNeighbor = node;
    }
    this->m_previousLevelNode[level] = node;
}

LayoutableTreeNode * LayoutableTree::getLeftMost(LayoutableTreeNode *node, int level, int maxlevel)
{
    if ( level >= maxlevel )
        return node;
    if ( node->numOfShownChildren() == 0 )
        return NULL;
    for(int i=0; i< node->numOfShownChildren(); ++i)
    {
        LayoutableTreeNode* child = node->getShownChildAt(i);
        LayoutableTreeNode* leftmostDescendant = getLeftMost(child, level+1, maxlevel);
        if ( leftmostDescendant != NULL)
        {
            return leftmostDescendant;
        }
    }
    return NULL;
}

void LayoutableTree::secondWalk(LayoutableTreeNode *node, int level, double X, double Y)
{
    double xTmp = this->m_rootXOffset + node->m_prelim + X;
    double yTmp = this->m_rootYOffset + Y;
    double maxsizeTmp = 0;


    maxsizeTmp = this->m_maxLevelHeight[level];

    node->m_XPosition = xTmp;
    node->m_YPosition = yTmp;
    if (node->numOfShownChildren() != 0)
    {
        secondWalk(node->m_children.first(), level+1, X+node->m_modifier, Y+maxsizeTmp+this->m_config["LevelSeparation"].toDouble());
    }
    LayoutableTreeNode* rightSibling = node->getRightSiling();
    if ( rightSibling != NULL)
    {
        secondWalk(rightSibling, level, X, Y);
    }
}

void LayoutableTree::apportion(LayoutableTreeNode *node, int )
{
    LayoutableTreeNode* firstChild = node->m_children.first();
    LayoutableTreeNode* firstChildLeftNeighbor = firstChild->m_leftNeighbor ;
    int j = 1;
    for(; firstChild != NULL && firstChildLeftNeighbor != NULL;)
    {
        double modifierSumRight = 0.0;
        double modifierSumLeft = 0;
        LayoutableTreeNode* rightAncestor = firstChild;
        LayoutableTreeNode* leftAncestor = firstChildLeftNeighbor;
        for(int l = 0; l < j; ++l)
        {
            rightAncestor = rightAncestor->m_parent;
            leftAncestor = leftAncestor->m_parent;
            modifierSumRight += rightAncestor->m_modifier;
            modifierSumLeft += leftAncestor->m_modifier;
        }
        double totalGap = (firstChildLeftNeighbor->m_prelim + modifierSumLeft + firstChildLeftNeighbor->getWidth() +
                           this->m_config["SubtreeSeparation"].toDouble()) - (firstChild->m_prelim + modifierSumRight);
        if ( totalGap > 0 )
        {
            LayoutableTreeNode* subtreeAux = node;
            int numSubtrees = 0;
            for(; subtreeAux != NULL && subtreeAux != leftAncestor; subtreeAux = subtreeAux->getLeftSibling())
            {
                numSubtrees++;
            }
            if ( subtreeAux != NULL)
            {
                LayoutableTreeNode* subtreeMoveAux = node;
                double singleGap = totalGap / static_cast<double>(numSubtrees);
                for(; subtreeMoveAux != leftAncestor; subtreeMoveAux = subtreeMoveAux->getLeftSibling())
                {
                    subtreeMoveAux->m_prelim += totalGap;
                    subtreeMoveAux->m_modifier += totalGap;
                    totalGap -= singleGap;
                }
            }
        }
        j++;
        if(firstChild->numOfShownChildren() == 0)
        {
            firstChild = this->getLeftMost(node, 0, j);
        }
        else
        {
            firstChild = firstChild->m_children.first();
        }
        if (firstChild != NULL)
        {
            firstChildLeftNeighbor = firstChild->m_leftNeighbor;
        }
    }
}

void LayoutableTree::shift_position(double x)
{
    QQueue<LayoutableTreeNode*> tree_queue;
    tree_queue.append(m_root);
    while(!tree_queue.isEmpty())
    {
        LayoutableTreeNode* item = tree_queue.first();
        item->m_XPosition -= x;
        tree_queue.pop_front();

        QListIterator<LayoutableTreeNode*> it(item->m_children);
        while(it.hasNext())
        {
            LayoutableTreeNode* node = it.next();
            if(!node->isHidden())
            {
                tree_queue.append(node);
            }
        }
    }
}
void LayoutableTree::updatePosition(LayoutableTreeNode *node)
{
    QListIterator<LayoutableTreeNode*> it(node->m_children);
    while (it.hasNext())
    {
        LayoutableTreeNode* item = it.next();
        item->setPosition(QPointF(item->m_XPosition, item->m_YPosition));
        updatePosition(item);
    }
}

void LayoutableTree::appendChild(LayoutableTreeNode *parent, LayoutableTreeNode *child)
{
    parent->appendChild(child);
    child->setParent(parent);
}

QList<LayoutableTreeNode *> LayoutableTree::getAllChildren(LayoutableTreeNode *parent)
{
    return parent->m_children;
}

void LayoutableTree::deleteChild(LayoutableTreeNode *parent, LayoutableTreeNode *child)
{
    parent->removeChild(child);
    child->setParent(NULL);
}

