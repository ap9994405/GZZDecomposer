#ifndef BENZENOID_BUILDER_H
#define BENZENOID_BUILDER_H

#include <QtWidgets>
#include <QHash>
#include <QSet>
#include "edgemodel.h"
#include "bonditem.h"
#include "ringitem.h"


class BuilderScene;
class ZoomableView;
class GraphModel;

class BuilderWidget : public QWidget
{
    Q_OBJECT
public:
    BuilderWidget(QWidget *parent = 0);
    virtual ~BuilderWidget();
private:
    ZoomableView *view;
    BuilderScene *scene;
    QHash<EdgeModel, BondItem* > edges;
    QSet<BondItem*> m_selected_edges;
    QSet<RingItem*> m_selected_rings;
signals:
    void modified();
    void ZZPolynomialRequest(GraphModel*);
private slots:
    void selectBond(BondItem*);
    void unselectBond(BondItem*);
    void ringClicked(RingItem* ring);
    void contextMenu(QPoint point);
public slots:
    void clear();
    void draw_grid();
    QList<EdgeModel> getGraph();
    GraphModel* getGraphModel();
    void setGridRotate(bool rotate);
protected:

};

#endif // BENZENOID_BUILDER_H
