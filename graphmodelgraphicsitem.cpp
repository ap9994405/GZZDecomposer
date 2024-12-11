#include "graphmodelgraphicsitem.h"
#include "graphmodel.h"
#include "bonditem.h"
#include <QtWidgets>
#include <QString>
#include "graphmodelgraphicsitemdelegate.h"
#include <QObject>

#include <QPainterPath>
#include "graphmodeltag.h"
#include "zzpolynomialcalculator.h"

#include <QDebug>
#include <QGraphicsItem>
//#include "mygraphicsitemgroup.h"

#include "graphicsitemdebugdialog.h"
#include "utils.h"
#include "formats.h"

#include <QFont>
#include <QFontMetricsF>

#include "QGraphicsTextItemWithBackgroundColor.h"

const double bondlength = 30.0;
const int tagSize = 40;
const double marker_size = bondlength/2.0;

GraphModelGraphicsItem::GraphModelGraphicsItem(GraphModel *model, QGraphicsItem *parent)
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

GraphModelGraphicsItem::~GraphModelGraphicsItem()
{
    finalize();
}

void GraphModelGraphicsItem::createInternels()
{
    if (m_model->isDead() == false)
    {
        createMolecule();
        updatePath();
        createTag();
        createFactor();
        updateItemPositions();
        updateBoundingRect();

        if (m_model->isDisconnected())
        {
            this->setEnabled(false);
        }
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



void GraphModelGraphicsItem::createContainers()
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

void GraphModelGraphicsItem::finalize()
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

void GraphModelGraphicsItem::createMolecule()
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

    QListIterator<EdgeModel> it(m_model->getDoubleBonds());
    while(it.hasNext())
    {
        const EdgeModel &tmp = it.next();
        if (m_edge_bond_mapping.contains(tmp))
            m_edge_bond_mapping[tmp]->setDoubleBond(true);
        else
            qDebug() << "wtf";
    }
    QListIterator<QList<EdgeModel> > rit(m_model->getRings());  //getRing
    while(rit.hasNext())
    {
        const QList<EdgeModel>& bonds = rit.next();
        QPointF center;
        QList<QPointF> bond_center;

        QPair<QPointF,float> farthest_edge; //Qpair<position,distance to center>
        for(int i=0; i<bonds.size(); ++i)
        {
            if (!m_edge_bond_mapping.contains(bonds[i]))
                return;
            BondItem* bond = m_edge_bond_mapping[bonds[i]];
            bond_center.append(bond->mapToScene(bond->boundingRect().center()));
            center += bond->mapToScene(bond->boundingRect().center());
        }
        center /= bonds.size();

        // qDebug()<<center;
        // qDebug()<<bond_center;
        float tmp_dis;
        if (bonds.size() == 6)
        {   
            QGraphicsEllipseItem *ring =  new QGraphicsEllipseItem(center.x()-15.0, center.y()-15.0, 30, 30, this);
            QPen pen;
            pen.setColor(QColor("#d0d0d0"));     //改ring顏色
            pen.setWidth(5);
            ring->setPen(pen);
            m_bondGroup->addToGroup(ring);
        }
        else if (bonds.size() == 10)
        {
            farthest_edge.first = bond_center[0];
            farthest_edge.second = pow((center.x() - bond_center[0].x()), 2)+pow((center.y() - bond_center[0].y()), 2);
            tmp_dis =  pow((center.x() - bond_center[1].x()), 2)+pow((center.y() - bond_center[1].y()), 2);
            for(int i=1; i<bonds.size(); ++i)
            {
                tmp_dis = pow((center.x() - bond_center[i].x()), 2)+pow((center.y() - bond_center[i].y()), 2);
                if (tmp_dis >= farthest_edge.second)
                {
                    // farthest_edge2 = farthest_edge;
                    // farthest_edge2.first = farthest_edge.first;
                    // farthest_edge2.second = farthest_edge.second;
                    farthest_edge.first = bond_center[i];
                    farthest_edge.second = tmp_dis;
                }
            }
            // QGraphicsEllipseItem *ring =  new QGraphicsEllipseItem(center.x()-15.0, center.y()-15.0, 30, 30, this);
            // QPen pen;
            // pen.setColor(QColor("#d0d0d0"));     //改ring顏色
            // pen.setWidth(5);
            // ring->setPen(pen);
            // m_bondGroup->addToGroup(ring);
            // float slope;
            QPointF new_center1,new_center2,center_to_edge;
            QPainterPath path,remove_center_bond; 
            float slope,ang_rad,ang_deg,rot_rad,rot_deg;

            center_to_edge = center - farthest_edge.first;
            
            if (center_to_edge.x() < 0 )
            {
                center_to_edge = -center_to_edge;
            } 
            //always make the circle at the top and right be the first one
            if (abs(center_to_edge.x()) > abs(center_to_edge.y()))
            {
                new_center1 = center + center_to_edge/2;
                new_center2 = center - center_to_edge/2;                
            }
            else 
            {
                new_center2 = center + center_to_edge/2;
                new_center1 = center - center_to_edge/2;  
            }

            slope = center_to_edge.y()/center_to_edge.x();
            if (slope == 0)
            {
                ang_rad = 0;
                ang_deg = 0;
            }
            else if (slope > 0)
            {
                ang_rad = 0.523598776;
                ang_deg = 30;
            }
            else
            {
                ang_rad = -0.523598776;
                ang_deg = -30;
            }
            rot_rad = 1.00999558/2; //can be Adjust
            rot_deg = 57.868484/2;  //rot_deg = rot_rad*180/M_PI;
            QPointF ring1_begin,ring1_end,ring2_begin,ring2_end;
            float new_x,new_y;
            //if draw bridge then draw circle, might remove the not smooth problem.
            if (abs(center_to_edge.x()) > abs(center_to_edge.y()))  //or slope of two furthest dege is is zero
            {   
                // qDebug() << "slope = 0";
                // cover center of bond with white line
                remove_center_bond.moveTo(center.x(), center.y()+3);
                remove_center_bond.lineTo(center.x(), center.y()-3);
                QGraphicsPathItem *back_ground = new QGraphicsPathItem(remove_center_bond);
                QPen white_line;
                white_line.setColor(QColor("#ffffff"));  //#ffffff white
                white_line.setWidth(6);
                back_ground->setPen(white_line);
                m_bondGroup->addToGroup(back_ground);
                
                ring1_begin.setX(new_center1.x() + 15*cos(-M_PI/2-rot_rad));
                ring1_begin.setY(new_center1.y() - 15*sin(-M_PI/2-rot_rad));
                // first ring 
                path.moveTo(ring1_begin.x(),ring1_begin.y());
                path.arcTo(new_center1.x() - 15, new_center1.y() - 15, 30, 30, -90-rot_deg, 180+rot_deg*2);
                
                // ring1_end = path.elementAt(1);
                ring1_end.setX(new_center1.x() + 15*cos(M_PI/2+rot_rad));
                ring1_end.setY(new_center1.x() + 15*cos(M_PI/2+rot_rad));
                ring2_begin.setX(new_center2.x() - 15*cos(-M_PI/2-rot_rad));
                ring2_begin.setY(new_center2.y() + 15*sin(-M_PI/2-rot_rad));
                // upper bridge of the rings  
                for (qreal x = ring1_end.x(); x >= ring2_begin.x(); x -= 0.01)
                {
                    qreal y = -std::pow(17.7262+0.443155*std::pow(x-center.x(),2),0.5)+center.y();
                    // qreal y=-0.025*(x-center.x())*(x-center.x())-4.81784+center.y();
                    path.lineTo(x, y);
                }
                // second ring 
                // path.moveTo(ring2_begin.x(), ring2_begin.y());
                path.arcTo(new_center2.x() - 15, new_center2.y() - 15, 30, 30, 90-rot_deg, 180+rot_deg*2);
                // lower bridge of the rings,but use same parameter as upper bridge
                for (qreal x = ring2_begin.x(); x <= ring1_end.x(); x += 0.01)
                {
                    qreal y = std::pow(17.7262+0.443155*std::pow(x-center.x(),2),0.5)+center.y();
                    // qreal y=0.025*(x-center.x())*(x-center.x())+4.81784+center.y();
                    path.lineTo(x, y);
                }
            }
            else if (slope > 0)
            {
                // float coeff_a, coeff_b, coeff_c, val_1, val_2, previous_y;
                // qDebug() << "slope > 0";
                // ring1_begin.setX(new_center1.x() + 15*cos(ang_rad-rot_rad));
                // ring1_begin.setY(new_center1.y() - 15*sin(ang_rad-rot_rad));
                remove_center_bond.moveTo(center.x(), center.y()+3);
                remove_center_bond.lineTo(center.x(), center.y()-3);
                QGraphicsPathItem *back_ground = new QGraphicsPathItem(remove_center_bond);
                QPen white_line;
                white_line.setColor(QColor("#ffffff"));  //#ffffff white
                white_line.setWidth(6);
                back_ground->setPen(white_line);
                m_bondGroup->addToGroup(back_ground);

                path.moveTo(new_center1.x() + 15*cos(ang_rad-rot_rad), new_center1.y() - 15*sin(ang_rad-rot_rad));
                path.arcTo(new_center1.x() - 15, new_center1.y() - 15, 30, 30, 0+ang_deg-rot_deg, 180+rot_deg*2);
                
                ring1_end.setX(new_center1.x() + 15*cos(M_PI+ang_rad+rot_rad));
                ring1_end.setY(new_center1.y() - 15*sin(M_PI+ang_rad+rot_rad));
                ring2_begin.setX(new_center2.x() - 15*cos(-ang_rad+rot_rad));
                ring2_begin.setY(new_center2.y() + 15*sin(-ang_rad+rot_rad));
                //先算出垂直之hyperbola 然後再旋轉
                for (qreal x = center.x()-18.7237; x <= center.x()+18.7237; x += 0.01)
                {
                    qreal y = std::pow(17.7262+0.443155*std::pow(x-center.x(),2),0.5)+center.y();
                    // rotate x,y
                    new_x = 0.5*(x-center.x()) - 0.866*(y-center.y()) + center.x();
                    new_y = 0.866*(x-center.x()) + 0.5*(y-center.y()) + center.y();
                    path.lineTo(new_x, new_y);
                }
                // path.moveTo(new_center2.x() - 15*cos(-ang_rad+rot_rad), new_center2.y() + 15*sin(-ang_rad+rot_rad));
                // path.moveTo(ring2_begin.x(), ring2_begin.y());
                path.arcTo(new_center2.x() - 15, new_center2.y() - 15, 30, 30, 180+ang_deg-rot_deg, 180+rot_deg*2);
                for (qreal x = center.x()+18.7237; x >= center.x()-18.7237; x -= 0.01)
                {
                    qreal y = -std::pow(17.7262+0.443155*std::pow(x-center.x(),2),0.5)+center.y();
                    new_x = 0.5*(x-center.x()) - 0.866*(y-center.y()) + center.x();
                    new_y = 0.866*(x-center.x()) + 0.5*(y-center.y()) + center.y();
                    path.lineTo(new_x, new_y);
                }
            }
            else if (slope < 0)
            {
                // qDebug() << "slope < 0";
                path.moveTo(new_center1.x() - 15*cos(ang_rad-rot_rad),new_center1.y() + 15*sin(ang_rad-rot_rad));
                path.arcTo(new_center1.x() - 15, new_center1.y() - 15, 30, 30, 180+ang_deg-rot_deg, 180+rot_deg*2);
                for (qreal x = center.x()-18.7237; x <= center.x()+18.7237; x += 0.01)
                {
                    qreal y = std::pow(17.7262+0.443155*std::pow(x-center.x(),2),0.5)+center.y();
                    // rotate x,y
                    new_x = 0.5*(x-center.x()) + 0.866*(y-center.y()) + center.x();
                    new_y = -0.866*(x-center.x()) + 0.5*(y-center.y()) + center.y();
                    path.lineTo(new_x, new_y);
                }
                // path.moveTo(new_center2.x() + 15*cos(-ang_rad+rot_rad), new_center2.y() + 15*sin(-ang_rad+rot_rad));
                path.arcTo(new_center2.x() - 15, new_center2.y() - 15, 30, 30, ang_deg-rot_deg, 180+rot_deg*2);
                for (qreal x = center.x()+18.7237; x >= center.x()-18.7237; x -= 0.01)
                {
                    qreal y = -std::pow(17.7262+0.443155*std::pow(x-center.x(),2),0.5)+center.y();
                    new_x = 0.5*(x-center.x()) + 0.866*(y-center.y()) + center.x();
                    new_y = -0.866*(x-center.x()) + 0.5*(y-center.y()) + center.y();
                    path.lineTo(new_x, new_y);
                }
            }
            else
            {
                qDebug() << "something wrong";
            }
            // qDebug() << center_to_edge << center_to_edge/2;
            QGraphicsPathItem *bisring = new QGraphicsPathItem(path);
            QPen bispen;
            bispen.setColor(QColor("#d0d0d0"));     //改bisring顏色 #eb0e0e red
            bispen.setWidth(5);
            bisring->setPen(bispen);
            m_bondGroup->addToGroup(bisring);
        }

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

        item->setPos(center_x-(metric.width(num)/2.0), center_y);
        item->setAcceptHoverEvents(false);
        item->setVisible(false);
        m_atomnumbers.insert(atom_it.key(), item);

        QGraphicsEllipseItem* circle = new QGraphicsEllipseItem(center_x-circle_size/2.0, center_y-circle_size/2.0,
                                                                circle_size*2, circle_size*2, this);
        circle->setBrush(QBrush(Qt::SolidPattern));
        circle->setPen(QPen(Qt::black));
        circle->setVisible(false);
        circle->setAcceptHoverEvents(true);
        m_atomItems.insert(atom_it.key(), circle);
    }
}

void GraphModelGraphicsItem::createTag()
{
}

int GraphModelGraphicsItem::getHeight()
{
    return boundingRect().height();
//    return rect().height();
}

int GraphModelGraphicsItem::getWidth()
{
//    return rect().width();
    return boundingRect().width();
}

bool GraphModelGraphicsItem::isHidden()
{
    return m_isHidden;
}

void GraphModelGraphicsItem::setHidden(bool on)
{
    m_isHidden = on;
    setVisible(!m_isHidden);
}

void GraphModelGraphicsItem::unselectBonds()
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

void GraphModelGraphicsItem::selectBond(EdgeModel bond)
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

GraphModel * GraphModelGraphicsItem::getModel()
{
    return m_model;
}

QRectF GraphModelGraphicsItem::boundingRect2()
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

void GraphModelGraphicsItem::updateFactor(const QString &HTMLCode)
{
    m_factor->setHtml(HTMLCode);
    updateItemPositions();
    updateBoundingRect();
}

void GraphModelGraphicsItem::createFactor() // m_factor->setHtml("print tag");
{
    m_factor->setFont(m_font);
    m_factor->setHtml(m_model->getPoly().toHTML2());
}



void GraphModelGraphicsItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    if (!m_model->isDead() && !m_model->isDisconnected() )
    {
        QGraphicsRectItem::contextMenuEvent(event);
        QPoint globalPos = event->screenPos();
        QMenu myMenu;

        QAction *ZZ = new QAction(tr("ZZ"),this);
        if (!m_model->isFinished())
        {
            ZZ = myMenu.addAction("Compute ZZ polynomial...");
        }
//        QAction *debug =  myMenu.addAction("Select for debuging...");
        QAction *export_as = myMenu.addAction("Export structure as...");

        QAction* selectedItem = myMenu.exec(globalPos);
        if (selectedItem == ZZ)
        {
                emit ZZPolynomialRequest(m_model);
        }
        else if (selectedItem == export_as)
        {
            export_structure(this->m_model);
        }
//        else if (selectedItem == debug)
//        {
//            static GraphicsItemDebugDialog dialog;
//            dialog.setItem(this);
//            dialog.show();
//        }
    }
}

void GraphModelGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    if (!m_model->isDead())
    {
        this->setPen(QPen(Qt::NoPen));
    }
}

void GraphModelGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
    if (!m_model->isDead())
    {
        this->setPen(QPen(QColor("lightblue")));
    }
}

void GraphModelGraphicsItem::itemBondSelected(BondItem *bond)
{
    selectBond(bond->getEdgeModel());
}

void GraphModelGraphicsItem::itemBondUnselected(BondItem *)
{
    unselectBonds();
}

void GraphModelGraphicsItem::itemPolynomialChanged(GraphModel *model)
{
    updateFactor(model->getPoly().toHTML2());
}

void GraphModelGraphicsItem::itemStateChanged(GraphModel *)
{
        finalize();
        createContainers();
        createInternels();
}

void GraphModelGraphicsItem::childTagChanged()
{
    updateItemPositions();
    updateBoundingRect();
    emit tagChanged();
}

void GraphModelGraphicsItem::setTagVisible(bool visible)
{
    m_tagVisible = visible;
    updateItemPositions();
    updateBoundingRect();
}

void GraphModelGraphicsItem::setShowTagWhenDisconnected(bool on)
{
    m_showTagWhenDisconnected = on;
    updateItemPositions();
    updateBoundingRect();
}

void GraphModelGraphicsItem::setShowMarker(bool value)
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

bool GraphModelGraphicsItem::isGridRotated()
{
    return m_isRotated;
}

void GraphModelGraphicsItem::reset()
{
    delete m_bondGroup ;
    delete m_factor ;
    delete m_tagItem ;
    delete m_totalGroup;

    createContainers();
    createInternels();
}

void GraphModelGraphicsItem::updateBoundingRect()
{
    if (!m_model->isDead())
    {
        QRectF rect = this->mapRectFromScene(m_bondGroup->mapToScene(m_bondPath).boundingRect());
        if (m_tagItem->isVisible())
        {
            QRectF tagRect = this->mapRectFromItem(m_tagItem, m_tagItem->boundingRect());
            rect = rect.united(tagRect);
        }
        if (m_factor->isVisible())
        {
            QRectF tagRect = this->mapRectFromItem(m_factor, m_factor->boundingRect());
            rect = rect.united(tagRect);
        }
        QRectF final = rect;
        m_totalGroup->moveBy(-final.x(), -final.y());
        this->setRect(0,0,final.width(), final.height());
    }
    else
    {
        this->setRect(0,0,100,100);
    }
}

void GraphModelGraphicsItem::setGridRotated(bool rotate)
{   
    qDebug() << "setGridRotate";
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

void GraphModelGraphicsItem::updateItemPositions()
{
    m_totalGroup->setPos(0,0);
    m_factor->show();

    QRectF rr = this->mapRectFromScene(m_bondGroup->mapToScene(m_bondPath).boundingRect());
    
    if (m_model->isFinished())
    {
        m_tagItem->hide();
        m_factor->setPos(rr.center().x()-m_factor->boundingRect().center().x(),rr.bottom());
        m_factor->show();
    }
    else if (m_model->isDead())
    {
        m_tagItem->hide();
    }
    else
    {   
        if (m_tagVisible)
        {
            if (m_model->getPoly().toHTML2() == "1")
            {
                m_factor->hide();
            }
            if (m_model->isDisconnected())
            {
                if (m_showTagWhenDisconnected)
                {
                    m_tagItem->show();
                }
                else
                {
                    m_tagItem->hide();
                }
            }
            else
            {
                m_tagItem->show();
            }
        }
        else
        {
            m_tagItem->hide();
            m_factor->hide();
        }

        m_tagItem->setPos(rr.center().x()-m_tagItem->boundingRect().center().x(),rr.bottom());
        m_factor->setParentItem(m_tagItem);
        m_factor->setPos(-(m_factor->boundingRect().width()+5),0);       

        if (m_tagItem->boundingRect().width() > rr.width() && m_tagItem->pos().x() < 0)
        {
            m_totalGroup->moveBy(-m_tagItem->pos().x(),0);
        }
    }
}

void GraphModelGraphicsItem::updatePath()
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


bool GraphModelGraphicsItem::isMarkerShowed()
{
    return m_selected_marker->isVisible();
}

void GraphModelGraphicsItem::updateTag()
{
    m_tagItem->setText(m_model->getFullTag());
}

void GraphModelGraphicsItem::setBondSelectable(bool selectable)
{

    for(int i=0; i<m_bonditems.size();++i)
    {
        m_bonditems[i]->setAcceptHoverEvents(selectable);
        m_bonditems[i]->setAcceptedMouseButtons(Qt::NoButton);
    }

}

void GraphModelGraphicsItem::setAtomNumberVisible(bool visible)
{
    for(auto& a:m_atomnumbers)
    {
        a->setVisible(visible);
    }

}

void GraphModelGraphicsItem::clearLink()
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

void GraphModelGraphicsItem::addLink(const QList<QPair<int, int> > &links)
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

QPointF GraphModelGraphicsItem::getMidPoint(const EdgeModel &edge) const
{
    return this->m_edge_bond_mapping[edge]->getMidPoint()+m_bondGroup->pos();
}

QPointF GraphModelGraphicsItem::getStartPoint(const EdgeModel &edge) const
{
    return this->m_edge_bond_mapping[edge]->getStartPoint()+m_bondGroup->pos();
}

QPointF GraphModelGraphicsItem::getEndPoint(const EdgeModel &edge) const
{
    return this->m_edge_bond_mapping[edge]->getEndPoint()+m_bondGroup->pos();
}


QList<QPointF> GraphModelGraphicsItem::getRingPoints(const QList<EdgeModel> &edges) const
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

// void GraphModelGraphicsItem::find_bisring_center()
