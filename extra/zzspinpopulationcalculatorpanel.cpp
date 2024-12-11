#include "zzspinpopulationcalculatorpanel.h"
#include "graphmodelgraphicsitem3.h"
#include "graphmodelgraphicsitem4.h"
#include "zoomableview.h"
#include "graphmodel.h"
#include "bonditem.h"

#include <QCoreApplication>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFontMetricsF>
#include "utils.h"
#include "widget.h"
#include <QPainter>
#include <iostream>
#include <fstream>
#include <QFile>
using namespace std;
#include <ostream>
#include <time.h>




#include "symmetryoperators.h"

#include "zzpolynomialcalculator.h"
#include "gzip_helper.h"

#include <QProgressDialog>
#include <QMessageBox>
#include <QtSvg>

inline uint qHash(const QPoint &key)
{
    QString str = QString("(%1,%2)").arg(key.x()).arg(key.y());
    QString hkey = QString(QCryptographicHash::hash(str.toStdString().c_str(),QCryptographicHash::Md5).toHex());
    return qHash(hkey);
}

ZZSpinpopulaitonCalculatorPanel::ZZSpinpopulaitonCalculatorPanel(QWidget *parent) : QWidget(parent) 

{
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setMargin(0);
    scene = new QGraphicsScene(this);

    ZoomableView* viewer = new ZoomableView(scene);
    viewer->setZoomable(true);
    viewer->zoom(1.5);
    view = viewer;
    view->setMouseTracking(true);
    layout->addWidget(view);

    m_calc2 = new QPushButton(tr("Spinpopulation"));
    m_calc3 = new QPushButton(tr("List prescentage"));

    connect(m_calc2, SIGNAL(clicked()), this, SLOT(calc2()));
    connect(m_calc3, SIGNAL(clicked()), this, SLOT(list()));

    QHBoxLayout *layout_h = new QHBoxLayout();

    layout_h->addStretch(1);
    layout_h->addWidget(m_calc2);
    layout_h->addWidget(m_calc3);
    layout_h->addStretch(1);
    layout->addLayout(layout_h);
    layout->addSpacing(10);
    this->setLayout(layout);

}

ZZSpinpopulaitonCalculatorPanel::~ZZSpinpopulaitonCalculatorPanel()
{

}



void ZZSpinpopulaitonCalculatorPanel::setGraph(GraphModel *graph)
{
    clear_all_things();


    m_graph = graph;
    graph_item = new GraphModelGraphicsItem4(m_graph);




//    graph_item->setAtomNumberVisible(true);
    graph_item->setBondSelectable(false);
    graph_item->setTagVisible(false);
//    if (m_rotateGrid)
//    {
//        graph_item->setGridRotated(m_rotateGrid);
//    }

    scene->addItem(graph_item);
    scene->update();
    view->centerOn(graph_item);
    view->update();
    scene->setSceneRect(scene->itemsBoundingRect());


//    save_connected_edges();



}


void ZZSpinpopulaitonCalculatorPanel::exportSVG(QString filename, bool compressed)
{
    QSvgGenerator svgGen;

    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    svgGen.setOutputDevice(&buffer);


    QRectF rect = scene->itemsBoundingRect();
    QGraphicsRectItem *bg=new QGraphicsRectItem(rect.x()-50, rect.y()-50, rect.width()+100, rect.height()+100,0);
    bg->setPen(QPen(Qt::NoPen));
    bg->setBrush(QBrush(QColor("white")));
    bg->setZValue(-50);


;


    scene->addItem(bg);

    QRectF rr = bg->rect();
    svgGen.setTitle("ZZ Aromaticity Export");
//    svgGen.setResolution(300);
    svgGen.setSize(QSize(rr.width(),rr.height()));
    svgGen.setViewBox(rr);

    QPainter painter;
    painter.begin(&svgGen);




    scene->render(&painter,rr,rr);

    painter.end();

    scene->removeItem(bg);
    delete bg;

    QFile file( filename );
    file.open( QIODevice::WriteOnly );
    if (compressed)
    {
        QByteArray compressed = compress(byteArray);
        file.write( compressed );
    }
    else
    {
        file.write( byteArray );
    }
    file.close();

}





void ZZSpinpopulaitonCalculatorPanel::mouseDoubleClickEvent(QMouseEvent *event)
{
    ZZSpinpopulaitonCalculatorPanel::mouseDoubleClickEvent(event);
}


void ZZSpinpopulaitonCalculatorPanel::mouseMoveEvent(QMouseEvent *event)
{
    ZZSpinpopulaitonCalculatorPanel::mouseMoveEvent(event);
}
void ZZSpinpopulaitonCalculatorPanel::mousePressEvent(QMouseEvent *event)
{

  ZZSpinpopulaitonCalculatorPanel::mousePressEvent(event);
}


void ZZSpinpopulaitonCalculatorPanel::paintEvent(QPaintEvent *e)
{
   QPainter painter(this);

   painter.setPen(Qt::green);               //指定畫筆顏色

   painter.setPen(QPen(Qt::red, 5));        //指定畫筆顏色和粗細
   painter.setBrush(Qt::red);              //指定筆刷顏色，可以想成物體的填充色
   painter.drawEllipse(100, 300, 20, 20);//指定x、y、width、height的矩形，繪製橢圓於內

 }



   void ZZSpinpopulaitonCalculatorPanel::calc2()
{

      clearText();
      red_atom_coordinate.clear();
      blue_atom_coordinate.clear();
      spin_polynomial_blue.clear();
      spin_polynomial_red.clear();
      m_textItems.clear();
      red_circle.clear();
      blue_circle.clear();


    QProgressDialog progress("Task in progress...", "Cancel", 0, 2, this);
    progress.setWindowModality(Qt::WindowModal);


    progress.setValue(0);
    progress.show();

    QCoreApplication::processEvents();

    QList<EdgeModel> edges = m_graph ->getAllEdges();

    edgessize = edges.size() ;

    cout << "!!!!!!!!!Original edge size = " << edgessize <<endl ;

    QList<GraphModel*> new_graph ;

    QList<EdgeModel> removed_edges = m_graph->m_hidden_edges;

    QList<int> connect_edges ;

 bool cancelled = false;

 GraphModelGraphicsItem4 *graph_item2 =  new GraphModelGraphicsItem4(m_graph);

  cout << " have " << graph_item2->atom_coordinate.size() << " atoms " << endl;


//for(int i=0 ; i<graph_item2->atom_coordinate.size();i++)
//{
//  cout << "atom " << i << "coordinate = " << graph_item2->atom_coordinate[i].x()<<" " <<graph_item2->atom_coordinate[i].y()<<endl;

//}


  progress.setRange(0,graph_item2->atom_coordinate.size()+red_atom_coordinate.size()-1);


      for(int j=0 ; j<graph_item2->atom_coordinate.size();j++)
      {
              progress.setValue(j);

         for(int k=0;k<edges.size();k++)
         {
             if(
                  graph_item2->atom_coordinate[j] == graph_item2->getStartPoint(edges[k])

                  )
             {

               connect_edges.append(k);

             }

             else if (
                        graph_item2->atom_coordinate[j] == graph_item2->getEndPoint(edges[k])
                      )
             {

               connect_edges.append(k);

             }

         }

      for(int k=0 ;k<connect_edges.size();k++)
      {
               edges.removeAt(connect_edges[connect_edges.size()-k-1]);
      }
            GraphModel* gm_child = new GraphModel(edges,removed_edges,m_graph,GraphModel::Single, 0);
            ZZPolynomialCalculator *workerThread = new ZZPolynomialCalculator(gm_child, this);

             workerThread->serialRun();

            if(workerThread->getTotal().toDouble()>0)
                  {
                     red_atom_coordinate.append(graph_item2->atom_coordinate[j]);

                  }

             edges.clear();

             edges =  m_graph ->getAllEdges();

             connect_edges.clear();
        }

      for(int i=0 ;i<red_atom_coordinate.size();i++)
      {
          spin_polynomial_red.append(0.0);

      }



  for(int i=0 ; i<red_atom_coordinate.size();i++)
  {
      QCoreApplication::processEvents();

      progress.setValue(graph_item2->atom_coordinate.size()+i);

      if (progress.wasCanceled())
          {
            cancelled = true ;
            break;
          }

         for(int k=0;k<edges.size();k++)
         {
             if(   red_atom_coordinate[i] == graph_item2->getStartPoint(edges[k]) )

             {
               connect_edges.append(k);
             }

             else if (  red_atom_coordinate[i]   == graph_item2->getEndPoint(edges[k]) )

             {
               connect_edges.append(k);
             }

         }

      for(int k=0 ;k<connect_edges.size();k++)
      {
               edges.removeAt(connect_edges[connect_edges.size()-k-1]);
      }

            GraphModel* gm_child = new GraphModel(edges,removed_edges,m_graph,GraphModel::Single, 0);
            ZZPolynomialCalculator *workerThread = new ZZPolynomialCalculator(gm_child, this);

//                         GraphModelGraphicsItem3 *graph_item2 =  new GraphModelGraphicsItem3(gm_child); // check
//                         graph_item2->setPos(120*i-440,-120);
//                         scene->addItem(graph_item2);
             workerThread->serialRun();

            if(workerThread->getTotal().toDouble()>0)
                  {
                    spin_polynomial_red[i] += (workerThread->getTotal().toDouble());
                       cout<<"red polynomial  " <<i<< " = " <<spin_polynomial_red[i]<<endl;
//                        cout<<"blue polynomial "<<j <<" = "<<spin_polynomial_blue[j]<<endl;
                  }

             edges.clear();

             edges =  m_graph ->getAllEdges();

             connect_edges.clear();

    }




    double sum = 0.0 ;

    for(int k=0 ; k<spin_polynomial_red.size();k++)   // find sum
    {
       sum += spin_polynomial_red[k];

    }


    if(sum == 0)
    {     QPointF standard_p ;
        standard_p.setX(graph_item2->x());
        standard_p.setY(graph_item2->y());
           QString subTotal = QString("This structure = 0 ");
           QGraphicsTextItem *text = new QGraphicsTextItem(subTotal);
              text ->setDefaultTextColor("red");
              text->setPos(standard_p.x(),standard_p.y()-50);
              scene->addItem(text);
              m_textItems.append(text);
              cout<<"sum= "<< sum << endl ;

    }


  else
  {
        cout<<"sum= "<< sum << endl ;
    for(int k=0 ; k<spin_polynomial_red.size();k++)   // divide sum , get precent
    {
       spin_polynomial_red[k]= spin_polynomial_red[k]/sum ;

    }


    RedMax = 0.0 ;

    for(int k=0 ; k<spin_polynomial_red.size();k++)   // find RedMaxinum number in "all" list
    {
         if(spin_polynomial_red[k]> RedMax)
           {
             RedMax = spin_polynomial_red[k];
            }

    }

    cout << "RedMax = " << RedMax << endl ;

   RedMin = 100.0;

    for(int k=0 ; k<spin_polynomial_red.size();k++)   // find minimum number in "all" list
    {

          if (spin_polynomial_red[k]< RedMin )
          {
             RedMin = spin_polynomial_red[k];
          }

    }

    cout << "RedMin = " << RedMin << endl;


         for(int k=0 ; k<spin_polynomial_red.size();k++)   //  normalize circle size
         {
               spin_polynomial_red[k] =  spin_polynomial_red[k] / RedMax ;

         }





        for(int i=0; i<spin_polynomial_red.size() ; i++)
        {
//               　　　QString subTotal = QString("%1").arg(spin_Polynomial[i]);
//                　　　string str = subTotal.toStdString(); //check
//                　　　cout << "job " << i <<" poly = " << str <<endl ;    // check
//               　　　GraphModelGraphicsItem4 *graph_item2 =  new GraphModelGraphicsItem4(new_graph[i]); // check
//              　　　　QGraphicsTextItem *text = new QGraphicsTextItem(subTotal);
                    // text ->setDefaultTextColor("red");
                    // text->setPos(spin_point[i].x()-7 ,spin_point[i].y()-16 );
                    // graph_item2->setPos(120*i-440,-120);

          double k=25*spin_polynomial_red[i];
          QBrush redBrush(Qt::red);
          QPen redpen(Qt::red);
          red_circle.append(scene->addEllipse(red_atom_coordinate[i].x()-(k-1)/2.0,red_atom_coordinate[i].y()-(k-2)/2.0,k,k,redpen,redBrush));


//       red_circle.append(scene->addEllipse(spin_point[i].x()-(k-1)/2.0,spin_point[i].y()-(k-2)/2.0,k,k,redpen,redBrush));
                //scene->addItem(text);
                //scene ->addItem(graph_item2);
                //  m_textItems.append(text);
       }


//    for(int i=0; i<rings.size();++i)
//    {
//        QList<EdgeModel> edges = rings[i];

//        edgessize = edges.size() ;  //define int edgesize , will be used on erase.

//        for(int j=0; j<edges.size();++j)    //find each edges's midpoint,startpoint,endpoint position
//        {
//            QPointF startpoint = graph_item->getStartPoint(edges[j]);
//            QPointF endpoint = graph_item->getEndPoint(edges[j]);

//            QBrush redBrush(Qt::red);
//            QPen redpen(Qt::red);
//            double k=(rand()%20 )+1;

//            startellipse.append( scene->addEllipse(endpoint.x()-(k-1)/2.0,endpoint.y()-(k-2)/2.0,k,k,redpen,redBrush));
//            endellipse.append( scene->addEllipse(startpoint.x()-(k-1)/2.0,startpoint.y()-(k-2)/2.0,k,k,redpen,redBrush));
//       }
//   }

     }

  }




   void ZZSpinpopulaitonCalculatorPanel::clear_all_things()
   {

       scene->clear();
       red_atom_coordinate.clear();
       blue_atom_coordinate.clear();
       spin_polynomial_blue.clear();
       spin_polynomial_red.clear();
       m_textItems.clear();
       m_textItems2.clear();
       red_circle.clear();
       red_circle2.clear();
       blue_circle.clear();
       blue_circle2.clear();


   }


void ZZSpinpopulaitonCalculatorPanel::clearText()
{

    for(int i=0; i<m_textItems.size();i++)
    {
        scene->removeItem(m_textItems[i]);

    }


    m_textItems.clear();

    for(int i=0;i<red_circle.size();i++)
    {

        scene->removeItem(red_circle[i]);

    }

    for(int i=0;i<blue_circle.size();i++)
    {

        scene->removeItem(blue_circle[i]);

    }

    red_circle.clear();

    blue_circle.clear();
}
void ZZSpinpopulaitonCalculatorPanel::clearText2()
{
    for(int i=0; i<m_textItems2.size();++i)
    {
        scene->removeItem(m_textItems2[i]);
    }
    m_textItems2.clear();


    for(int i=0;i<red_circle2.size();i++)
    {

        scene->removeItem(red_circle2[i]);

    }

    for(int i=0;i<blue_circle2.size();i++)
    {

        scene->removeItem(blue_circle2[i]);

    }

    red_circle2.clear();

    blue_circle2.clear();
}






void ZZSpinpopulaitonCalculatorPanel::resizeEvent(QResizeEvent *)
{
    if (graph_item!=nullptr)
    {
//        view->ensureVisible(graph_item);
        view->centerOn(graph_item);
    }
}

void ZZSpinpopulaitonCalculatorPanel::list()
{


    clearText2();


    QBrush redBrush(Qt::red);
    QPen redpen(Qt::red);
    QPen blackpen(Qt::black);
    GraphModelGraphicsItem4 *graph_item2 =  new GraphModelGraphicsItem4(m_graph);


     QPointF standard_p ;
     standard_p.setX(graph_item2->x());
     standard_p.setY(graph_item2->y());

//     for(int i=0 ; i<6 ; i++)
//     {
//      scene->addLine(standard_p.x()-110 ,standard_p.y()+i*30 ,standard_p.x()-30 ,standard_p.y()+i*30 , blackpen);
//     }

//    scene->addLine(standard_p.x()-110  , standard_p.y() ,  standard_p.x()-110 , standard_p.y()+150 , blackpen);
//    scene->addLine(standard_p.x()-30   , standard_p.y() ,  standard_p.x()-30 , standard_p.y()+150, blackpen);


    srand(time(NULL));// set 3 radom numbers
    Radom1 =  (rand()%spin_polynomial_red.size() );
    Radom2 =  (rand()%spin_polynomial_red.size() );
    Radom3 =  (rand()%spin_polynomial_red.size() );
    cout << Radom1 << " " << Radom2 << " " << Radom3 << endl;
      double mid;
      double  x = max(max(spin_polynomial_red[Radom3],spin_polynomial_red[Radom2]),spin_polynomial_red[Radom1]);
      double  y = min(min(spin_polynomial_red[Radom3],spin_polynomial_red[Radom2]),spin_polynomial_red[Radom1]);
    {

     if(x>=spin_polynomial_red[Radom3]&& spin_polynomial_red[Radom3]>=y )
     {
      mid = spin_polynomial_red[Radom3];
      cout <<"mid= " << mid << endl ;
     }
    else if(x>=spin_polynomial_red[Radom2] && spin_polynomial_red[Radom2]>=y )
     {
       mid = spin_polynomial_red[Radom2];
       cout <<"mid= " << mid << endl ;
     }

    else if(x>=spin_polynomial_red[Radom1] && spin_polynomial_red[Radom1]>=y )
       {
         mid = spin_polynomial_red[Radom1];
         cout <<"mid= " << mid << endl ;
       }

      }

    cout << "Radom_zz1= " << spin_polynomial_red[Radom1] <<endl;
    cout << "Radom_zz2= " << spin_polynomial_red[Radom2] <<endl;
    cout << "Radom_zz3= " << spin_polynomial_red[Radom3] <<endl;

    QList<double> number ;
    number.append( RedMax*100    );
    number.append( x*100*RedMax  );
    number.append( mid*100*RedMax);
    number.append( y*100*RedMax  );
    number.append( RedMin*100    );

    QFont font;
    font.setPixelSize(12.0);

           for (int i=0 ; i<5;i++)
              {
               if(number[i]<1 && number[i]!=0 )
               {
                   prescentage = QString("<1%");
               }

               else
               {
                  prescentage = QString("%1%").arg(int(number[i]));

               }
                    QGraphicsTextItem *text = new QGraphicsTextItem(prescentage);
                    text->setFont(font);
                    text->setDefaultTextColor("blue");
                    text->setPos(standard_p.x()-68,standard_p.y()+12+30*i);
                    scene -> addItem(text);
                    m_textItems2.append(text);
            }

      QString Max_prescentage = QString("Max");
      QString Min_prescentage = QString("Min");
      QGraphicsTextItem *text_max = new QGraphicsTextItem(Max_prescentage);
      QGraphicsTextItem *text_min = new QGraphicsTextItem(Min_prescentage);
      text_max->setFont(font);
      text_min->setFont(font);
      text_max->setDefaultTextColor("green");
      text_min->setDefaultTextColor("green");
      text_max->setPos(standard_p.x()-68,standard_p.y());
      text_min->setPos(standard_p.x()-68,standard_p.y()+120);
      scene -> addItem(text_max);
      scene -> addItem(text_min);
      m_textItems2.append(text_max);
      m_textItems2.append(text_min);



cout << spin_polynomial_red[Radom3]*RedMax << " " << spin_polynomial_red[Radom2]*RedMax <<" " <<spin_polynomial_red[Radom1]*RedMax << endl;


                   double k1 = 25;
                   double k2 = 25*x   ;
                   double k3 = 25*mid ;
                   double k4 = 25*y   ;
                   double k5 = 25*RedMin/RedMax;

                   red_circle2.append(scene->addEllipse(graph_item2->x()-90-(k1)/2,graph_item2->y()+15 -(k1/2)  ,k1,k1,redpen,redBrush));
                   red_circle2.append(scene->addEllipse(graph_item2->x()-90-(k2)/2,graph_item2->y()+45 -(k2/2)  ,k2,k2,redpen,redBrush));
                   red_circle2.append(scene->addEllipse(graph_item2->x()-90-(k3)/2,graph_item2->y()+75-(k3/2)  ,k3,k3,redpen,redBrush));
                   red_circle2.append(scene->addEllipse(graph_item2->x()-90-(k4)/2,graph_item2->y()+105-(k4/2)  ,k4,k4,redpen,redBrush));
                   red_circle2.append(scene->addEllipse(graph_item2->x()-90-(k5)/2,graph_item2->y()+135-(k5/2)  ,k5,k5,redpen,redBrush));




//            for (int k=0 ; k<3 ; k++)
//            {
//                double random =  (rand()%startellipse.size() )+1;
//                QString prescentage = QString("%1%").arg();


//            }








//        for(int j=0; j<startellipse.size();++j)
//          {
//              scene->  removeItem(startellipse[j]);
//              scene -> removeItem(endellipse[j]);
//          }

//     startellipse.clear();
//


}



//void ZZSpinpopulaitonCalculatorPanel::save_connected_edges()
//{
//    clearText();

//    QList<EdgeModel> edges = m_graph ->getAllEdges();

//    QList<EdgeModel> removed_edges = m_graph->m_hidden_edges;

//    QList<int> connect_edges ;


//    GraphModelGraphicsItem4 *graph_item2 =  new GraphModelGraphicsItem4(m_graph);

//        for(int j=0 ; j<graph_item2->atom_coordinate.size();j++)
//        {
//           for(int k=0;k<edges.size();k++)
//           {
//               if(
//                    graph_item2->atom_coordinate[j] == graph_item2->getStartPoint(edges[k])

//                    )
//               {

//                 connect_edges.append(k);

//               }

//               else if (
//                          graph_item2->atom_coordinate[j] == graph_item2->getEndPoint(edges[k])
//                        )
//               {

//                 connect_edges.append(k);

//               }

//           }

//        for(int k=0 ;k<connect_edges.size();k++)
//        {
//                 edges.removeAt(connect_edges[connect_edges.size()-k-1]);
//        }
//              GraphModel* gm_child = new GraphModel(edges,removed_edges,m_graph,GraphModel::Single, 0);
//              ZZPolynomialCalculator *workerThread = new ZZPolynomialCalculator(gm_child, this);

//               workerThread->serialRun();

//              if(workerThread->getTotal().toDouble()>0)
//                    {
//                       red_atom_coordinate.append(graph_item2->atom_coordinate[j]);

//                    }

//               edges.clear();

//               edges =  m_graph ->getAllEdges();

//               connect_edges.clear();
//          }

//        for(int i=0 ;i<red_atom_coordinate.size();i++)
//        {
//            spin_polynomial_red.append(0.0);

//        }

//}
