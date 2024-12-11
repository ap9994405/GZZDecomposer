#include "builderwidget.h"
#include "builderscene.h"
#include "bonditem.h"
#include <QtWidgets>
#include "utils.h"
#include "ringitem.h"
#include "zoomableview.h"


#include "graphmodel.h"

//#include <QGLWidget>


BuilderWidget::BuilderWidget(QWidget *parent)
    : QWidget(parent)
{

    QHBoxLayout *layout = new QHBoxLayout();
    layout->setMargin(0);
    scene = new BuilderScene(this);
    view = new ZoomableView(scene);
    layout->addWidget(view);
    this->setLayout(layout);
    view->setRenderHints(QPainter::Antialiasing);
    view->setContextMenuPolicy(Qt::CustomContextMenu);


//    view->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));

    clear();
    draw_grid();

    connect(view, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenu(QPoint)));;

}


BuilderWidget::~BuilderWidget()
{

}

void BuilderWidget::clear()
{
    QSetIterator<BondItem*> it(m_selected_edges);
    while(it.hasNext())
    {
        it.next()->toggleSelection();
    }
    m_selected_edges.clear();
    m_selected_rings.clear();
}

void BuilderWidget::draw_grid()
{
    double bondlength = 30.0;

    BondItem *item ;// = new BondItem();


    int len_x = 50;
    int len_y = 50;

    QPoint vertex_xys[7] = {QPoint(1,0), QPoint(0,-1), QPoint(-1,-1), QPoint(-1,0), QPoint(0,1), QPoint(1,1), QPoint(1,0)};

    for(int i=0; i<len_x; ++i)
    {
        for(int j=0; j<len_y;++j)
        {
            QPoint ring_center = ringXY2vertexXY(QPoint(i,j));
            QPolygonF ring;
            RingItem *r = new RingItem(QPoint(i,j));
            connect(r, SIGNAL(clicked(RingItem*)), this, SLOT(ringClicked(RingItem*)));
            for(int k=0; k<6; ++k)
            {
                QPoint ver_1 = ring_center + vertex_xys[k];
                QPoint ver_2 = ring_center + vertex_xys[k+1];
                QPointF v1 = vertexXY2XY(ver_1,bondlength); // vertexXY2XY in utils.cpp

                EdgeModel edge(ver_1, ver_2);   //edge(StartPoint,EndPoint)

                if (!edges.contains(edge))
                {
                    item = new BondItem(0,0,bondlength, edge, BondItem::Grid);
                    connect(item, SIGNAL(bondSelected(BondItem*)), this, SLOT(selectBond(BondItem*)));
                    connect(item, SIGNAL(bondUnselected(BondItem*)), this, SLOT(unselectBond(BondItem*)));
                    edges.insert(edge, item);
                    r->addBondItem(item);
                    scene->addItem(item);
//                    qDebug() << QString("[(%1,%2), (%3,%4)] added").arg(ver_1.x()).arg(ver_1.y()).arg(ver_2.x()).arg(ver_2.y());
                }
                else
                {

                    QHash<EdgeModel, BondItem*>::iterator eit=edges.find(edge);

                    BondItem *item = eit.value();
                    if (eit != edges.end())
                    {
//                        qDebug() << edge.toString() << " " << item->getEdgeModel().toString();
//                        qDebug() << qHash(edge) << " " << qHash(item->getEdgeModel());
                        r->addBondItem(item);
                    }
                    else
                    {

                    }


//                    qDebug() << QString("[(%1,%2), (%3,%4)] existed").arg(ver_1.x()).arg(ver_1.y()).arg(ver_2.x()).arg(ver_2.y());
                }


                ring << v1 ;
            }
//            qDebug() << "ring size: " << r->getNumOfBonds();
            r->setPolygon(ring);
            r->setOpacity(0.3);
            r->setZValue(-10);
            scene->addItem(r);

        }
    }

    view->centerOn(scene->sceneRect().center());

}

QList<EdgeModel> BuilderWidget::getGraph()
{
    QList<EdgeModel> res;
    QSetIterator<BondItem*> it(m_selected_edges);
    while(it.hasNext())
    {
        res.append(it.next()->getEdgeModel());
    }
    return res;
}

// add and remove bond from selected edges list
void BuilderWidget::selectBond(BondItem *bond)
{
    m_selected_edges.insert(bond);
    emit modified();
}

void BuilderWidget::unselectBond(BondItem *bond)
{
    m_selected_edges.remove(bond);
    emit modified();
}


void BuilderWidget::ringClicked(RingItem *ring)
{
    if (m_selected_rings.contains(ring))
    {
        ring->UnselectAllBonds();
        m_selected_rings.remove(ring);
        QSetIterator<RingItem*> it(m_selected_rings);
        while(it.hasNext())
        {
            it.next()->SelectAllBonds();
        }
    }
    else
    {
        ring->SelectAllBonds();
        m_selected_rings.insert(ring);
    }
    emit modified();
}

void BuilderWidget::contextMenu(QPoint point)
{
    QPoint globalPos = view->mapToGlobal(point);

    QMenu myMenu;
    myMenu.addAction("Compute ZZ polynomial...");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
//        qDebug() << "yes";
        GraphModel *model = getGraphModel();
        emit ZZPolynomialRequest(model);
        delete model;
    }
    else
    {
//        qDebug() << "no";
    }
}

GraphModel* BuilderWidget::getGraphModel()
{
    return new GraphModel(this->getGraph(),QList<EdgeModel>(), NULL, GraphModel::None, 0);
}

void BuilderWidget::setGridRotate(bool )
{
    QTransform q = view->transform();
    if (q.isRotating())
    {
        q.rotate(-30);
    }
    else
    {
        q.rotate(30);
    }
    view->setTransform(q);
}

