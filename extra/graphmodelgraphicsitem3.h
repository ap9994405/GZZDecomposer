// This Header file is for ZZSPinpopulation

#ifndef GRAPHMODELGRAPHITEM_H
#define GRAPHMODELGRAPHITEM_H

#include <QGraphicsRectItem>
#include <QList>
#include <QHash>
#include <QFont>
#include <QPainterPath>
#include "edgemodel.h"

class BondItem;
class GraphModel;
class GraphModelTag;

class GraphModelGraphicsItem3 : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
    friend class GraphicsItemDebugDialog;
public:
    GraphModelGraphicsItem3(GraphModel* model, QGraphicsItem * parent = 0);
    bool isHidden();
    void setHidden(bool on);
    int getHeight();
    int getWidth();
    void unselectBonds();
    void selectBond(EdgeModel bond);
    ~GraphModelGraphicsItem3();
    GraphModel* getModel();
    QList<QPointF> atom_coordinate;

    QRectF boundingRect2();
    void updateFactor(const QString& HTMLCode);
    void setTagVisible(bool visible);
    void setShowTagWhenDisconnected(bool on);
    void setShowMarker(bool value);
    bool isMarkerShowed();
    void updateTag();

    void setBondSelectable(bool selectable);
    void setAtomNumberVisible(bool visible);

    void clearLink();
    void addLink(const QList<QPair<int, int> >& links);

    QPointF getMidPoint(const EdgeModel& edge) const;
    QList<QPointF> getRingPoints(const QList<EdgeModel>& edges) const;
    QPointF getStartPoint(const EdgeModel &edge) const;
    QPointF getEndPoint(const EdgeModel &edge) const;
    QMap<int, QGraphicsTextItem*> m_atomnumbers;
    QMap<int, QGraphicsEllipseItem*> m_atomItems;
    QMap<int, QPointF> m_atomPosition;
    QList<QGraphicsLineItem*> m_atomlinks;
    QList<QPointF> m_atom_pos;

private:
    GraphModel* m_model;
    QList<BondItem*> m_bonditems;
    QHash<EdgeModel, BondItem*> m_edge_bond_mapping;  
    BondItem* m_selected_bond;
    QGraphicsEllipseItem *m_selected_marker;

private:
protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
private slots:
    void itemBondSelected(BondItem* bond);
    void itemBondUnselected(BondItem* bond);
    void itemPolynomialChanged(GraphModel* model);
    void itemStateChanged(GraphModel*);
    void childTagChanged();
signals:
    void ZZPolynomialRequest(GraphModel* model);
    void tagChanged();
public slots:
    void setGridRotated(bool rotate);
    bool isGridRotated();
    void reset();
    void updateBoundingRect();
private:
    void updateItemPositions();
    void updatePath();

    void createInternels();
    void createContainers();


    void finalize();


    void createMolecule();
    void createTag();
    void createFactor();

    QPainterPath m_bondPath;
    bool m_isTagVisible;
    bool m_isRotated;
    bool m_isHidden;

    GraphModelTag* m_tagItem;
    QGraphicsTextItem *m_factor;
    QGraphicsItemGroup *m_bondGroup;
    QGraphicsItemGroup *m_totalGroup;
    QFont m_font;
    bool m_showTagWhenDisconnected;
    bool m_tagVisible;

private:
};



#endif // GRAPHMODELGRAPHITEM_H
