#ifndef GRAPHMODELGRAPHICSITEMDELEGATE_H
#define GRAPHMODELGRAPHICSITEMDELEGATE_H

#include <QObject>

class GraphModelGraphicsItem;
class BondItem;
class GraphModel;
class GraphModelGraphicsItemDelegate : public QObject
{
    Q_OBJECT
public:
    explicit GraphModelGraphicsItemDelegate(GraphModelGraphicsItem* item, QObject *parent = 0);
private slots:
    void itemBondSelected(BondItem* bond);
    void itemBondUnselected(BondItem* bond);
    void itemPolynomialChanged(GraphModel* model);
private:
    GraphModelGraphicsItem* m_item;
};

#endif // GRAPHMODELGRAPHICSITEMDELEGATE_H
