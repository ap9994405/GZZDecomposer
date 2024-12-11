#include "bonditem.h"
#include <QPen>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QPoint>
#include "utils.h"
#include "edgemodel.h"

const QString BondItem::selected_color = "#40a1ff";
const QString BondItem::selected_color_grayscale = "#8f8f8f";

BondItem::BondItem(double shift_x, double shift_y, double bondlength, EdgeModel edge, Mode mode, QGraphicsItem *parent):
    QGraphicsLineItem(parent), m_bondlength(bondlength), m_edge(edge), m_mode(mode)
{

    setupDefaults(shift_x,shift_y);
}

void BondItem::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
//    qDebug() << "hoverEnter" ;
    m_state = Hovered;
    updateAppearence();
}

void BondItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
//    qDebug() << "hoverLeave" ;
    if (selected)
    {
        m_state = BondItem::Selected;
    }
    else
    {
        m_state = BondItem::None;
    }
    updateAppearence();
}

void BondItem::setupDefaults(double shift_x, double shift_y)
{
    this->setAcceptHoverEvents(true);
    this->clicked = false;
    this->m_state = None;
    this->selected = false;
    this->m_isDouble = false;

    if (m_mode == BondItem::Grid)
    {
        m_pen.setColor(QColor("#d0d0d0"));  //  ///////////////////////改bond顏色
    }
    else
    {
        m_pen.setColor(Qt::black);
    }
    m_pen.setCapStyle(Qt::RoundCap);
    m_pen.setWidth(width);
    m_pen.setJoinStyle(Qt::MiterJoin);
    this->setPen(m_pen);
    QPointF v1 = vertexXY2XY(m_edge.startPoint(),m_bondlength);
    QPointF v2 = vertexXY2XY(m_edge.endPoint(),m_bondlength);
    this->setLine(v1.x()+shift_x,v1.y()+shift_y,v2.x()+shift_x,v2.y()+shift_y);
    m_originalLine = this->line();
}

void BondItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug() << "mouseDown" ;
    if ( event->button() == Qt::LeftButton )
    {
        this->clicked = true;
    }
    else
    {
        this->clicked = false;
    }
//    qDebug() << m_edge.toString();
}

void BondItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
    if ( this->clicked )
    {
        this->clicked = false;
        setSelection(!this->selected);
        notify();
    }
}

void BondItem::updateAppearence()
{
    //qDebug() << "update" << "(selected:" << selected << ")";

    QPen pen = this->pen();

    if ( m_state == None)
    {
        pen.setColor(m_pen.color());
        if (m_mode == BondItem::Grid)
        {
            this->setZValue(0);
        }
    }
    else
    {
        this->setZValue(5);
        if ( selected && m_state == Selected)
        {
//            pen.setColor("#1e90ff");
            pen.setColor("#40a1ff");

//            pen.setColor("orange");
//            pen.setColor("purple");
        }
        else
        {
            pen.setColor("red");
        }
    }
//    this->setPen(pen);
    if (m_isDouble)
    {
        QLineF line = m_originalLine;
        QLineF nv = line.normalVector();
//        qDebug() << nv;
        nv.setLength(2.5);
        nv.translate(-nv.p1().x(),-nv.p1().y());
//        line.translate(nv.p2());
        this->setLine(line.translated(nv.p2()));
//        qDebug() << nv;
        QListIterator<QGraphicsItem*> it(this->childItems());
        while(it.hasNext())
        {
            delete it.next();
        }
        QGraphicsLineItem *second_bond = new QGraphicsLineItem(this);
        QPen tpen = this->pen();
        tpen.setWidthF(2.5);
        this->setPen(tpen);
        second_bond->setPen(tpen);
        second_bond->setLine(line.translated(-nv.p2().x(),-nv.p2().y()));
    }
    else
    {
        QListIterator<QGraphicsItem*> it(this->childItems());
        while(it.hasNext())
        {
            delete it.next();
        }
        pen.setWidthF(5.0);
        this->setPen(pen);
        this->setLine(m_originalLine);
    }
}

void BondItem::selectBond(bool emitSignal)
{
    if (!isSelected())
    {
        setSelection(true);
        if (emitSignal)
            notify();
    }
}

void BondItem::unselectBond(bool emitSignal)
{
    if (isSelected())
    {
        setSelection(false);
        if (emitSignal)
            notify();
    }
}

void BondItem::setDoubleBond(bool on)
{
    if (m_mode != BondItem::Grid)
        return;
    m_isDouble = on;
    updateAppearence();
}

BondItem::~BondItem()
{
//    qDebug() << "BondItem " << (void*) this << " destoryed";
}

bool BondItem::isSelected()
{
    return selected;
}

EdgeModel BondItem::getEdgeModel()
{
    return m_edge;
}

QPointF BondItem::getMidPoint() const
{
    return (m_originalLine.p1()+m_originalLine.p2())/2.0;
}

QPointF BondItem::getStartPoint() const
{
    return m_originalLine.p1();
}

QPointF BondItem::getEndPoint() const
{
    return m_originalLine.p2();
}

void BondItem::setSelection(bool selected)
{
    this->selected = selected;
    if (selected)
    {
        m_state = BondItem::Selected;
    }
    else
    {
        m_state = BondItem::None;
    }
    updateAppearence();
}

void BondItem::notify()
{
    if (this->selected)
    {
        emit bondSelected(this);
    }
    else
    {
        emit bondUnselected(this);
    }
}

void BondItem::toggleSelection(bool emitSignal)
{
    setSelection(!this->selected);
    if(emitSignal)
    {
        notify();
    }
}
