#ifndef GRAPHMODELGRAPHITEM2_H
#define GRAPHMODELGRAPHITEM2_H

#include <QGraphicsRectItem>
#include <QList>
#include <QHash>
#include <QFont>
#include "edgemodel.h"

class BondItem;
class GraphModel;
class GraphModelTag;


class GraphModelGraphicsItem2 : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    GraphModelGraphicsItem2(GraphModel* model, QGraphicsItem * parent = 0);
    bool isHidden();
    void setHidden(bool on);
    int getHeight();
    int getWidth();
    void unselectBonds();
    void selectBond(EdgeModel bond);
    ~GraphModelGraphicsItem2();
    GraphModel* getModel();

    QRectF boundingRect2();
    void updateFactor(const QString& HTMLCode);
    void setTagVisible(bool visible);
    void setShowTagWhenDisconnected(bool ){}
    void updateTag(){}
    void updateBoundingRect(){}
private:
    GraphModel* m_model;
    QList<BondItem*> m_bonditems;
    QHash<EdgeModel, BondItem*> m_edge_bond_mapping;

private:
protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
private slots:
    void itemBondSelected(BondItem* bond);
    void itemBondUnselected(BondItem* bond);
    void itemPolynomialChanged(GraphModel* model);
signals:
    void ZZPolynomialRequest(GraphModel* model);
private:
    void createInternels();
    void createFactor();
    bool m_isHidden;
    GraphModelTag* m_tagItem;
    QGraphicsTextItem *m_poly;
    QFont m_font;
};

#endif // GRAPHMODELGRAPHITEM2_H
