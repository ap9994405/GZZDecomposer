#ifndef johanna_H
#define johanna_H

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
class johanna : public QWidget
{
    Q_OBJECT
public:
    explicit johanna(QWidget *parent = 0);
    ~johanna();
    void setGraph(GraphModel* graph);
    QVector<QVector<QVector<QVector<int> > > > layer_permu;




signals:


public slots:
    void exportSVG(QString filename, bool compressed);


private slots:

    void W_N();
    void check_zz_can_work();
    void normal_procedure(int layer_number , int fragment , int max_fragemnt_number , QVector<QVector<QVector<QVector<int> > > > reduced_upper , QVector<QVector<QVector<QVector<int> > > > reduced_lower, char layer_type,  QVector<QVector<QVector<int> > >  interface_permu);
    void c_recur(int k,int n,int m,QVector<QVector<int> > list , int a ,int b );
    void combinationUtil(int arr[], int data[], int start, int end,int index, int r);
    void if_lower_zero(int layer_number , int fragment,int max_fragement_number ,int order,int possibility,QVector<QVector<QVector<QVector<int> > > > reduced_upper , QVector<QVector<QVector<QVector<int> > > > reduced_lower,  QVector<QVector<char> >  layer_type,QVector<QVector<QVector<int> > >  interface_permu , int last_layer_permu_size);
    void if_upper_zero(int layer_number , int fragment,int max_fragement_number ,int order,int possibility , QVector<QVector<QVector<QVector<int> > > > reduced_lower, QVector<QVector<char> >  layer_type,QVector<QVector<QVector<int> > >  interface_permu , int last_layer_permu_size);
    bool check_zero(QVector<QVector<QVector<QVector<int> > > > reduced_upper);

    int factorial(int n);
    int check_ZZ_polynomial(QVector<QVector<int> >  possibility_list );










private:
    GraphModel* m_graph= nullptr;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QPushButton *m_calc2, *m_calc3,*m_calc4,*m_calc5;
    QLineF m_originalLine;
    GraphModelGraphicsItem3 *graph_item = nullptr;
    QList<QGraphicsTextItem*> m_textItems;
    QList<QGraphicsEllipseItem*> red_circle, blue_circle,red_circle2,blue_circle2;
    QList<QGraphicsTextItem*> m_textItems2;
    int edgessize;
    int ringsize;
    QList<double>  spin_polynomial_red , spin_polynomial_blue , atom_polynomial  ;
    double BlueMax ,RedMax, BlueMin ,RedMin;
    int Red_Maxnum,Red_Minnum,Blue_Maxnum,Blue_Minnum,Radom1,Radom2,Radom3;
    QList<QPointF> red_atom_coordinate ,blue_atom_coordinate;
    QPointF point_average;
    QList<int> connect_edges ;
    QVector<QVector<int> >  templist  ;
    QString prescentage_red , prescentage_blue;
    QVector<QVector<QVector<int> > > layer ;
    QVector<QVector<QVector<QString> > >  ZZ_polynomial;
    QVector<QVector<QVector<QVector<int> > > > ZZ_polynomial_int  ;
    int layer_order ,  number_of_permu_by_fragment , original_order;
    QVector<QVector<double> > check_layer_type_x , check_layer_type_y ;

    QString temp_zz ;

    QList<int> tempZ_zz_int;

    int possibility;


    int p , check  , resize;


    void clearText() ;
    void clearText2() ;
    void clear_all_things();





protected:
    virtual void resizeEvent(QResizeEvent *);
    void mouseDoubleClickEvent(QMouseEvent *event) ;
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *e);

};









#endif // ZZAROMATICITYCALCULATORPANEL_H
