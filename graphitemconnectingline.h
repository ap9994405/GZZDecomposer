#ifndef GRAPHITEMCONNECTINGLINE_H
#define GRAPHITEMCONNECTINGLINE_H

#include <QObject>
#include <QtWidgets>


class GraphModelTreeNode;
class GraphItemConnectingLine : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
public:
    GraphItemConnectingLine(GraphModelTreeNode* parent, GraphModelTreeNode* child);
private slots:
    void PositionChanged();
private:
    GraphModelTreeNode* m_parent;
    GraphModelTreeNode* m_child;
    QGraphicsPathItem* m_path_item;
    QGraphicsRectItem *m_textRect;
    QGraphicsTextItem *m_text;
};

#endif // GRAPHITEMCONNECTINGLINE_H
