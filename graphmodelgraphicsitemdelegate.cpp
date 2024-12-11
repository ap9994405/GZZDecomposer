#include "graphmodelgraphicsitemdelegate.h"
#include "graphmodelgraphicsitem.h"
#include "bonditem.h"
#include "graphmodel.h"

GraphModelGraphicsItemDelegate::GraphModelGraphicsItemDelegate(GraphModelGraphicsItem* item, QObject *parent) :
    QObject(parent)
{
    m_item = item;
    connect(m_item->getModel(),SIGNAL(PolynomialChanged(GraphModel*)), this, SLOT(itemPolynomialChanged(GraphModel*)));
}

void GraphModelGraphicsItemDelegate::itemBondSelected(BondItem *bond)
{
    m_item->selectBond(bond->getEdgeModel());
}

void GraphModelGraphicsItemDelegate::itemBondUnselected(BondItem *bond)
{
    m_item->unselectBonds();
}

void GraphModelGraphicsItemDelegate::itemPolynomialChanged(GraphModel *model)
{
    m_item->updateFactor(model->getPoly().toHTML());
}
