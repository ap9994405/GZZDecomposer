#ifndef TREELAYOUTNODE_H
#define TREELAYOUTNODE_H

#include <QList>
#include <QPoint>

class ITreeNodeVistor;
class LayoutableTreeNode
{
    friend class LayoutableTree;
protected:
    LayoutableTreeNode(LayoutableTreeNode* parent = 0);
protected:
    int numOfShownChildren();
    int numOfAllChildren();
    LayoutableTreeNode* getShownChildAt(int index);
    QList<LayoutableTreeNode*> getAllChildren();
    QList<LayoutableTreeNode*> getShownChildren();
    LayoutableTreeNode* getParent();
    void setParent(LayoutableTreeNode* parent = 0);
    void appendChild(LayoutableTreeNode* child);
    void removeChild(LayoutableTreeNode* child);
protected:
    QList<LayoutableTreeNode*> m_children;
    LayoutableTreeNode* m_parent;
private:
    void initLayoutParameter();
    //for layout algorithm
    //data
    double m_XPosition;
    double m_YPosition;
    double m_prelim;
    double m_modifier;
    LayoutableTreeNode* m_leftNeighbor;
    LayoutableTreeNode* m_rightNeighbor;
    //functions
    double getChildrenCenter();
    LayoutableTreeNode* getLeftSibling();
    LayoutableTreeNode* getRightSiling();

    void visit(ITreeNodeVistor* vistor);

protected:
    virtual bool isHidden() = 0;
    virtual double getHeight() = 0;
    virtual double getWidth() = 0;
    virtual void setPosition(const QPointF& point) = 0;
public:
    virtual ~LayoutableTreeNode();

};

#endif // TREELAYOUTNODE_H
