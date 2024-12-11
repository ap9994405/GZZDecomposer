// This cpp file is for zzpolynomialcalculator

#include "graphmodelgraphicsitem2.h"
#include "graphmodel.h"
#include "bonditem.h"
#include <QtWidgets>
#include <QString>
#include "graphmodelgraphicsitemdelegate.h"
#include <QObject>

#include "graphmodeltag.h"
#include "zzpolynomialcalculator.h"

#include <QGraphicsItem>

const double bondlength = 30.0;
const int tagSize = 40;

GraphModelGraphicsItem2::GraphModelGraphicsItem2(GraphModel *model, QGraphicsItem *parent):QGraphicsRectItem(parent)
{
    this->setAcceptHoverEvents(true);
//    this->setAcceptedMouseButtons(Qt::RightButton | Qt::LeftButton);

    m_tagItem = NULL;
    m_model = model;
    m_isHidden = false;
//    m_delegate = new GraphModelGraphicsItemDelegate(this);
    m_tagItem = NULL;
    m_poly = NULL;


    m_font.setPixelSize(tagSize - 5);
    m_font.setFamily("Times New Roman");

    connect(model,SIGNAL(PolynomialChanged(GraphModel*)), this, SLOT(itemPolynomialChanged(GraphModel*)));

    createInternels();

}

GraphModelGraphicsItem2::~GraphModelGraphicsItem2()
{
//    qDebug() << "GraphModelGraphicsItem::~GraphModelGraphicsItem()";
//    delete m_delegate;
}

void GraphModelGraphicsItem2::createInternels()
{
        this->setPen(QPen(Qt::NoPen));

        QGraphicsItemGroup *g = new QGraphicsItemGroup(this);
        g->setHandlesChildEvents(false);
        m_bonditems.clear();

        const QList<EdgeModel> &edges = m_model->getEdges();
        const QList<EdgeModel> &hidden_edges = m_model->getHiddenEdges();

        for(int i=0; i<edges.size(); ++i)
        {
            BondItem* bond = new BondItem(0,0,bondlength, edges[i], BondItem::Normal);
            m_edge_bond_mapping.insert(edges[i], bond);
            g->addToGroup(bond);
            m_bonditems.append(bond);
        }

        for(int i=0; i<hidden_edges.size(); ++i)
        {
            BondItem* bond = new BondItem(0,0,bondlength, hidden_edges[i], BondItem::Normal);
            m_edge_bond_mapping.insert(hidden_edges[i], bond);
            g->addToGroup(bond);
        }


        QRectF rect = g->boundingRect();
        double x = rect.x();
        double y = rect.y();

        g->moveBy(-x,-y);

        g->moveBy(5,5);

        this->setRect(0,0,g->boundingRect().width()+10, g->boundingRect().height()+10);

        this->setEnabled(false);
}

int GraphModelGraphicsItem2::getHeight()
{
    return boundingRect().height();
}

int GraphModelGraphicsItem2::getWidth()
{
    return boundingRect().width();
}

bool GraphModelGraphicsItem2::isHidden()
{
    return m_isHidden;
}

void GraphModelGraphicsItem2::setHidden(bool on)
{
    m_isHidden = on;
    setVisible(!m_isHidden);
}

void GraphModelGraphicsItem2::unselectBonds()
{
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

void GraphModelGraphicsItem2::selectBond(EdgeModel bond)
{
    unselectBonds();
//    qDebug() << "GraphModelGraphicsItem::selectBond";
    if (m_edge_bond_mapping.contains(bond))
    {
        m_edge_bond_mapping[bond]->setSelection(true);
    }
    m_model->selectBond(bond);
}

GraphModel * GraphModelGraphicsItem2::getModel()
{
    return m_model;
}

QRectF GraphModelGraphicsItem2::boundingRect2()
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

void GraphModelGraphicsItem2::updateFactor(const QString &HTMLCode)
{
    if (m_poly == NULL)
        createFactor();
    else
        m_poly->setHtml(HTMLCode);

}

void GraphModelGraphicsItem2::createFactor()
{
    if (m_poly != NULL)
    {
        delete m_poly;
        m_poly = NULL;
    }
    m_poly = new QGraphicsTextItem(m_tagItem);
    m_poly->setFont(m_font);
    m_poly->setHtml(m_model->getPoly().toHTML());
    m_poly->setPos(-(m_poly->boundingRect().width()+5),0);
}

void GraphModelGraphicsItem2::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    if (!m_model->isDead() && !m_model->isDisconnected() && !m_model->isFinished())
    {
        QGraphicsRectItem::contextMenuEvent(event);
        QPoint globalPos = event->screenPos();
        QMenu myMenu;
        myMenu.addAction("Compute ZZ polynomial...");

        QAction* selectedItem = myMenu.exec(globalPos);
        if (selectedItem)
        {
            emit ZZPolynomialRequest(m_model);
        }        
    }
}

void GraphModelGraphicsItem2::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    if (!m_model->isDead())
    {
        this->setPen(QPen(Qt::NoPen));
    }
}

void GraphModelGraphicsItem2::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
    if (!m_model->isDead())
    {
        this->setPen(QPen(QColor("lightblue")));
    }
}

void GraphModelGraphicsItem2::itemBondSelected(BondItem *bond)
{
    selectBond(bond->getEdgeModel());
}

void GraphModelGraphicsItem2::itemBondUnselected(BondItem *)
{
    unselectBonds();
}

void GraphModelGraphicsItem2::itemPolynomialChanged(GraphModel *model)
{
    updateFactor(model->getPoly().toHTML());
}

void GraphModelGraphicsItem2::setTagVisible(bool visible)
{
    m_tagItem->setVisible(visible);
}



