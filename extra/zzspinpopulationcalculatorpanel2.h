#ifndef ZZSpinpopulaitonCALCULATORPANEL2_H
#define ZZSpinpopulaitonCALCULATORPANEL2_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "graphmodel.h"
#include <QtGui>
#include <QtCore>
#include <QObject>



class GraphModel;
class QPushButton;
class GraphModelGraphicsItem3;
class GraphModelGraphicsItem4;
class ZZSpinpopulaitonCalculatorPanel2 : public QWidget
{
    Q_OBJECT
public:
    explicit ZZSpinpopulaitonCalculatorPanel2(QWidget *parent = 0);
    ~ZZSpinpopulaitonCalculatorPanel2();
    void setGraph(GraphModel* graph);
    int original_atom_number;





signals:


public slots:
    void exportSVG(QString filename, bool compressed);


private slots:

    void calc2();
    void list();
     void check();







private:
    GraphModel* m_graph= nullptr;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QPushButton *m_calc2, *m_calc3,*m_calc4;
    QLineF m_originalLine;
    GraphModelGraphicsItem3 *graph_item = nullptr;
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
    QString prescentage_red , prescentage_blue;
    bool equal;


    void clearText() ;
    void clearText2();
    void clear_all_things();
    void save_atom_coordinate() ;
    void run_number_no_equal();
    void define_red_blue_atom();



protected:
    virtual void resizeEvent(QResizeEvent *);
    void mouseDoubleClickEvent(QMouseEvent *event) ;
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *e);

};









#endif // ZZAROMATICITYCALCULATORPANEL2_H
