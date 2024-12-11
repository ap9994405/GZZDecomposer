// This cpp file is for ZZSPinpopulation

#include "graphmodelgraphicsitem4.h"
#include "graphmodel.h"
#include "bonditem.h"
#include <QtWidgets>
#include <QString>
#include "graphmodelgraphicsitemdelegate.h"
#include <QObject>

#include <QPainterPath>
#include "graphmodeltag.h"
#include "zzpolynomialcalculator.h"
#include <ostream>
#include <iostream>
#include <stdlib.h>

#include <QDebug>
#include <QGraphicsItem>
//#include "mygraphicsitemgroup.h"

#include "graphicsitemdebugdialog.h"
#include "utils.h"
#include "formats.h"

#include <QFont>
#include <QFontMetricsF>

#include "QGraphicsTextItemWithBackgroundColor.h"
using namespace std;


const double bondlength = 30.0;
const int tagSize = 40;
const double marker_size = bondlength/2.0;

GraphModelGraphicsItem4::GraphModelGraphicsItem4(GraphModel *model, QGraphicsItem *parent)
    :QGraphicsRectItem(parent)
{


    m_showTagWhenDisconnected = false;
    m_tagVisible = true;
    this->setAcceptHoverEvents(true);

    m_model = model;
    m_isHidden = false;
    m_font.setPixelSize(tagSize - 5);
    m_font.setFamily("Times New Roman");

    m_tagItem = NULL;
    m_factor = NULL;
    m_selected_bond = NULL;
    m_selected_marker = new QGraphicsEllipseItem(0,0,marker_size,marker_size,this);
    m_selected_marker->setBrush(QBrush(Qt::SolidPattern));
    m_selected_marker->setVisible(false);


//    connect(m_model, SIGNAL(StateChanged(GraphModel*)), this, SLOT(itemStateChanged(GraphModel*)));
    connect(m_model,SIGNAL(PolynomialChanged(GraphModel*)), this, SLOT(itemPolynomialChanged(GraphModel*)));


    createContainers();
    createInternels();

}

GraphModelGraphicsItem4::~GraphModelGraphicsItem4()
{
    finalize();
}

void GraphModelGraphicsItem4::createInternels()
{


    if (m_model->isDead() == true)
    {
        createMolecule();
        updatePath();
        createTag();
        createFactor();
        updateItemPositions();
        updateBoundingRect();

    }
    else
    {
        this->setPen(QPen(QColor("black")));
        this->setRect(0,0,100,100);
        QGraphicsTextItem *item = new QGraphicsTextItem(this);
        QFont font;
        font.setPixelSize(this->boundingRect().height());
        item->setDefaultTextColor(QColor("blue"));
        font.setFamily("Times New Roman");
        item->setFont(font);
        item->setPlainText("0");
        QPointF cp = this->boundingRect().center()-item->boundingRect().center();
        item->moveBy(cp.x(),cp.y());
    }


}





void GraphModelGraphicsItem4::createContainers()
{
    // initializes the class member of the graphics items.
    m_bondGroup = new QGraphicsItemGroup(this);
    m_bondGroup->setHandlesChildEvents(false);
    m_tagItem = new GraphModelTag(m_model,m_font);


    connect(m_tagItem, SIGNAL(tagChanged()), this, SLOT(childTagChanged()));

    m_factor = new QGraphicsTextItem();
    m_tagItem->hide();
    m_factor->hide();

    m_totalGroup = new QGraphicsItemGroup(this);
    m_totalGroup->setHandlesChildEvents(false);
    m_totalGroup->addToGroup(m_bondGroup);
    m_totalGroup->addToGroup(m_factor);
    m_totalGroup->addToGroup(m_tagItem);

    //    m_bondPath = new QPainterPath();
}

void GraphModelGraphicsItem4::finalize()
{
    delete m_bondGroup ;
    delete m_factor ;
    delete m_tagItem ;
    delete m_totalGroup;

    m_totalGroup = NULL;
    m_factor = NULL;
    m_tagItem = NULL;
    m_bondGroup = NULL;


}

void GraphModelGraphicsItem4::createMolecule()
{
    this->setPen(QPen(Qt::NoPen));

    m_bonditems.clear();
    m_edge_bond_mapping.clear();


    const QList<EdgeModel> &edges = m_model->getEdges();
    const QList<EdgeModel> &hidden_edges = m_model->getHiddenEdges();

    m_atomnumbers.clear();

    QMap<int, QPoint> atomIndexes;

    for(int i=0; i<edges.size(); ++i)
    {
        BondItem* bond = new BondItem(0,0,bondlength, edges[i], BondItem::Normal, this);
        QObject::connect(bond,SIGNAL(bondSelected(BondItem*)),this,SLOT(itemBondSelected(BondItem*)));
        QObject::connect(bond,SIGNAL(bondUnselected(BondItem*)),this,SLOT(itemBondUnselected(BondItem*)));
        m_edge_bond_mapping.insert(edges[i], bond);
        m_bondGroup->addToGroup(bond);
        m_bonditems.append(bond);

        atomIndexes.insert(m_model->getNeighborList().getIndex(edges[i].startPoint()),edges[i].startPoint());
        atomIndexes.insert(m_model->getNeighborList().getIndex(edges[i].endPoint()),edges[i].endPoint());

    }

    for(int i=0; i<hidden_edges.size(); ++i)
    {
        BondItem* bond = new BondItem(0,0,bondlength, hidden_edges[i], BondItem::Grid, this);
        m_edge_bond_mapping.insert(hidden_edges[i], bond);
        bond->setEnabled(false);
        bond->setZValue(-20);
        m_bondGroup->addToGroup(bond);

        atomIndexes.insert(m_model->getNeighborList().getIndex(hidden_edges[i].startPoint()),hidden_edges[i].startPoint());
        atomIndexes.insert(m_model->getNeighborList().getIndex(hidden_edges[i].endPoint()),hidden_edges[i].endPoint());


    }


//    for(int i=0 ;i<atomIndexes.size();i++)
//     {

//        atom_coordinate.append(atomIndexes.value(i));
//      }



    QListIterator<EdgeModel> it(m_model->getDoubleBonds());
    while(it.hasNext())
    {
        const EdgeModel &tmp = it.next();
        if (m_edge_bond_mapping.contains(tmp))
            m_edge_bond_mapping[tmp]->setDoubleBond(true);
        else
            qDebug() << "wtf";
    }
    QListIterator<QList<EdgeModel> > rit(m_model->getRings());
    while(rit.hasNext())
    {
        const QList<EdgeModel>& bonds = rit.next();
        QPointF center;
        for(int i=0; i<bonds.size(); ++i)
        {
            if (!m_edge_bond_mapping.contains(bonds[i]))
                return;
            BondItem* bond = m_edge_bond_mapping[bonds[i]];
            center += bond->mapToScene(bond->boundingRect().center());
        }
        center /= 6.0;
        QGraphicsEllipseItem *ring =  new QGraphicsEllipseItem(center.x()-15.0, center.y()-15.0, 30, 30, this);
        QPen pen;
        pen.setColor(QColor("#d0d0d0"));
        pen.setWidth(5);
        ring->setPen(pen);
        m_bondGroup->addToGroup(ring);
    }

    QRectF rect = m_bondGroup->boundingRect();
    double x = rect.x();
    double y = rect.y();
    m_bondGroup->moveBy(-x,-y);



    QMapIterator<int, QPoint> atom_it(atomIndexes);
    while(atom_it.hasNext())
    {
        atom_it.next();
        QPointF v = vertexXY2XY(atom_it.value(), bondlength);
        QString num = QString("%1").arg(atom_it.key()+1);


        QGraphicsTextItem * item = new QGraphicsTextItem(num,this);
        item->setDefaultTextColor(Qt::red);
        QFont font = item->font();
        QFontMetricsF metric(font);

        double center_x = v.x()-x;
        double center_y = v.y()-y;
        const double circle_size = 5.0;

        m_atomPosition[atom_it.key()] = QPointF(center_x, center_y);
        atom_coordinate.append(m_atomPosition[atom_it.key()]);

        item->setPos(center_x-(metric.width(num)/2.0), center_y);
        item->setAcceptHoverEvents(false);
        item->setVisible(false);
        m_atomnumbers.insert(atom_it.key(), item);

        QGraphicsEllipseItem* circle = new QGraphicsEllipseItem(center_x-circle_size/2.0, center_y-circle_size/2.0,
                                                                circle_size*2, circle_size*2, this);
        circle->setBrush(QBrush(Qt::yellow));
        circle->setPen(QPen(Qt::yellow));
        circle->setVisible(false);
        circle->setAcceptHoverEvents(false);
        m_atomItems.insert(atom_it.key(), circle);
    }
}

void GraphModelGraphicsItem4::createTag()
{
}

int GraphModelGraphicsItem4::getHeight()
{
    return boundingRect().height();
//    return rect().height();
}

int GraphModelGraphicsItem4::getWidth()
{
//    return rect().width();
    return boundingRect().width();
}

bool GraphModelGraphicsItem4::isHidden()
{
    return m_isHidden;
}

void GraphModelGraphicsItem4::setHidden(bool on)
{
    m_isHidden = on;
    setVisible(!m_isHidden);
}

void GraphModelGraphicsItem4::unselectBonds()
{
    m_selected_marker->setPos(0,0);
    m_selected_bond = NULL;
//    qDebug() << "GraphModelGraphicsItem::unselectBond";
    QListIterator<BondItem*> it(m_bonditems);
    while(it.hasNext())
    {
        BondItem* bond = it.next();
        if (bond->isSelected())
        {
            bond->setSelection(false);
        }
    }
    m_model->unselectBond();
}

void GraphModelGraphicsItem4::selectBond(EdgeModel bond)
{
    unselectBonds();
//    qDebug() << "GraphModelGraphicsItem::selectBond";
    if (m_edge_bond_mapping.contains(bond))
    {
        m_edge_bond_mapping[bond]->setSelection(true);
        m_selected_bond = m_edge_bond_mapping[bond];
        QPointF pos = m_edge_bond_mapping[bond]->mapToItem(this,m_edge_bond_mapping[bond]->boundingRect().center());
        m_selected_marker->setPos(pos.x()-marker_size/2.0,pos.y()-marker_size/2.0);
        m_selected_marker->setZValue(1000);
    }
    m_model->selectBond(bond);

}

GraphModel * GraphModelGraphicsItem4::getModel()
{
    return m_model;
}

QRectF GraphModelGraphicsItem4::boundingRect2()
{

//    QListIterator<QGraphicsItem*> it(this->childItems());

//    QRectF rect ;
//    while(it.hasNext())
//    {
//        QGraphicsItem* item = it.next();
//        if (item->isVisible())
//        {
//            rect = rect.united(item->boundingRect());
//        }
//    }
//    return rect;


    QRectF rect = boundingRect();
    if (m_tagItem == NULL)
    {
        return rect;
    }
    else
    {
        QRectF rect2 = m_tagItem->boundingRect();
        return rect.adjusted(0,0,0,rect2.height());
    }
}

void GraphModelGraphicsItem4::updateFactor(const QString &HTMLCode)
{
    m_factor->setHtml(HTMLCode);
    updateItemPositions();
    updateBoundingRect();
}

void GraphModelGraphicsItem4::createFactor()
{
    m_factor->setFont(m_font);
    m_factor->setHtml(m_model->getPoly().toHTML());
}



void GraphModelGraphicsItem4::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{

}

void GraphModelGraphicsItem4::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{

}

void GraphModelGraphicsItem4::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{

}

void GraphModelGraphicsItem4::itemBondSelected(BondItem *bond)
{
    selectBond(bond->getEdgeModel());
}

void GraphModelGraphicsItem4::itemBondUnselected(BondItem *)
{
    unselectBonds();
}

void GraphModelGraphicsItem4::itemPolynomialChanged(GraphModel *model)
{
    updateFactor(model->getPoly().toHTML());
}

void GraphModelGraphicsItem4::itemStateChanged(GraphModel *)
{
        finalize();
        createContainers();
        createInternels();
}

void GraphModelGraphicsItem4::childTagChanged()
{
    updateItemPositions();
    updateBoundingRect();
    emit tagChanged();
}

void GraphModelGraphicsItem4::setTagVisible(bool visible)
{
    m_tagVisible = visible;
    updateItemPositions();
    updateBoundingRect();
}

void GraphModelGraphicsItem4::setShowTagWhenDisconnected(bool on)
{
    m_showTagWhenDisconnected = on;
    updateItemPositions();
    updateBoundingRect();
}

void GraphModelGraphicsItem4::setShowMarker(bool value)
{
    if (m_selected_bond)
    {
        m_selected_marker->setVisible(value);
//        if (value)
//        {
//            QPen pen = m_selected_bond->pen();
//            pen.setColor(QColor(BondItem::selected_color_grayscale));
//            m_selected_bond->setPen(pen);
//        }
//        else
//        {
//            QPen pen = m_selected_bond->pen();
//            pen.setColor(QColor(BondItem::selected_color));
//            m_selected_bond->setPen(pen);
//        }
    }
}

bool GraphModelGraphicsItem4::isGridRotated()
{
    return m_isRotated;
}

void GraphModelGraphicsItem4::reset()
{
    delete m_bondGroup ;
    delete m_factor ;
    delete m_tagItem ;
    delete m_totalGroup;

    createContainers();
    createInternels();
}

void GraphModelGraphicsItem4::updateBoundingRect()
{


        this->setRect(0,0,100,100);


}

void GraphModelGraphicsItem4::setGridRotated(bool rotate)
{
    if (m_isRotated == rotate)
        return;
    m_isRotated = rotate;
    QTransform a ; //= m_bondGroup->transform();

    m_totalGroup->setPos(0,0);

    QRectF rect = m_bondGroup->boundingRect();
    QPointF pos = rect.center();

    if (m_isRotated)
    {
        a.translate(pos.x(), pos.y()).rotate(30).translate(-pos.x(), -pos.y());
    }
    else
    {
        a.translate(pos.x(), pos.y()).rotate(-30).translate(-pos.x(), -pos.y());
    }
    m_bondGroup->setTransform(a, true);

    updatePath();
    updateItemPositions();
    updateBoundingRect();

}

void GraphModelGraphicsItem4::updateItemPositions()
{
    m_totalGroup->setPos(0,0);

    QRectF rr = this->mapRectFromScene(m_bondGroup->mapToScene(m_bondPath).boundingRect());

    if (m_model->isFinished())
    {
        m_tagItem->hide();
        m_factor->setPos(rr.center().x()-m_factor->boundingRect().center().x(),rr.bottom());
        m_factor->show();
    }

    else
    {



        m_tagItem->setPos(rr.center().x()-m_tagItem->boundingRect().center().x(),rr.bottom());
        m_factor->setParentItem(m_tagItem);
        m_factor->setPos(-(m_factor->boundingRect().width()+5),0);       

        if (m_tagItem->boundingRect().width() > rr.width() && m_tagItem->pos().x() < 0)
        {
            m_totalGroup->moveBy(-m_tagItem->pos().x(),0);
        }

        if (m_model->getPoly().isIdentity())
        {
            m_factor->setVisible(false);
        }
        else
        {
            m_factor->setVisible(true);
        }
    }
}

void GraphModelGraphicsItem4::updatePath()
{
    QListIterator<BondItem*> it(m_edge_bond_mapping.values());
    QPainterPath path;
    while(it.hasNext())
    {
        path += it.next()->shape();
    }
    QPainterPathStroker stroker;
    stroker.setWidth(5.0);
    QPainterPath final_path = stroker.createStroke(path);

    m_bondPath.swap(final_path);
}


bool GraphModelGraphicsItem4::isMarkerShowed()
{
    return m_selected_marker->isVisible();
}

void GraphModelGraphicsItem4::updateTag()
{
    m_tagItem->setText(m_model->getFullTag());
}

void GraphModelGraphicsItem4::setBondSelectable(bool selectable)
{

    for(int i=0; i<m_bonditems.size();++i)
    {
        m_bonditems[i]->setAcceptHoverEvents(selectable);
        m_bonditems[i]->setAcceptedMouseButtons(Qt::NoButton);
    }

}

void GraphModelGraphicsItem4::setAtomNumberVisible(bool visible)
{
    for(auto& a:m_atomnumbers)
    {
        a->setVisible(visible);
    }

}

void GraphModelGraphicsItem4::clearLink()
{
    for(int i=0; i<m_atomlinks.size();++i)
    {
        delete m_atomlinks[i];
    }
    m_atomlinks.clear();

    QMapIterator<int, QGraphicsEllipseItem*> it(m_atomItems);
    while(it.hasNext())
    {
        it.next();
        it.value()->setPen(QPen(Qt::black));
    }
}

void GraphModelGraphicsItem4::addLink(const QList<QPair<int, int> > &links)
{

    for(int i=0; i<links.size();++i)
    {
        int index1 = links[i].first;
        int index2 = links[i].second;
        if (index1 > index2)
        {
            std::swap(index1, index2);
        }

        if (!m_atomPosition.contains(index1) || !m_atomPosition.contains(index2))
            return ;

        QPointF p1 = m_atomPosition[index1];
        QPointF p2 = m_atomPosition[index2];


        QGraphicsLineItem* item = new QGraphicsLineItem(QLineF(p1,p2), this);
        QPen pen(Qt::green, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
        item->setPen(pen);
        m_atomlinks.append(item);

        if (m_atomItems.contains(index1))
        {
            QGraphicsEllipseItem* atomItem = m_atomItems[index1];
            atomItem->setPen(QPen(Qt::green));
        }
        if (m_atomItems.contains(index2))
        {
            QGraphicsEllipseItem* atomItem = m_atomItems[index2];
            atomItem->setPen(QPen(Qt::green));
        }

    }



}

QPointF GraphModelGraphicsItem4::getMidPoint(const EdgeModel &edge) const
{
    return this->m_edge_bond_mapping[edge]->getMidPoint()+m_bondGroup->pos();
}

QPointF GraphModelGraphicsItem4::getStartPoint(const EdgeModel &edge) const
{
    return this->m_edge_bond_mapping[edge]->getStartPoint()+m_bondGroup->pos();
}

QPointF GraphModelGraphicsItem4::getEndPoint(const EdgeModel &edge) const
{
    return this->m_edge_bond_mapping[edge]->getEndPoint()+m_bondGroup->pos();
}


QList<QPointF> GraphModelGraphicsItem4::getRingPoints(const QList<EdgeModel> &edges) const
{
    QList<QPointF> uniq_points;
    const auto& edgepoint = this->m_edge_bond_mapping[edges.first()];

    QPointF shift(edgepoint->width/2.0,edgepoint->width/2.0);

    auto e1p1 = edgepoint->getStartPoint()+m_bondGroup->pos()+shift;
    auto e1p2 = edgepoint->getEndPoint()+m_bondGroup->pos()+shift;

    const auto& edgepoint2 = this->m_edge_bond_mapping[edges[1]];
    auto e2p1 = edgepoint2->getStartPoint()+m_bondGroup->pos()+shift;
    auto e2p2 = edgepoint2->getEndPoint()+m_bondGroup->pos()+shift;


    auto diff1 = e1p1 - e2p1;
    auto diff2 = e1p1 - e2p2;
    auto dis1 = QPointF::dotProduct(diff1, diff1);
    auto dis2 = QPointF::dotProduct(diff2, diff2);
    if ( dis1 > 0.2 && dis2 > 0.2)
    {
        uniq_points.append(e1p2);
    }
    else
    {
        uniq_points.append(e1p1);
    }

    for (int i=1; i<edges.size(); ++i)
    {
        const auto& edge = edges[i];
        const auto& edgepoint = this->m_edge_bond_mapping[edge];
        auto start_pos = edgepoint->getStartPoint()+m_bondGroup->pos()+shift;
        auto end_pos = edgepoint->getEndPoint()+m_bondGroup->pos()+shift;

        auto pos_diff = start_pos - uniq_points.last();
        if ( QPointF::dotProduct(pos_diff, pos_diff) < 0.1)
            uniq_points.append(end_pos);
        else
            uniq_points.append(start_pos);
    }

    return uniq_points;
}

