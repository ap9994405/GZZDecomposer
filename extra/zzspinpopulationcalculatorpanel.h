#ifndef ZZSpinpopulaitonCALCULATORPANEL_H
#define ZZSpinpopulaitonCALCULATORPANEL_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "graphmodel.h"
#include <QtGui>
#include <QtCore>
#include <QObject>
#include "zzpolynomialcalculator.h"




class GraphModel;
class QPushButton;
class GraphModelGraphicsItem4;
class GraphModelGraphicsItem3;
class ZZSpinpopulaitonCalculatorPanel : public QWidget
{
    Q_OBJECT
public:
    explicit ZZSpinpopulaitonCalculatorPanel(QWidget *parent = 0);
    ~ZZSpinpopulaitonCalculatorPanel();
    void setGraph(GraphModel* graph);




signals:


public slots:
    void exportSVG(QString filename, bool compressed);

private slots:

    void calc2();
    void list();








private:
    GraphModel* m_graph= nullptr;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QPushButton *m_calc2, *m_calc3,*m_calc4;
    QLineF m_originalLine;
    GraphModelGraphicsItem4 *graph_item = nullptr;
    QList<QGraphicsTextItem*> m_textItems;
    QList<QGraphicsEllipseItem*> red_circle, blue_circle,red_circle2,blue_circle2;
    QList<QGraphicsTextItem*> m_textItems2;
    int edgessize;
    int ringsize;
    QList<double>  spin_polynomial_red , spin_polynomial_blue  ;
    double BlueMax ,RedMax, BlueMin ,RedMin;
    int Red_Maxnum,Red_Minnum,Blue_Maxnum,Blue_Minnum,Radom1,Radom2,Radom3;
    QList<QPointF> red_atom_coordinate ,blue_atom_coordinate;
    QPointF point_average;
    QList<int> connect_edges ;
    QString prescentage;
    void clearText() ;
    void clearText2() ;
    void clear_all_things();
    void save_connected_edges() ;


protected:
    virtual void resizeEvent(QResizeEvent *);
    void mouseDoubleClickEvent(QMouseEvent *event) ;
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *e);

};









#endif // ZZAROMATICITYCALCULATORPANEL_H
