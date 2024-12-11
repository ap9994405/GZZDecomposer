#ifndef TREELAYOUT_H
#define TREELAYOUT_H

#include <QList>
#include <QHash>
#include <QVariant>

class LayoutableTreeNode;
class ITreeNodeVistor;

class LayoutableTree
{
public:
    LayoutableTree(LayoutableTreeNode* root);

    void appendChild(LayoutableTreeNode* parent, LayoutableTreeNode* child);
    void deleteChild(LayoutableTreeNode* parent, LayoutableTreeNode* child);
//    void deleteAllChild(LayoutableTreeNode* parent);
    QList<LayoutableTreeNode*> getAllChildren(LayoutableTreeNode* parent);
    void reposition();
    LayoutableTreeNode* getRootNode();

    void visitTreeNodes(ITreeNodeVistor* vistor);

private:
    void shift_position(double x);
    void updatePosition(LayoutableTreeNode* node);


private:
    //layout helper functions
    void firstWalk(LayoutableTreeNode* node, int level);
    void secondWalk(LayoutableTreeNode* node, int level, double X, double Y);
    void apportion(LayoutableTreeNode* node, int level);
    void setLevelHeight(LayoutableTreeNode* node, int level);
    void setLevelWidth(LayoutableTreeNode* node, int level);
    void setNeighbors(LayoutableTreeNode* node, int level);
    LayoutableTreeNode* getLeftMost(LayoutableTreeNode* node, int level, int maxlevel);

private:
    QHash<int, double> m_maxLevelHeight;
    QHash<int, double> m_maxLevelWidth;
    QHash<int, LayoutableTreeNode*> m_previousLevelNode;
    QHash<QString, QVariant> m_config;
    double m_rootYOffset;
    double m_rootXOffset;



private:
    LayoutableTreeNode*  m_root;
};

#endif // TREELAYOUT_H
