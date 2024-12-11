#ifndef GRAPHMODELTREENODE_H
#define GRAPHMODELTREENODE_H

#include "layoutabletreenode.h"
#include <QObject>

class GraphModelGraphicsItem;
class GraphModel;
class GraphModelTreeNode : public QObject, public LayoutableTreeNode
{
    Q_OBJECT
    friend class GraphicsModelGraphicsItemVistor;
public:
    GraphModelTreeNode(GraphModelGraphicsItem* model, GraphModelTreeNode* parent = 0 );
    GraphModelGraphicsItem* getGraphicsItem();
    QList<GraphModel*> getChildrenModels();
    QList<GraphModelTreeNode*> getAllChildren();
    bool hasChildren();
    GraphModel* getModel();
    ~GraphModelTreeNode();
    QPointF getPos();
protected:
    virtual double getWidth();
    virtual double getHeight();
    virtual bool isHidden();
    virtual void setPosition(const QPointF &point);
signals:
    void PositionChanged();
private:
    GraphModelGraphicsItem* m_graphitem;
    bool m_isHidden;
};

#endif // GRAPHMODELTREENODE_H
