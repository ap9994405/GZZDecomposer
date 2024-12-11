#ifndef BONDITEM_H
#define BONDITEM_H

#include <QGraphicsLineItem>
#include "edgemodel.h"
#include <QPen>
#include <QLineF>

class BondItem : public QObject, public QGraphicsLineItem
{
    Q_OBJECT
public:
    enum State
    {
        None, Selected, Hovered
    };
    enum Mode
    {
        Normal, Grid
    };
    BondItem(double shift_x, double shift_y, double bondlength, EdgeModel edge, Mode mode, QGraphicsItem *parent = 0);

    static const QString selected_color;
    static const QString selected_color_grayscale;

public slots:
    void setSelection(bool selected);
    void toggleSelection(bool emitSignal = true);
    void selectBond(bool emitSignal = false);
    void unselectBond(bool emitSignal = false);
    void setDoubleBond(bool on);


protected:
    double m_bondlength;
    EdgeModel m_edge;
    Mode m_mode;
    State m_state;
    QPen m_pen;
    bool m_isDouble;

public:
    const int width = 5;
    bool isSelected();
    EdgeModel getEdgeModel();
    QPointF getMidPoint() const;
    QPointF getStartPoint() const;
    QPointF getEndPoint() const;
    ~BondItem();
private:
    bool clicked;
    bool selected;
    QLineF m_originalLine;
private:
    void setupDefaults(double shift_x, double shift_y);
    void notify();
private slots:
    void updateAppearence();
protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
signals:
    void bondSelected(BondItem*);
    void bondUnselected(BondItem*);
};

#endif // BONDITEM_H
