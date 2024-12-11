#include "johanna.h"
#include "graphmodelgraphicsitem3.h"
#include "zoomableview.h"
#include "graphmodel.h"
#include "bonditem.h"
#include <stdio.h>
#include "interface_calculation.h"

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
#include <neightborlist.h>
#include <cmath>
#include "interface_calculation.h"
#include "zzpolynomialcalculator.h"





#include "symmetryoperators.h"

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

johanna::johanna(QWidget *parent) : QWidget(parent)

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


    m_calc3 = new QPushButton(tr("Johanna"));





     connect(m_calc3, SIGNAL(clicked()), this, SLOT(check_zz_can_work()));



    QHBoxLayout *layout_h = new QHBoxLayout();


    layout_h->addStretch(1);

    layout_h->addWidget(m_calc3);


    layout_h->addStretch(1);

    layout->addLayout(layout_h);
    layout->addSpacing(10);
    this->setLayout(layout);




}

johanna::~johanna()
{

}



void johanna::setGraph(GraphModel *graph)
{
    clear_all_things();


    m_graph = graph;
    graph_item = new GraphModelGraphicsItem3(m_graph);




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

}


void johanna::check_zz_can_work()
{

    GraphModelGraphicsItem3 *graph_item2 =  new GraphModelGraphicsItem3(m_graph);

    QList<EdgeModel> edges = m_graph ->getAllEdges();

    edgessize = edges.size() ;

    cout << "!!!!!!!!!Original edge size = " << edgessize <<endl ;

    QList<GraphModel*> new_graph ;

    QList<EdgeModel> removed_edges = m_graph->m_hidden_edges;

    QList<int> connect_edges ;

    QPointF standard_p ;
    QBrush redBrush(Qt::red);
    QPen redpen(Qt::red);
    QBrush blueBrush(Qt::blue);
    QPen bluepen(Qt::blue);
    QPen blackpen(Qt::white);
    QFont font;
    font.setPixelSize(12.0);
    standard_p.setX(graph_item2->x());
    standard_p.setY(graph_item2->y());

    GraphModel* gm_child = new GraphModel(edges,removed_edges,m_graph,GraphModel::Single, 0);
    ZZPolynomialCalculator *workerThread = new ZZPolynomialCalculator(gm_child, this);

     workerThread->serialRun();

    if(workerThread->getTotal().toDouble()==0)
          {
        QString x = QString("ZZ Polynomial = 0 ");
        QGraphicsTextItem *text = new QGraphicsTextItem(x);
        text->setFont(font);
        text->setDefaultTextColor("blue");
        text->setPos(standard_p.x()-20,standard_p.y()-50);
        scene -> addItem(text);
        m_textItems2.append(text);

          }

    else
    {

        W_N();

    }




}


void johanna::W_N()
{

 double x ;
  cout << pow(x,2) << endl;

    layer.clear();
    layer_permu.clear();
    m_textItems.clear();
    ZZ_polynomial.clear();
    ZZ_polynomial_int.clear();
    check_layer_type_x.clear();
    check_layer_type_y.clear();









  GraphModelGraphicsItem3 *graph_item2 =  new GraphModelGraphicsItem3(m_graph);



    QBrush redBrush(Qt::red);
    QPen redpen(Qt::red);
    QBrush blueBrush(Qt::blue);
    QPen bluepen(Qt::blue);
    QPen blackpen(Qt::white);
    QFont font;
    font.setPixelSize(12.0);
    QPointF standard_p ;
    standard_p.setX(graph_item2->x());
    standard_p.setY(graph_item2->y());

   QList<EdgeModel> edges = m_graph ->getAllEdges();
   QList<EdgeModel> removed_edges = m_graph->m_hidden_edges;
   QList<int> connect_edges ;
   NeightborList *neighbor = new NeightborList(edges,removed_edges);

for(int i=0 ; i < neighbor->m_neighborlist.size() ; i++)
{
      cout << "i = "<<  neighbor->m_neighborlist[i].size() << endl;
}


//   for(int i=0 ; i<edges.size();i++)
//   {

//       QString s = edges[i].toString();
//       cout << "edge " << i << " = "  << s.toStdString() << endl;

//   }



//   scene->addEllipse(standard_p.rx()-25/2,standard_p.ry()-(25/2)  ,25,25,bluepen,blueBrush);

//   cout <<"standard x = " <<  standard_p.rx() << "standard y =" << standard_p.ry() << endl;
   QList<double> y_coordinate ;
   QList<double> x_coordinate ;
   double temp ;
//   QMap<int, int > interface_bond;
   QList<QPointF> interface_bond;  // save atom's coor(by QPointF) on interface


   for(int i=0;i<graph_item2->atom_coordinate.size();i++)                  // arrange y from small to big
      {
       for(int j=0; j<graph_item2->atom_coordinate.size()-1; j++ )
        {     if(graph_item2->atom_coordinate[j].ry() > graph_item2->atom_coordinate[j+1].ry())
            {
               double tmp_y =graph_item2->atom_coordinate[j].ry();
               double tmp_x =graph_item2->atom_coordinate[j].rx();
               graph_item2->atom_coordinate[j].ry()=graph_item2->atom_coordinate[j+1].ry();
               graph_item2->atom_coordinate[j+1].ry() = tmp_y ;

               graph_item2->atom_coordinate[j].rx()=graph_item2->atom_coordinate[j+1].rx();
               graph_item2->atom_coordinate[j+1].rx() = tmp_x ;
             }
         }
       }







   for (int i=0 ; i<graph_item2->atom_coordinate.size();i++)      // save y and x coordinate
   {
       x_coordinate.append(graph_item2->atom_coordinate[i].rx());
       y_coordinate.append(graph_item2->atom_coordinate[i].ry());
       QString x = QString("%1").arg(graph_item2->atom_coordinate[i].rx());
       QString y = QString("%1").arg(graph_item2->atom_coordinate[i].ry());
      cout << "atom " << i+1 << " = " << x.toStdString() << "  " << y.toStdString() << endl;




       for(int j=0 ;j<i;j++)                  // save interface bonds ( atom coor at start point and end point )
       {
           if(graph_item2->atom_coordinate[i].rx() == graph_item2->atom_coordinate[j].rx() )
            {
               if(abs(graph_item2->atom_coordinate[i].ry() - graph_item2->atom_coordinate[j].ry()) == 30)
             {
                 interface_bond.append(graph_item2->atom_coordinate[i]);
                 interface_bond.append(graph_item2->atom_coordinate[j]);

             }
            }
       }

   }

    cout << "interface has " << interface_bond.size()/2 << " bonds " <<endl;

    QVector<QVector<double> > bond;   // save all atom's coor(by atom1,x  atom2,x  atom1,y atom2,y) on interface
    bond.resize(interface_bond.size()/2);

   for(int i=0 ; i<bond.size();i++)
    {
        bond[i].append(interface_bond[2*i].rx());                // start point x
        bond[i].append(interface_bond[2*i+1].rx());              // end point x
        bond[i].append(interface_bond[2*i].ry());                // start point y
        bond[i].append(interface_bond[2*i+1].ry());              // end point y

    }

   for(int i=0;i<y_coordinate.size();i++)                  // arrange y from small to big
      {
       for(int j=0; j<y_coordinate.size()-1; j++ )
        {     if(y_coordinate[j] > y_coordinate[j+1])
            {
               double tmp=y_coordinate[j];
               y_coordinate[j]=y_coordinate[j+1];
               y_coordinate[j+1] = tmp ;
             }
         }
       }

   for(int i=0;i<x_coordinate.size();i++)                  // arrange x from small to big
      {
       for(int j=0; j<x_coordinate.size()-1; j++ )
        {     if(x_coordinate[j] > x_coordinate[j+1])
            {
               double tmp=x_coordinate[j];
               x_coordinate[j] = x_coordinate[j+1];
               x_coordinate[j+1] = tmp ;
             }
         }
       }



   QList<double> value_y ;
   value_y.append(y_coordinate[0]);

   for (int i=0 ; i<y_coordinate.size()-1;i++)   // save value in y coordinate
   {
       if(y_coordinate[i] != y_coordinate[i+1])  // delete the same value of y
       {
           value_y.append(y_coordinate[i+1]);
       }
   }


   QList<double> value_x ;
   value_x.append(x_coordinate[0]);

   for (int i=0 ; i<x_coordinate.size()-1;i++)   // save value in x coordinate
   {
       if(x_coordinate[i] != x_coordinate[i+1])  // delete the same value of x
       {
           value_x.append(x_coordinate[i+1]);
       }
   }





   QList<double> position;      // save the position (arranged by order of x coordinate)
//   position.resize(value_x.size());
   for (int i=0 ; i<value_x.size();i++)
   {
      position.append(value_x[i]);
      cout << " pos " << i+1 << " = " << value_x[i] << endl;

   }
     cout << " position size = " << position.size() <<endl;







     QVector<QVector<QVector<int> > > count ;          // count =  atom numbers on each layer
     
     
 QVector<QVector<double> > layer_start_x_coor; 



// QVector<QVector<double> > lower_x_coor;
      
 layer_start_x_coor.resize(value_y.size()/2);
 
 check_layer_type_x.resize(value_y.size()/2);

 check_layer_type_y.resize(value_y.size()/2);
 
 //lower_x_coor.resize(value_y.size()/2);
     count.resize(value_y.size()/2);

      for(int k =0 ; k<value_y.size();k+=2)     // count how many times that value_y exist ( count how many atom exist on each layer)
      {
      	
         //check_layer_type_x.clear();
      	
      	  int fragment_num=0;

          cout << " now at layer " << k/2+1 << endl;
      	  
      	 
      	
          count[k/2].resize(fragment_num+1);
          count[k/2][0].append(1);

          cout << " count " << k/2 <<  " resize to " << fragment_num+1 << endl;


           for(int j=0 ; j<graph_item2->atom_coordinate.size();j++)
            {
               if ( graph_item2->atom_coordinate[j].ry() == value_y[k]  )
              {
                             
                cout << "  y coor   =  value_y "  << " k = " << k<< "  j = " << j << " coor = " <<graph_item2->atom_coordinate[j].ry() <<  endl;
            
                check_layer_type_x[k/2].append(graph_item2->atom_coordinate[j].rx());  // add all the x coor on layer k
                check_layer_type_y[k/2].append(graph_item2->atom_coordinate[j].ry());  // add all the x coor on layer k

                cout << " x coor append ok!" << endl;
                



                for(int a=0;a< check_layer_type_x[k/2].size();a++)                  // arrange x from small to big
                   {
                    for(int b=0; b< check_layer_type_x[k/2].size()-1; b++ )
                     {     if( check_layer_type_x[k/2][b] >  check_layer_type_x[k/2][b+1])
                         {
                            double tmp= check_layer_type_x[k/2][b];
                            double tmpy= check_layer_type_y[k/2][b];
                             check_layer_type_x[k/2][b]= check_layer_type_x[k/2][b+1];
                             check_layer_type_y[k/2][b]= check_layer_type_y[k/2][b+1];
                             check_layer_type_x[k/2][b+1] = tmp ;
                             check_layer_type_y[k/2][b+1] = tmpy ;
                          }
                      }
                    }



              }
              
              
              if(graph_item2->atom_coordinate[j].ry() == value_y[k+1])
              
              {
                 cout << "  y coor   =  value_y "  << " k = " << k+1 << "  j = " << j<<" coor = " <<graph_item2->atom_coordinate[j].ry() <<  endl;
              	 
                 check_layer_type_x[k/2].append(graph_item2->atom_coordinate[j].rx());  // add all the x coor on layer k
                  check_layer_type_y[k/2].append(graph_item2->atom_coordinate[j].ry());  // add all the y coor on layer k
              	 


                  for(int a=0;a< check_layer_type_x[k/2].size();a++)                  // arrange x from small to big
                     {
                      for(int b=0; b< check_layer_type_x[k/2].size()-1; b++ )
                       {     if( check_layer_type_x[k/2][b] >  check_layer_type_x[k/2][b+1])
                           {
                              double tmp= check_layer_type_x[k/2][b];
                              double tmpy= check_layer_type_y[k/2][b];
                               check_layer_type_x[k/2][b]= check_layer_type_x[k/2][b+1];
                               check_layer_type_y[k/2][b]= check_layer_type_y[k/2][b+1];
                               check_layer_type_x[k/2][b+1] = tmp ;
                               check_layer_type_y[k/2][b+1] = tmpy ;
                            }
                        }
                      }
              	
              	
			  }
            }
            
//           for(int i=0 ; i <check_layer_type_x[k/2].size();i++)
//           {
//             cout<< " layer " << k/2+1 << "x coor =  " << check_layer_type_x[k/2][i]<<endl;

//             cout << " layer " << k/2+1 <<" y coor  = " << check_layer_type_y[k/2][i]<<endl;

//           }

            
          //  int fragment_start_at = 0 ;            // k/2 == now at layer 
            
            layer_start_x_coor[k/2].append(check_layer_type_x[k/2][1]); // layer k/2  first x_coor
            
            cout << " layer " << k/2+1 << " fragment " << fragment_num+1 << "  x coordinate start at " << check_layer_type_x[k/2][0] << endl;



          //  count[k/2][fragment_num].append(0);
            
            for(int i=0 ; i <check_layer_type_x[k/2].size()-1;i++)    // check how many fragment?     i+2 = number of points
            {       


                QPointF P1,P2;
                P1.setX(check_layer_type_x[k/2][i]);
                P2.setX(check_layer_type_x[k/2][i+1]);
                P1.setY(check_layer_type_y[k/2][i]);
                P2.setY(check_layer_type_y[k/2][i+1]);
                bool split = true;


                for(int b=0;b<edges.size();b++)
                {

                    if(     (  (graph_item2->getStartPoint(edges[b]) == P1) &&   (graph_item2->getEndPoint(edges[b]) == P2) )   ||
                            (  (graph_item2->getStartPoint(edges[b]) == P2) &&   (graph_item2->getEndPoint(edges[b]) == P1) ))
                    {

                        split = false;

                    }

                }




             
              if(split==true )  // if   split
              {
              	
              	cout << "have fragment split" << endl;

                fragment_num ++ ;    // go to the next fragment

                count[k/2].resize(fragment_num+1);

                cout << " count " << k/2 <<  " resize to " << fragment_num+1 << endl;


                 count[k/2][fragment_num].append(1);
					       				                                	
                cout << " layer " << k/2+1 << " fragment " << fragment_num+1 <<  " number of x_coordinate  = " << i+2 << endl;
              	                                               	             	
                layer_start_x_coor[k/2].append(check_layer_type_x[k/2][i+2]);   //  next fragment start at     check_layer_type_x[k/2][i+1]
              	
                cout << "layer " << k/2+1 << " fragment " << fragment_num+1 << "  x coordinate start at " << check_layer_type_x[k/2][i+1] << endl;

              	
			  }
			  
              if( split == false)
			  {

                   count[k/2][fragment_num][0]++;



//			     if( i == check_layer_type_x[k/2].size()-2)   // if at the lowest layer
//				 	{
					  
//                      if( fragment_num != 0)  // if more than one fragment
					  
//                      { int  summerize_all_point =0;

//                          for(int c=0;c<fragment_num;c++)
//                          {

//                            summerize_all_point+=count[k/2][c][0];

//                             cout<< " all = " << summerize_all_point << endl;
//                          }


//                            count[k/2][fragment_num].append(   i+2 -   summerize_all_point      );
					       	
//                            cout << "layer " << k/2+1 << " fragment " << fragment_num << "  has " << i+2 -  summerize_all_point  << " points " << endl;
//					  }
					  
//					   else   // if only has one fragment
//					   {
						 
//			                 count[k/2][fragment_num].append(i+2);
			                 
//                             cout << "layer " << k/2+1 << " fragment " << fragment_num+1 << "  has " << i+2   << " points " << endl;
			        
//			         	}
//					}


//                 else
//                 {
//                     count[k/2][fragment_num]+=;

//                     cout << "layer " << k/2+1 << " fragment " << fragment_num+1 << "  has " << i+2   << " points " << endl;


//                 }
			  }
                        
           }
      }

cout << "count size = " << count.size() << endl ;


 QVector<QVector<char> > layer_type;
 
// QVector<QVector<int> > number_of_type_split_temp;
 
 
 layer_type.resize(value_y.size()/2);
 
// number_of_type_temp.resize(value_y.size()/2);

 
 
 

for(int i=0; i<count.size();i++)
{
	
    for(int j=0; j<count[i].size();j++)
{
  cout << " count  layer " << i+1 << " fragment " << j+1 << " = " << count[i][j][0] <<endl ;
}

}






      // QVector<QVector<int> > order;

       //order.resize(value_y.size()/2);

  QList<int> order;
      
      
      for(int i=0 ; i<layer_type.size();i++) // initialize each layer to order 0
      {
      	
        order.append(0);
	  }
     

      int total_value = 0 ;

cout << "~~~~~~~~~~~~~~" <<endl;

for( int j=0 ; j<count.size();j++) // define N , W , L , R    // layer j
{

          for(int i=0 ; i<count[j].size(); i++)          // fragment i
          {

              cout <<  " now at layer " << j+1 << " fragment " << i+1 << " number of point =  " << count[j][i][0] << endl;

              if(count[j][i][0]%2 == 1)    // N or W
              {

                  cout << " n or w "<< endl;

                  for(int k=0 ; k<graph_item2->atom_coordinate.size();k++)
                  {
                      if( (layer_start_x_coor[j][i]) == graph_item2->atom_coordinate[k].rx())
                      {



                          if(graph_item2->atom_coordinate[k].ry() == value_y[j*2])
                          {
                              cout << " W !! " << endl;

                              layer_type[j].append('W');
                              // number_of_type_temp.append(abs(count[j+1] - count[j]));
                              QString x = QString("W");
                              QGraphicsTextItem *text = new QGraphicsTextItem(x);
                              text->setFont(font);
                              text->setDefaultTextColor("blue");
                              text->setPos(standard_p.x()-50+20*i,value_y[j]);
                              scene -> addItem(text);
                              m_textItems2.append(text);


                              order[j]+=1;
                              total_value += 1;

                          }

                          if(graph_item2->atom_coordinate[k].ry() == value_y[j*2+1])
                          {
                               cout << " N !! " << endl;

                              layer_type[j].append('N');   // layer j append
                             // number_of_type_split_temp[j].append(abs(count[j+1][i] - count[j][i]));

                              QString x = QString("N");
                              QGraphicsTextItem *text = new QGraphicsTextItem(x);
                              text->setFont(font);
                              text->setDefaultTextColor("blue");
                              text->setPos(standard_p.x()-50+20*i,value_y[j]);
                              scene -> addItem(text);
                              m_textItems2.append(text);

                              order[j] += (-1);
                              total_value += (-1);

                          }





                      }



                  }



              }

              else if(count[j][i][0]%2 == 0)  //  R or L
              {
                  for(int k=0 ; k<graph_item2->atom_coordinate.size();k++)
                  {
                      if( (layer_start_x_coor[j][i]) == graph_item2->atom_coordinate[k].rx())
                      {
                          if(graph_item2->atom_coordinate[k].ry() == value_y[j*2])
                          {

                               cout << " L !! " << endl;
                              layer_type[j].append('L');
                              QString x = QString("L");
                              // number_of_type_temp.append(1);
                              QGraphicsTextItem *text = new QGraphicsTextItem(x);
                              text->setFont(font);
                              text->setDefaultTextColor("blue");
                              text->setPos(standard_p.x()-50+20*i,value_y[j]);
                              scene -> addItem(text);
                              m_textItems2.append(text);
                          }

                          if(graph_item2->atom_coordinate[k].ry() == value_y[j*2+1])
                          {

                               cout << " R !! " << endl;

                              layer_type[j].append('R');
                          //  number_of_type_temp.append(1);
                            QString x = QString("R");
                            QGraphicsTextItem *text = new QGraphicsTextItem(x);
                            text->setFont(font);
                            text->setDefaultTextColor("blue");
                            text->setPos(standard_p.x()-50+20*i,value_y[j]);
                            scene -> addItem(text);
                            m_textItems2.append(text);

                          }





                      }



                  }




                            // upper_x_coor.clear() ;
                            // lower_x_coor.clear() ;




              }


          }
          
          
     }

          cout << "total_value = " << total_value << endl;
          cout << "order size= " << order.size() << endl;

          for(int i=0; i<order.size()-1;i++)
          {
                  order[i+1] += order[i];

          }

          for(int i=0 ; i<order.size();i++)
          {

              cout << "order " << i+1 << " = " << order[i] <<endl;

          }





        QVector<QVector<double> >  layer_ycoor;





        Interface_calculation *data = new Interface_calculation[order.size()] ;  //declare the class for each layer

        ZZ_polynomial.resize(order.size());
        ZZ_polynomial_int.resize(order.size());



        for(int i=0 ; i<layer_type.size();i++)   // add N,W,R,L to each interface
        {
            data[i].layer_type.resize(layer_type[i].size());

            for(int j=0 ; j<layer_type[i].size();j++)   // add N,W,R,L to each interface
            {

            data[i].layer_type[j].append(layer_type[i][j]);
            cout << " layer " << i+1 << " type_add " << layer_type[i][j] <<endl;

            }
        }




     //   for(int i=0 ; i<number_of_type_temp.size();i++)
       // {
         //     data[i].number_of_type.append(number_of_type_temp[i]);
           //   cout << "layer " << i << " has " <<   data[i].number_of_type[0] <<  data[i].layer_type[0] << endl;

        //}

         for(int i=0 ; i<order.size() ;i++)
         {
           data[i].order.append(order[i]);    // add order to each interface

           cout << "layer " << i << " has order " << data[i].order[0] << endl;
        }






         layer.resize(order.size()-1);
         layer_ycoor.resize(order.size()-1);

         int k=0;           // save the pos on each interface bond (ex. layer1 has 1.3.5.7)
         int number_of_interface = 0 ;



          for(int i=0 ; i<bond.size();i++)
            {

        cout << " now at bond " << i+1 <<endl;
        cout << " x = " << bond[i][0] << " and " << bond[i][1] << endl;
        cout << " y = " << bond[i][2] << " and " << bond[i][3] << endl;


              for( int l=0 ; l<position.size();l++)
                {

                  if ( (bond[i][0] == position[l]) )    // if that bond's x = layer's x (一個 interface bond的x 只有一個)

                  {

                      cout << " bond " << i+1 << " x  at pos " << l+1 << endl;

                      if( i != 0 )
                      {

                       if( (i) == (bond.size()-1))  // if at the lowest layer
                       {

                           if( ((bond[i][2] == bond[i-1][2]  ) && (bond[i][3] == bond[i-1][3] )) ||   // if they are in the same layer
                               ((bond[i][2] == bond[i-1][3]  ) && (bond[i][3] == bond[i-1][2] )) )
                           {

                           }

                           else
                           {
                               cout << " lowest layer not at the smae layer "<< endl;
                               k++;  // they are not in the same layer , so k++ go to the next layer
                              number_of_interface = 0 ; //Go to next layer , start from number 1 ;

                           }

                       }

                       else // if not at the lowest layer
                       {

                       if( ((bond[i][2] == bond[i-1][2]  ) && (bond[i][3] == bond[i-1][3] )) ||   // if they are in the same layer
                           ((bond[i][2] == bond[i-1][3]  ) && (bond[i][3] == bond[i-1][2] )) )
                       {
                               cout << " at same layer " <<endl;
                       }
                       else
                       {
                           cout << " not at same layer " << " bond " << i+1 << " y = " << bond[i][2] << " and " << bond[i][3] << endl;
                           cout << " not at same layer " << " bond " << i+2 << " y = " << bond[i-1][2] << " and " << bond[i-1][3] << endl;

                           k++;  // they are not in the same layer , so k++ go to the next layer
                          number_of_interface = 0 ; //Go to next layer , start from number 1 ;
                       }
                     }


                        layer[k].resize(number_of_interface+1);
                        layer[k][number_of_interface].append(l+1); // l starts from 0 , but we need to save pos from 1, so set append(l+1).
                        cout << " layer " << k+1 << " number " << number_of_interface+1 << " append " << l+1 <<endl;
                         data[k].atom_coordinate_x.append(bond[i][0]);
                        number_of_interface += 1;  // go to next number ;

                        if(bond[i][2]>bond[i][3]) // start y 在 end y的下面 ?
                        {
                        layer_ycoor[k].append(bond[i][3]);
                        layer_ycoor[k].append(bond[i][2]);
                        data[k].atom_coordinate_y.append(bond[i][3]);
                        data[k].atom_coordinate_y.append(bond[i][2]);

                        }

                        else
                        {
                            layer_ycoor[k].append(bond[i][2]);
                            layer_ycoor[k].append(bond[i][3]);
                            data[k].atom_coordinate_y.append(bond[i][2]);
                            data[k].atom_coordinate_y.append(bond[i][3]);
                        }


                    }

                      if( i == 0 )
                      {

                          layer[k].resize(number_of_interface+1);
                          layer[k][number_of_interface].append(l+1); // l starts from 0 , but we need to save pos from 1, so set append(l+1).
                          cout << " layer " << k+1 << " number " << number_of_interface+1 << " append " << l+1 <<endl;
                           data[k].atom_coordinate_x.append(bond[i][0]);
                          number_of_interface += 1;  // go to next number ;

                          if(bond[i][2]>bond[i][3]) // start y 在 end y的下面 ?
                          {
                          layer_ycoor[k].append(bond[i][3]);
                          layer_ycoor[k].append(bond[i][2]);
                          data[k].atom_coordinate_y.append(bond[i][3]);
                          data[k].atom_coordinate_y.append(bond[i][2]);

                          }

                          else
                          {
                              layer_ycoor[k].append(bond[i][2]);
                              layer_ycoor[k].append(bond[i][3]);
                              data[k].atom_coordinate_y.append(bond[i][2]);
                              data[k].atom_coordinate_y.append(bond[i][3]);
                          }


                      }
                  }
                }

//             for(int j=i+1 ; j<bond.size();j++)
//              {
//                 cout << "start to check bond " << i+1  << " and bond " << j+1 << endl;
//                 if(   ((bond[i][2] == bond[j][2]  ) && (bond[i][3] == bond[j][3] )) ||
//                       ((bond[i][2] == bond[j][3]  ) && (bond[i][3] == bond[j][2] )) )  // if two bonds are at same height(same y)
//                 {

//                          for( int l=0 ; l<position.size();l++)      // find that bond's x position
//                            {

//                              if ( (bond[j][0] == position[l]) )    // if that bond's x = layer's x (found)
//                              {
//                                   layer[k].resize(number_of_interface+1);
//                                   layer[k][number_of_interface].append(l+1);
//                                   data[k].atom_coordinate_x.append(bond[j][0]);

////                                   cout << " layer " << k+1 << " number " << number_of_interface+1 << " append " << l+1 <<endl;

//                                   number_of_interface += 1;  // go to next number ;
//                              }

//                            }
//                          bond.removeAt(j);
//                          j--;
//                 }
//             }
//              bond.removeAt(i);
//              i--;  // remove bond i , so every bond have to go forward one position in the List.
//             k++; //go to the next layer.


           }



for(int j=0 ; j<order.size()-1; j++)         // add atom information to " data "
     {

       cout <<" interface" << j+1 << " y coor=" << data[j].atom_coordinate_y[0] << endl;
        cout <<" interface" << j+1 << " y coor=" << data[j].atom_coordinate_y[1] << endl;

        for(int i=0 ; i<data[j].atom_coordinate_x.size();i++)
        {
             cout <<" interface" << j+1 << " x coor=" << data[j].atom_coordinate_x[i] << endl;

        }

     }



for(int i=0;i<layer.size() ; i++)        //  add the interface_ position to "  data "
{

   for(int j=0 ; j<layer[i].size();j++)
   {
        data[i].interface_position.append(layer[i][j][0]);

        cout<< " data interface " << i+1 << " add " << layer[i][j][0] << endl;
   }

}





            QVector<QVector<QVector<int> > > Aromatic_ring;
            Aromatic_ring.resize(layer.size());



          for(int i=0;i<layer.size() ; i++)        //  check aromaticity ring in each interface (ex. {3,5} , {5,7} ... )
          {
              int Aromatic_size = 0 ;
//                  cout << " i size = " << layer.size() << endl  ;

             for(int j=0 ; j<layer[i].size()-1;j++)
             {
//                 cout << " j size = " << layer[i].size() << endl  ;
//                 cout << " now i = " << i << endl;
//                 cout << " now j = " << j << endl;
                 if(abs(layer[i][j+1][0]-layer[i][j][0]) == 2)  // if two bonds are near (like 3,5)
                 {

                     int neighbor_hit = 0 ;  // to check both two neighbors
                     double check_neighbor_x = position[ layer[i][j][0]] ;
                     cout << " check pos " << layer[i][j][0]+1 << endl;
                     cout<< " pos x = " << position[ layer[i][j][0] ] ;
                     double check_neighbor_y1 = layer_ycoor[i][0]-15;
                     double check_neighbor_y2 = layer_ycoor[i][1]+15;
                     cout << " y1= " << check_neighbor_y1 << " " << " y2= " << check_neighbor_y2 << endl;


                     for(int k=0 ; k<graph_item2->atom_coordinate.size();k++)     // check neighbor coor on which atom
                     {
                         if(graph_item2->atom_coordinate[k].x()== check_neighbor_x)
                         {
                           if(  (graph_item2->atom_coordinate[k].y() == check_neighbor_y1)
                                || (graph_item2->atom_coordinate[k].y() == check_neighbor_y2)  )
                               {
                                  neighbor_hit = neighbor_hit + (neighbor->m_neighborlist[k].size()) ;  // add its neighbor numbers
                               }
                           }
                       }







                     if(  (neighbor_hit == 5)  || (neighbor_hit == 4) ||(neighbor_hit == 6) )  // if two neighbor coor are = 2 .
                     {

                         bool aromaticity_ok = true ;

                         QPointF P1,P2,P3,P4,P5,P6;

                         P1.setX(position[ layer[i][j][0]-1 ]);
                         P2.setX(position[ layer[i][j][0] ]);
                         P3.setX(position[ layer[i][j][0]+1 ]);
                         P4.setX(position[ layer[i][j][0]+1 ]);
                         P5.setX(position[ layer[i][j][0] ]);
                         P6.setX(position[ layer[i][j][0]-1 ]);

                         P1.setY(check_neighbor_y1+15);
                         P2.setY(check_neighbor_y1);
                         P3.setY(check_neighbor_y1+15);
                         P4.setY(check_neighbor_y2-15);
                         P5.setY(check_neighbor_y2);
                         P6.setY(check_neighbor_y2-15);


                         int get_six_corners =0;


                         for(int a=0;a<edges.size();a++)
                         {

                             if( ((graph_item2->getStartPoint(edges[a]) == P1) && (graph_item2->getEndPoint(edges[a]) == P2) ) ||
                                 ((graph_item2->getStartPoint(edges[a]) == P2) && (graph_item2->getEndPoint(edges[a]) == P1) ) ||
                                 ((graph_item2->getStartPoint(edges[a]) == P2) && (graph_item2->getEndPoint(edges[a]) == P3) ) ||
                                     ((graph_item2->getStartPoint(edges[a]) == P3) && (graph_item2->getEndPoint(edges[a]) == P2) ) ||
                                     ((graph_item2->getStartPoint(edges[a]) == P3) && (graph_item2->getEndPoint(edges[a]) == P4) ) ||
                                     ((graph_item2->getStartPoint(edges[a]) == P4) && (graph_item2->getEndPoint(edges[a]) == P3) ) ||
                                     ((graph_item2->getStartPoint(edges[a]) == P4) && (graph_item2->getEndPoint(edges[a]) == P5) ) ||
                                     ((graph_item2->getStartPoint(edges[a]) == P5) && (graph_item2->getEndPoint(edges[a]) == P4) ) ||
                                     ((graph_item2->getStartPoint(edges[a]) == P5) && (graph_item2->getEndPoint(edges[a]) == P6) ) ||
                                     ((graph_item2->getStartPoint(edges[a]) == P6) && (graph_item2->getEndPoint(edges[a]) == P5) ) ||
                                     ((graph_item2->getStartPoint(edges[a]) == P6) && (graph_item2->getEndPoint(edges[a]) == P1) ) ||
                                     ((graph_item2->getStartPoint(edges[a]) == P1) && (graph_item2->getEndPoint(edges[a]) == P6) )
                                     )
                             {

                                 get_six_corners ++;



                             }




                         }


                    if(get_six_corners == 6)
                    {

                       if( i>0 )  // 若有上層
                         {
                                     cout << " up order = " << data[i-1].order[0] << " up number of interface bonds = " << data[i-1].interface_position.size() << endl;
                           if(data[i-1].order[0] == data[i-1].interface_position.size())  // 若上層order = interface bond 數
                         {
                               // check 是否上層的interface bond有插在我們要觀察的aromaticity 環上?

                             for(int a=0 ; a< data[i-1].interface_position.size();a++)
                             {
                                 if(  data[i-1].interface_position[a] == (layer[i][j][0]+1) )
                                 {
                                     aromaticity_ok = false;

                                 }

                             }

                         }

                         }

                       if( i<layer.size() )  // 若有下層
                         {

                           cout << " lower order = " << data[i+1].order[0] << " lower number of interface bonds = " << data[i+1].interface_position.size() << endl;

                           if(data[i+1].order[0] == data[i+1].interface_position.size())  // 若下層order = interface bond 數
                         {
                               // check 是否上層的interface bond有插在我們要觀察的aromaticity 環上?

                             for(int a=0 ; a< data[i+1].interface_position.size();a++)
                             {
                                 if(  data[i+1].interface_position[a] == (layer[i][j][0]+1) )
                                 {
                                     aromaticity_ok = false;

                                 }

                             }

                         }

                       }

                         }

                    else
                    {
                     aromaticity_ok = false;
                    }







                        if(aromaticity_ok == true)
                         {
                         Aromatic_size ++ ;
                         Aromatic_ring[i].resize(Aromatic_size);
                         Aromatic_ring[i][Aromatic_size-1].append(layer[i][j][0]);
                         Aromatic_ring[i][Aromatic_size-1].append(layer[i][j+1][0]);
                         cout << "At layer " << i+1  << "  " << layer[i][j][0] << " and " << layer[i][j+1][0] << " have aromaticity ring" << endl;
                         layer[i].insert(j+1,Aromatic_ring[i][Aromatic_size-1]);
                         j++;
                         }
                     }

                   }
                 }



            }



//                    for(int i=0;i<Aromatic_ring.size() ; i++)
//                    {

//                     for(int j=0 ; j<Aromatic_ring[i].size();j++)
//                      {
//                          cout << " i = " << i << " j = " << j <<" aro [i] [j] size = " << Aromatic_ring[i][j].size()<< endl;
//                          cout << "layer " << i+1 << " aro has " << Aromatic_ring[i][j][0] << endl;
//                          cout << "layer " << i+1 << " aro has " << Aromatic_ring[i][j][1] << endl;
//                      }
//                  }




//          for(int i=0;i<Aromatic_ring.size() ; i++)         // append aromatic ring to "layer"
//          {

//           for(int j=0 ; j<Aromatic_ring[i].size();j++)
//            {
////               layer[k].resize(layer[k].size()+1);
//             for(int k=0;k<layer[i].size();k++)
//               {
//                  if(layer[i][k][0]>Aromatic_ring[i][j][0])
//                    {

//                      layer[i].insert(k,Aromatic_ring[i][j]);

//                     }
//               }

//            }
//        }






      for(int i=0 ; i<layer.size();i++)
      {

           for(int j=0 ; j<layer[i].size();j++)
           {


              if(layer[i][j].size()==2)
              {
                  for(int k=0 ; k<layer[i][j].size();k++)

               {
                   cout << " layer " << i+1 << " has  aromaticity ring " <<  layer[i][j][k] << endl;

               }
             }

              else
             {
                  cout << " layer " << i+1 << " has " << layer[i][j][0] << endl;
             }


           }


      }


//          for(int i=0 ; i<layer_ycoor.size();i++)
//          {
//              for(int k=0 ; k<layer_ycoor[i].size();k++)
//              {
//                  cout << "layer " << i+1 << " has " << layer_ycoor[i][k] <<endl;
//              }
//          }




         QVector<QVector<int> > zz_layer;
         zz_layer.resize(order.size());
        cout << " interface " << " size = " << layer.size() <<endl;
        layer_permu.resize(layer.size());
    // layer[][] = 行,數字

   for(int a=0 ; a<layer.size(); a++)
    {
        p=0;
        cout << " m = " <<  layer[a].size() << endl;
        int m =  layer[a].size();  // Cm取n的m
        int n =  order[a];         // Cm取n的n
        int possible_permutation = factorial(m) / ( factorial(n)*factorial(m-n)) ; // Cm取n的值
        cout << " possible_permutation=  " << possible_permutation << endl;
        layer_permu[a].resize(1);  // layer_permu[][][][] = 行,第一個possibility,數字組合,數字




//        for(int b=0 ; b<layer_permu[a].size();b++)
//        {
//            layer_permu[a][b].resize(n);
//        }


        for(int i=0 ; i<=(m-n) && n>0 ; i++)
         {
              cout << "do crecur one time " << endl;
              cout << "start from k = " << i+1 << " n = " << n-1 << " a = " << a << endl;
             check = m-n-i ;
              c_recur(i+1,n-1,m,templist,a,0);

          }


  }




   for(int i=0; i<layer_permu.size();i++)               // delete same number at double bond and aromatic ring , beacuse double bond and aro can not be the same position
   {
       for(int j=0; j<layer_permu[i].size();j++)
       {

            bool again = false;

           for(int k=0; k<layer_permu[i][j].size();k++)
           {

              if( layer_permu[i][j][k].size()==2)
               {

                  for ( int l=0 ; l<layer_permu[i][j].size();l++)
                  {

                    if(l!=k)
                     {
                        for(int m=0 ; m<layer_permu[i][j][l].size();m++)
                              {

                                    if( (layer_permu[i][j][l][m] == layer_permu[i][j][k][0]) || (layer_permu[i][j][l][m] == layer_permu[i][j][k][1]) )
                                         {
                                              again = true;

                                         }

                               }
                     }


                 }


           }

           }


           if(again == true)
           {
               layer_permu[i].removeAt(j);

               j--;

                cout << "remove success" << endl;
           }



       }

   }




   int layer_number = 0;                            // define the position to each fragment
   int count_temp = 0 ;

   for ( int i=0 ; i< value_y.size();i++)
   {
      if(count_temp == (i-2))
      {
          count_temp = i;
          layer_number++ ;

      }

          for(int j=0 ; j<graph_item2->atom_coordinate.size();j++)
          {
              if( value_y[i] ==graph_item2->atom_coordinate[j].ry() )
              {


                  for( int k=0 ; k<position.size();k++ )
                  {
                      if( graph_item2->atom_coordinate[j].rx() == position[k])
                      {

                          data[layer_number].fragment_position.append(k+1);

                      }


                  }

              }


          }

   }



   for(int a=0 ; a<layer_permu.size()+1;a++)
   {
   for(int i=0;i<data[a].fragment_position.size();i++)                  // arrange  from small to big
      {
       for(int j=0; j<data[a].fragment_position.size()-1; j++ )
        {     if(data[a].fragment_position[j] > data[a].fragment_position[j+1])
            {
               double tmp=data[a].fragment_position[j];
               data[a].fragment_position[j]=data[a].fragment_position[j+1];
               data[a].fragment_position[j+1] = tmp ;
             }
         }
       }
   }


   for(int a=0 ; a<layer_permu.size()+1;a++)
   {
       int number_of_fragment_for_each_layer =0 ;
       data[a].fragment_position_split.resize(count[a].size());

       cout << " layer " << a+1  << " fragment resize to " << count[a].size() << endl;;
       data[a].fragment_position_split[number_of_fragment_for_each_layer].append(data[a].fragment_position[0]);

cout << " ok " << endl;

      for(int i=0 ;i<check_layer_type_x[a].size()-1;i++)
      {
          QPointF P1,P2;
          P1.setX(check_layer_type_x[a][i]);
          P2.setX(check_layer_type_x[a][i+1]);
          P1.setY(check_layer_type_y[a][i]);
          P2.setY(check_layer_type_y[a][i+1]);
          bool split = true;


          for(int b=0;b<edges.size();b++)
          {

              if(     (  (graph_item2->getStartPoint(edges[b]) == P1) &&   (graph_item2->getEndPoint(edges[b]) == P2) )   ||
                      (  (graph_item2->getStartPoint(edges[b]) == P2) &&   (graph_item2->getEndPoint(edges[b]) == P1) ))
              {

                  data[a].fragment_position_split[number_of_fragment_for_each_layer].append(data[a].fragment_position[i+1]);
                  split = false;
             cout << " okok " << endl;

              }

          }

          if(split == true)
          {


                  number_of_fragment_for_each_layer++;
                  data[a].fragment_position_split[number_of_fragment_for_each_layer].append(data[a].fragment_position[i+1]);



          }





      }
   }





//   for(int a=0 ; a<layer_permu.size()+1;a++)
//   {
//       int number_of_fragment_for_each_layer =0 ;
//       data[a].fragment_position_split.resize(count[a].size());
//       data[a].fragment_position_split[number_of_fragment_for_each_layer].append(data[a].fragment_position[0]);

//   for(int i=0;i<data[a].fragment_position.size()-1;i++)
//      {


//        if((data[a].fragment_position[i+1] - data[a].fragment_position[i]) == 1 )
//        {

//            data[a].fragment_position_split[number_of_fragment_for_each_layer].append(data[a].fragment_position[i+1]);
//        }

//        else
//        {
//           number_of_fragment_for_each_layer ++;
//           data[a].fragment_position_split[number_of_fragment_for_each_layer].append(data[a].fragment_position[i+1]);


//        }

//      }
//   }

    for(int i=0 ; i<layer_permu.size()+1;i++)
   {
        cout << " fragment  " <<  i+1 ;
      for ( int j=0 ; j<data[i].fragment_position_split.size();j++)
      {
          cout << " list " << j+1 << " has " ;

          for( int k=0 ; k<data[i].fragment_position_split[j].size();k++ )
          {
                cout << data[i].fragment_position_split[j][k] << "  " ;

          }
       }

      cout << endl;

   }



   ZZ_polynomial[layer_permu.size()].resize(1);
   ZZ_polynomial_int[layer_permu.size()].resize(1);



   for(int i=0; i<layer_permu.size();i++)
   {

      data[i].interface_permu.resize(layer_permu[i].size());    // 第i層有幾個possibility?
      ZZ_polynomial[i].resize(layer_permu[i].size());
      ZZ_polynomial_int[i].resize(layer_permu[i].size());

      cout << " -----now complete resize layer " << i+1 << " interface_permu to " << data[i].interface_permu.size()<<endl;
    //  cout << " data " << i+1 << " size = " << data[i].interface_permu.size()<<endl;


       for(int j=0; j<layer_permu[i].size();j++)
       {

            data[i].interface_permu[j].resize(layer_permu[i][j].size());  // 第i層 第j個possibility內有幾個元素?

            cout << " ------now complete resize possibility " << j+1 <<  " to " << data[i].interface_permu[j].size()<<endl;
           // cout << " data " << i+1 << " possibility " << j+1 << " size = " << data[i].interface_permu[j].size()<<endl;

           for(int k=0; k<layer_permu[i][j].size();k++)
           {


              if( layer_permu[i][j][k].size()==2)
               {
                      // 第i層 第j個possibility  裡面的第k個元素是aro還是double?

                     data[i].interface_permu[j][k].append(layer_permu[i][j][k][0]);
                     data[i].interface_permu[j][k].append(layer_permu[i][j][k][1]);

                     cout << " layer " << i+1 << " possibility " << j+1 << " has  aromaticity ring at " <<  layer_permu[i][j][k][0] << " and " <<  layer_permu[i][j][k][1]<< endl;
                     // cout << " data " << i+1 << " possibility " << j+1 << " has  aromaticity ring at " <<  data[i].interface_permu[j][k][0] << " and " <<  data[i].interface_permu[j][k][1]<< endl;
                     // cout << " data " << i+1 << " possibility " << j+1 << " size = " << data[i].interface_permu[j][k].size()<<endl;

              }

              else

              {
                  // 第i層 第j個possibility  裡面的第k個元素是aro還是double?
                   data[i].interface_permu[j][k].append(layer_permu[i][j][k][0]);
                   cout << " layer " << i+1 << " possibility " << j+1 << " has double bond at  " <<  layer_permu[i][j][k][0] << endl;
                  // cout << " data " << i+1 << " possibility " << j+1 << " has double bond at  " <<  data[i].interface_permu[j][k][0] << endl;
                  // cout << " data " << i+1 << " possibility " << j+1 << " size = " << data[i].interface_permu[j][k].size()<<endl;


              }
           }

       }

   }


    data[0].reduced_permu_upper.resize(0);   // upper frist one =0
    data[layer_permu.size()].reduced_permu_lower.resize(0);  // lower last one = 0

   for(int i=0; i<layer_permu.size();i++)       //  resize  reduced permu upper and lower
   {
       data[i+1].reduced_permu_upper.resize(data[i+1].fragment_position_split.size());   // resize split list
       cout << " upper layer " << i+2 << " resize " <<  data[i+1].fragment_position_split.size() <<endl;

       data[i].reduced_permu_lower.resize(data[i].fragment_position_split.size());   // resize split list
       cout << " lower layer " << i+1 << " resize " <<  data[0].fragment_position_split.size() <<endl;

       for(int m=0 ; m<data[i+1].fragment_position_split.size();m++)   // for each fragment list
       {

            data[i+1].reduced_permu_upper[m].resize(layer_permu[i].size());     // resize possibility
             cout << " upper layer " << i+2 << " fragment " << m+1 << " possibility resize " << layer_permu[i].size() << endl;

//          for(int j=0; j<layer_permu[i].size();j++)
//           {
//            data[i+1].reduced_permu_upper[m][j].resize(layer_permu[i][j].size());  // resize element ( over size here!!)

//           // cout << " upper layer " << i+2 << " fragment " << m+1 << " possibility " << j+1 << " element resize " << layer_permu[i][j].size() << endl;
//           }

       }



       for(int m=0 ; m<data[i].fragment_position_split.size();m++)   // for each fragment list
       {
            data[i].reduced_permu_lower[m].resize(layer_permu[i].size());
            cout << " lower layer " << i+1 << " fragment " << m+1 << " possibility resize " << layer_permu[i].size() << endl;

//          for(int j=0; j<layer_permu[i].size();j++)
//           {
//                      data[i].reduced_permu_lower[m][j].resize(layer_permu[i][j].size());

//                   //   cout << " lower layer " << i+1 << " fragment " << m+1 << " possibility " << j+1 << " element resize " << layer_permu[i][j].size() << endl;
//           }

       }
  }


   cout << " now go to upper element resize " <<endl;

    for(int i=0 ; i<layer_permu.size();i++)               // add split permu to reduced permu
    {
     // cout << " now go to layer " << i << endl;
                            for(int m=0 ; m<data[i+1].fragment_position_split.size();m++)   // for each fragment list
                            {
                               cout << " fragment " << m+1 << endl;

                                    for ( int j=0 ; j < data[i].interface_permu.size();j++)          // for upper possibility
                                     {
                                        resize = 0 ;
                                        cout << " now possibility = " << j+1 << endl;


                                      for(int k=0 ; k<data[i].interface_permu[j].size();k++)         // for  upper element
                                      {
                                                 cout << " now element = " << k+1 << endl;

                                         for(int l=0 ; l<data[i].interface_permu[j][k].size();l++)   // for upper number
                                          {
                                              cout << " now number = " << l+1 ;
                                             cout << " which is " << data[i].interface_permu[j][k][l] << endl;

                                             for(int n=0 ; n<data[i+1].fragment_position_split[m].size();n++) // for fragment number
                                             {
                                                      cout << " fragment number = " << data[i+1].fragment_position_split[m][n] << endl; ;

                                            if(data[i+1].fragment_position_split[m][n] == data[i].interface_permu[j][k][l])
                                             {

                                                if(  data[i].interface_permu[j][k].size() == 2)
                                              {
                                                  if( l == 0)
                                                  {
                                                           cout << " now l  = " << l <<endl;
                                               data[i+1].reduced_permu_upper[m][j].resize(resize+1);
                   cout << " layer " << i+2 << " upper_fragment " << m+1 << " possibility " << j+1 << " resize element " << data[i+1].reduced_permu_upper[m][j].size() << endl;
                                                    data[i+1].reduced_permu_upper[m][j][resize].append(data[i].interface_permu[j][k][0]);
                                                    data[i+1].reduced_permu_upper[m][j][resize].append(data[i].interface_permu[j][k][1]);
                     cout << " layer " << i+2 <<" upper fragment " << m+1 << " possibility " << j+1 << " element " << resize+1 <<  " append " << data[i].interface_permu[j][k][l] <<" and  "<< data[i].interface_permu[j][k][l+1] <<endl;
                                                        resize ++ ;

                                                  }
                                                }
                                                else
                                                {
                 //cout << "  upper layer " << i+2 << "[ fragment list ]" << m+1 << " [possibility] " << j+1 << " [element] " << data[i].interface_permu[j][k][l] << " is ok " << endl;
                                            data[i+1].reduced_permu_upper[m][j].resize(resize+1);
                                   cout <<  " layer " << i+2 <<" upper fragment " << m+1 << " possibility " << j+1 << " resize element " << data[i+1].reduced_permu_upper[m][j].size() << endl;


                                              data[i+1].reduced_permu_upper[m][j][resize].append(data[i].interface_permu[j][k][l]);

                     cout << " layer " << i+2 << " upper fragment "  << m+1 << " possibility " << j+1 << " element " << resize+1 <<  " append " << data[i].interface_permu[j][k][l] <<"ok " <<endl;

                                             resize ++ ;

                                            // cout << " resize = " <<resize <<endl;

                                                }



                                                }
                                             }

                                           }

                                       }

                  }



              }
    }



    cout << " upper finish !" << endl;





    for(int i=0 ; i<layer_permu.size()+1;i++)               // add split permu to reduced permu
    {
 //cout << " now at layer  " << i+1 << endl;
                            for(int m=0 ; m<data[i].fragment_position_split.size();m++)   // for each fragment list
                            {
                                cout << " fragment " << m+1 <<endl;

                                    for ( int j=0 ; j < data[i].interface_permu.size();j++)          // for lower possibility
                                     {

                                         resize =0 ;

                                         cout << " now possibility = " << j+1 << endl;

                                      for(int k=0 ; k<data[i].interface_permu[j].size();k++)         // for  lower element
                                      {
                                                   cout << " now element = " << k+1 << endl;


                                         for(int l=0 ; l<data[i].interface_permu[j][k].size();l++)   // for lower number
                                          {
                                             cout << " now number = " << l+1 ;
                                            cout << " which is " << data[i].interface_permu[j][k][l] << endl;

                                             for(int n=0 ; n<data[i].fragment_position_split[m].size();n++) // for fragment number
                                             {
                                                      cout << " fragment number = " << data[i].fragment_position_split[m][n] << endl; ;

                                            if(data[i].fragment_position_split[m][n] == data[i].interface_permu[j][k][l])
                                             {

                                                if(  data[i].interface_permu[j][k].size() == 2)

                                                {

                                                 if( l == 0 )
                                                 {

                                                     data[i].reduced_permu_lower[m][j].resize(resize+1);
                                   cout <<  " layer " << i+1 <<" lower fragment " << m+1 << " possibility " << j+1 << " resize element " << data[i].reduced_permu_lower[m][j].size()<<endl;

                                                    data[i].reduced_permu_lower[m][j][resize].append(data[i].interface_permu[j][k][l]);
                                                    data[i].reduced_permu_lower[m][j][resize].append(data[i].interface_permu[j][k][l+1]);

                cout <<  " layer " << i+1 <<" lower fragment " << m+1 << " possibility " << j+1 << " element " << resize+1 <<  " append  " << data[i].interface_permu[j][k][l]<<" and " <<  data[i].interface_permu[j][k][l+1] <<endl;

                              resize ++ ;
                                                  }
                                                }


                                         else
                                                {
                                                    data[i].reduced_permu_lower[m][j].resize(resize+1);
                                  cout << " layer " << i+1 << " lower fragment " << m+1 << " possibility " << j+1 << " resize element " << data[i].reduced_permu_lower[m][j].size()<<endl;


                                              data[i].reduced_permu_lower[m][j][resize].append(data[i].interface_permu[j][k][l]);

                                              cout <<  " layer " << i+1 <<" lower fragment " << m+1 << " possibility " << j+1 << " element " << resize+1 <<  " append  " << data[i].interface_permu[j][k][l]<<endl;

                                              resize ++ ;

                                                }

                                            }

                                          }
                                         }

                                      }

                                  }

                  }
    }









    cout << " lower finish !" << endl;




  // start my producer!!



      for(int i=0 ; i<layer_permu.size()+1;i++)  // for layer  0-4
      {

      int max_fragment_number = data[i].fragment_position_split.size();

      possibility = 0 ;


      tempZ_zz_int.clear();

      temp_zz.clear();

      int max_power = 0 ;


         for( int j=0 ; j < data[i].fragment_position_split.size() ; j++)   // for fragment list
          {
                  int current_fragemnt_list = j ;

//                  cout << " now lower size = " << data[i].reduced_permu_lower.size() << endl;
//                  cout << " reduced permu lower 0 0size = " << data[i].reduced_permu_lower[0][0].size() << endl;


                 if( (data[i].reduced_permu_lower.size()==0) ||  (data[i].reduced_permu_lower[0][0].size()==0)   )  //  if   lower = 0 ?
                 // if( check_zero(data[i].reduced_permu_lower) == true)
                  {

 if(j ==0)
{
     for( int p=0 ; p<ZZ_polynomial_int[layer_number-1][possibility].size();p++)  // check 上層最大的power 在哪是多少
     {
         if(ZZ_polynomial_int[layer_number-1][possibility].size()-1 > max_power )

         {
            max_power = ZZ_polynomial_int[layer_number-1][possibility].size()-1;

             ZZ_polynomial_int[layer_number][0].resize(max_power+1);
         }
      }

                for(int k=0 ;k< data[i].reduced_permu_upper[j].size();k++)   // 開始步驟 check每個上的元素
              {  original_order = data[i-1].order[0];

                possibility = k ;
  if_lower_zero(i,current_fragemnt_list,max_fragment_number,data[i-1].order[0],possibility, data[i].reduced_permu_upper,data[i].reduced_permu_lower, data[i].layer_type ,data[i].interface_permu,data[i].interface_permu.size());
              }


  }

                }

//           if(data[i].reduced_permu_lower.size()!=0)    // if lower != 0



          else // if lower !=0
          {

            if((data[i].reduced_permu_upper.size()==0) || (data[i].reduced_permu_upper[0][0].size()==0))  //  if   upper = 0 ?
        //if( check_zero(data[i].reduced_permu_upper) == true)


            {
                if(j == 0 )
              {

                   cout << " start to check upper =0 ; lower !=0 " << endl;
                for(int a=0 ; a<data[i].reduced_permu_lower[j].size();a++)
                {

          original_order = data[i].order[0];
          cout << " original order = " << data[i].order[0] << endl;

       possibility = a ;

       cout << " possibility = " << a ;

  if_upper_zero(i,current_fragemnt_list,max_fragment_number,data[i].order[0],possibility,data[i].reduced_permu_lower, data[i].layer_type ,data[i].interface_permu,data[i].interface_permu.size());
               }
             }


           }







            else  //  if   upper != 0 ?
            {
                if(current_fragemnt_list == 0)
                {

                    cout << " go the normal producure" << endl;

                // normal_procedure(i,j,data[i].reduced_permu_upper,data[i].reduced_permu_lower, data[i].layer_type[0] );

                 normal_procedure(i,current_fragemnt_list,max_fragment_number, data[i].reduced_permu_upper,data[i].reduced_permu_lower, data[i].layer_type[j][0] ,data[i].interface_permu);
                 cout << "end the normal producure" <<endl;

                }




            }






          }



        }




}






      for(int i=0 ; i<ZZ_polynomial_int[layer_permu.size()][0].size();i++ )
      {
             cout << " power " << i << " has " << ZZ_polynomial_int[layer_permu.size()][0][i].size()<<endl;

                 QString x = QString("x to the power of %1, cofficient = %2").arg(i).arg( ZZ_polynomial_int[layer_permu.size()][0][i].size());
                 QGraphicsTextItem *text = new QGraphicsTextItem(x);
                 text->setFont(font);
                 text->setDefaultTextColor("blue");
                 text->setPos(standard_p.x()-300,standard_p.y()-30*i);
                 scene -> addItem(text);
                 m_textItems2.append(text);

      }


}


bool johanna::check_zero(QVector<QVector<QVector<QVector<int> > > > List)

{

    bool zero = true;


    for(int i=0;i<List.size();i++)
    {
        for(int j=0;j<List[i].size();j++)
        {
            for(int k=0;k<List[i][j].size();k++)
            {
                  if(List[i][j].size()!=0)
                  {

                      zero = false;




                  }


            }


        }


    }

    return zero;



}


void johanna::if_upper_zero(int layer_number , int fragment ,int max_fragment_number ,int order,int possibility , QVector<QVector<QVector<QVector<int> > > > reduced_lower,  QVector<QVector<char> >  layer_type,QVector<QVector<QVector<int> > >  interface_permu,int last_layer_permu_size)


{

    cout << " func ok " << endl;
    if ( (layer_type[fragment][0] == 'L') || (layer_type[fragment][0] == 'R') )
    {

                // cout << " No ! , at lower != 0   , shape = L,R , upper =0 , which is ";
         if(reduced_lower[fragment][possibility].size()!=0)

         {
           cout << " No ! , at lower != 0   , shape = L,R , upper =0 " << endl;

         }

         else
         {
                 if(fragment != (max_fragment_number-1))
                 {
                     cout << " max_fragment number != fragment +1 " << endl;
                     cout << " max = " << max_fragment_number << " fragment = " << fragment+1 << endl;
                     fragment++;
                 if_upper_zero(layer_number,fragment,max_fragment_number,order,possibility,reduced_lower,layer_type,interface_permu,last_layer_permu_size);
                 return;

                }
                 else  // fragment over
                 {
                     if(order==0)
                     {
                         cout << "  fragment over order over!! " << endl;
                                      if( layer_number == 0) // if at the frist layer
                                     {

                                          ZZ_polynomial_int[layer_number][possibility].resize(check_ZZ_polynomial(interface_permu[possibility])+1);  // resize power
                                          ZZ_polynomial_int[layer_number][possibility][check_ZZ_polynomial(interface_permu[possibility])].append(1); // add one

                                      }

                                      else // not at the frist layer

                                ZZ_polynomial_int[layer_number][possibility].resize(ZZ_polynomial_int[layer_number-1][0].size()+check_ZZ_polynomial(interface_permu[possibility]));

                                           for(int e=0 ; e<ZZ_polynomial_int[layer_number-1][0].size();e++)    //上層power
                                           {
                                               for(int r=0 ; r<ZZ_polynomial_int[layer_number-1][0][e].size();r++)  // 上層數目
                                               {
                                ZZ_polynomial_int[layer_number][possibility][e+check_ZZ_polynomial(interface_permu[possibility])].append(1);


                                               }

                                           }



                                      }
                     }
        }

    }



    if ( layer_type[fragment][0] == 'N' )
    {
         cout << " NO! , at lower != 0 , upper=0 , shape = N  " << endl;
    }

    if (layer_type[fragment][0] == 'W' )

    {

         if( reduced_lower[fragment][possibility].size()==1)   // if element size =1
         {
                 cout << " got it , at lower != 0   ,  upper = 0 , shape = W , element size = 1, which is ";

                 cout << "[ order ]" << order << endl;

                 order -- ;

                 for( int b=0 ; b<reduced_lower[fragment][possibility][0].size();b++)
                 {
                     cout << reduced_lower[fragment][possibility][0][b] <<  "  " ;

                 }
                 if(fragment != (max_fragment_number-1))
                 {
                     cout << " max_fragment number != fragment +1 " << endl;
                     cout << " max = " << max_fragment_number << " fragment = " << fragment+1 << endl;
                     fragment++;
    if_upper_zero(layer_number,fragment,max_fragment_number,order,possibility,reduced_lower,layer_type,interface_permu,last_layer_permu_size);
    return;
                 }

                 else   // fragment over
                 {

if(order==0)
{
    cout << "  fragment over order over!! " << endl;
                 if( layer_number == 0) // if at the frist layer
                {
                     // QString temp_z = QString("x^%1").arg(check_ZZ_polynomial(interface_permu[possibility]));
                   //  ZZ_polynomial[layer_number][possibility].append(temp_z);
                     ZZ_polynomial_int[layer_number][possibility].resize(check_ZZ_polynomial(interface_permu[possibility])+1);  // resize power
                     ZZ_polynomial_int[layer_number][possibility][check_ZZ_polynomial(interface_permu[possibility])].append(1); // add one
                    // cout << " frist layer possibility" << possibility+1 <<" ZZ is " <<  ZZ_polynomial[layer_number][possibility][0].toStdString() <<endl;
                     // cout << " frist layer possibility" << possibility+1 <<" x to power of  " << check_ZZ_polynomial(interface_permu[possibility])<< " is " << 1 <<endl;

                 }

                 else // not at the frist layer
                 {
//QString zz = QString("(%1)*(x^%2)").arg( ZZ_polynomial[layer_number-1][0][0]).arg(check_ZZ_polynomial(interface_permu[possibility])); // if =0 ; upper has only 1 possibility
                   //   ZZ_polynomial[layer_number][possibility].append(zz);

           ZZ_polynomial_int[layer_number][possibility].resize(ZZ_polynomial_int[layer_number-1][0].size()+check_ZZ_polynomial(interface_permu[possibility]));

                      for(int e=0 ; e<ZZ_polynomial_int[layer_number-1][0].size();e++)    //上層power
                      {
                          for(int r=0 ; r<ZZ_polynomial_int[layer_number-1][0][e].size();r++)  // 上層數目
                          {
           ZZ_polynomial_int[layer_number][possibility][e+check_ZZ_polynomial(interface_permu[possibility])].append(1);


        //   cout << " power " << e+check_ZZ_polynomial(data[i].interface_permu[possibility]) << " +1 " <<endl;


                          }

                      }

       // cout << " layer " << layer_number+1 << " possibility " << possibility+1 << " ZZ is " <<  ZZ_polynomial[layer_number][possibility][0].toStdString() <<endl;



                 }
}

         }


         }





         if( reduced_lower[fragment][possibility].size()==0)  // 若沒東西
         {
             if(fragment != (max_fragment_number-1))
             {
                 cout << " max_fragment number != fragment +1 " << endl;
                 cout << " max = " << max_fragment_number << " fragment = " << fragment+1 << endl;
                 fragment++;
             if_upper_zero(layer_number,fragment,max_fragment_number,order,possibility,reduced_lower,layer_type,interface_permu,last_layer_permu_size);
             return;

            }
             else  // fragment over
             {
if(order ==0)
{

        cout << "  fragment over order over!! " << endl;

             if(layer_number == 0)  // if at the first layer
             {

//                 QString temp_z = QString("x^%1").arg(check_ZZ_polynomial(interface_permu[possibility]));
//                ZZ_polynomial[layer_number][possibility].append(temp_z);
                ZZ_polynomial_int[layer_number][possibility].resize(check_ZZ_polynomial(interface_permu[possibility])+1);  // resize power
                ZZ_polynomial_int[layer_number][possibility][check_ZZ_polynomial(interface_permu[possibility])].append(1); // add one

              //  cout << " frist layer possibility" << possibility+1 <<" ZZ is " <<  ZZ_polynomial[layer_number][possibility][0].toStdString() <<endl;
                 cout << " frist layer possibility" << possibility+1 <<" x to power of  " << check_ZZ_polynomial(interface_permu[possibility])<< " is " << 1 <<endl;



             }

             }
   }


             }




         else   // element size >1 !!
         {

             cout << "  No!! , at lower != 0 , upper = 0 , shape = N ,  element number in lower != 1 !!  " << endl;


         }


     }







}



void johanna::if_lower_zero(int layer_number , int fragment ,int max_fragment_number ,int order,int possibility,QVector<QVector<QVector<QVector<int> > > > reduced_upper , QVector<QVector<QVector<QVector<int> > > > reduced_lower,  QVector<QVector<char> >  layer_type,QVector<QVector<QVector<int> > >  interface_permu,int last_layer_permu_size)


{



    int max_power = 0;

    for( int s=0 ; s<ZZ_polynomial_int[layer_number-1].size();s++)  // check 上層 所有possibility的最大的power 在哪是多少
    {

    for( int p=0 ; p<ZZ_polynomial_int[layer_number-1][s].size();p++)
    {
        if(ZZ_polynomial_int[layer_number-1][s].size()-1 > max_power )

        {
           max_power = ZZ_polynomial_int[layer_number-1][s].size()-1;

           // ZZ_polynomial_int[layer_number][0].resize(max_power+1);
        }
     }

    }
        cout << " [ max power for last layer = ] " << max_power<< endl;
         ZZ_polynomial_int[layer_number][0].resize(max_power+1);
         cout << " resize to " << max_power+1 << endl;

//    for( int p=0 ; p<ZZ_polynomial_int[layer_number-1][possibility].size();p++)  // check 上層 這個possibility的最大的power 在哪是多少
//    {
//        if(ZZ_polynomial_int[layer_number-1][possibility].size()-1 > max_power )

//        {
//           max_power = ZZ_polynomial_int[layer_number-1][possibility].size()-1;

//           // ZZ_polynomial_int[layer_number][0].resize(max_power+1);
//        }
//     }



      cout << " [possibility ]= " << possibility ;

      cout << " [order]  " << order ;






        if ( (layer_type[fragment][0] == 'L') || (layer_type[fragment][0]== 'R') )
        {

            if( reduced_upper[fragment][possibility].size()==0)  // upper = 0 ?

            {

                     cout << " got it !" << endl;

                     if(fragment != (max_fragment_number-1))
                     {
                         cout << " max_fragment number != fragment +1 " << endl;
                         cout << " max = " << max_fragment_number << " fragment = " << fragment+1 << endl;
                         fragment++;



        if_lower_zero(layer_number,fragment,max_fragment_number,order,possibility,reduced_upper,reduced_lower,layer_type,interface_permu,last_layer_permu_size);
        return;



                     }

                     else   // fragment over
                     {

   if(order==0)
   {

        cout << " fragment over , order over " << endl;
                     if(layer_number == layer_permu.size())  // if at the lowest layer   // 因為data[i].interface permu[0] 沒有東西
                     {



                         for( int t=0 ; t<ZZ_polynomial_int[layer_number-1][possibility].size();t++)
                         {
                             for(int y=0 ; y<ZZ_polynomial_int[layer_number-1][possibility][t].size();y++)
                             {

                                  ZZ_polynomial_int[layer_number][0][t].append(1);

                            }

                             cout << " possibility " << possibility << " x to power of " << t << " has " << ZZ_polynomial_int[layer_number][0][t].size()<< endl;


                         }



                     }

                 else   // not at the lowest layer
                     {

                            for( int t=0 ; t<ZZ_polynomial_int[layer_number-1][possibility].size();t++)
                            {
                                for(int y=0 ; y<ZZ_polynomial_int[layer_number-1][possibility][t].size();y++)
                                {

                                     ZZ_polynomial_int[layer_number][0][t].append(1);

                               }

                                cout << " possibility " << possibility << " x to power of " << t << " has " << ZZ_polynomial_int[layer_number][0][t].size()<< endl;


                            }



                     }

   }

                   }
            }

            else
            {
                cout << " No!!  lower = 0 and the shape is L,R !! upper !=0  !! No combination !!" << endl;

            }


        }

        if(layer_type[fragment][0] == 'N')
        {

              //cout << " layer " << i+1 << " fragment " << j+1 <<" possibility " << a+1 <<  " element size = " << data[i].reduced_permu_upper[j][a].size() << endl;

           if( reduced_upper[fragment][possibility].size()==1)   // if element size =1
           {
                   cout << " got it , at lower=0   , shape =N , element size = 1, which is ";

                    order--;

                   for( int b=0 ; b<reduced_upper[fragment][possibility][0].size();b++)
                   {
                       cout << reduced_upper[fragment][possibility][0][b] <<  "  " ;

                   }

                   if(fragment != (max_fragment_number-1))
                   {
                       cout << " max_fragment number != fragment +1 " << endl;
                       cout << " max = " << max_fragment_number << " fragment = " << fragment+1 << endl;
                       fragment++;



      if_lower_zero(layer_number,fragment,max_fragment_number,order,possibility,reduced_upper,reduced_lower,layer_type,interface_permu,last_layer_permu_size);
      return;

                   }

                   else   // fragment over
                   {

 if(order==0)
 {

      cout << " fragment over , order over " << endl;
                   if(layer_number == layer_permu.size())  // if at the lowest layer   // 因為data[i].interface permu[0] 沒有東西
                   {

//                       QString zz = QString("(%1) +++ ").arg( ZZ_polynomial[layer_number-1][possibility][0]);
//                       temp_zz.append(zz);


                       //cout << " resize to " << ZZ_polynomial_int[i-1][possibility].size() << endl;



                       for( int t=0 ; t<ZZ_polynomial_int[layer_number-1][possibility].size();t++)
                       {
                           for(int y=0 ; y<ZZ_polynomial_int[layer_number-1][possibility][t].size();y++)
                           {

                                ZZ_polynomial_int[layer_number][0][t].append(1);

                          }

                           cout << " possibility " << possibility << " x to power of " << t << " has " << ZZ_polynomial_int[layer_number][0][t].size()<< endl;


                       }







                   }

               else   // not at the lowest layer
                   {
//                      QString zz = QString("(%1)+%2").arg( ZZ_polynomial[layer_number-1][possibility][0]).arg(check_ZZ_polynomial(interface_permu[0]));
//                      temp_zz.append(zz);



                          for( int t=0 ; t<ZZ_polynomial_int[layer_number-1][possibility].size();t++)
                          {
                              for(int y=0 ; y<ZZ_polynomial_int[layer_number-1][possibility][t].size();y++)
                              {

                                   ZZ_polynomial_int[layer_number][0][t].append(1);

                             }

                              cout << " possibility " << possibility << " x to power of " << t << " has " << ZZ_polynomial_int[layer_number][0][t].size()<< endl;


                          }



                   }

 }

                 }



                  // possibility ++ ;

                 //  order =original_order;


                        // cout << " data i-1 interface permu size = " <<  data[i-1].interface_permu.size() <<endl;

                //   cout << endl;





           }

           if( reduced_upper[fragment][possibility].size()==0)  // 若沒東西
           {

               if(fragment != (max_fragment_number-1))
               {
                   cout << " max_fragment number != fragment +1 " << endl;
                   cout << " max = " << max_fragment_number << " fragment = " << fragment+1 << endl;
                   fragment++;
               if_lower_zero(layer_number,fragment,max_fragment_number,order,possibility,reduced_upper,reduced_lower,layer_type,interface_permu,last_layer_permu_size);
               return;



              }

               else  // fragment over
               {

if(order ==0)
{

               if(layer_number == layer_permu.size())  // if at the lowest layer   // 因為data[i].interface permu[0] 沒有東西
               {

//                   QString zz = QString("(%1) +++ ").arg( ZZ_polynomial[layer_number-1][possibility][0]);
//                   temp_zz.append(zz);


                   for( int t=0 ; t<ZZ_polynomial_int[layer_number-1][possibility].size();t++)
                   {
                       for(int y=0 ; y<ZZ_polynomial_int[layer_number-1][possibility][t].size();y++)
                       {

                            ZZ_polynomial_int[layer_number][0][t].append(1);

                      }


                   }







               }

               else  // not at lowest layer
               {

                 //  QString zz = QString("(%1)+%2").arg( ZZ_polynomial[layer_number-1][possibility][0]).arg(check_ZZ_polynomial(interface_permu[0]));
                 //  temp_zz.append(zz);




                       for( int t=0 ; t<ZZ_polynomial_int[layer_number-1][possibility].size();t++)
                       {
                           for(int y=0 ; y<ZZ_polynomial_int[layer_number-1][possibility][t].size();y++)
                           {

                                ZZ_polynomial_int[layer_number][0][t].append(1);

                          }

                           cout << " possibility " << possibility << " x to power of " << t << " has " << ZZ_polynomial_int[layer_number][0][t].size()<< endl;


                       }
               }



  }

           }





           }


          if( reduced_upper[fragment][possibility].size()>1 )  //  狀況1 element size =1  , 狀況2 element size =0 , 狀況3 else (element size>1)
           {
                      //  possibility ++ ;
               cout << "  No!! , at lower = 0 , shape = N , element number in upper != 1 !!  " << endl;


           }


    }

        if(layer_type[fragment][0] == 'W')
        {
            cout << " lower = 0 , and the shape is W !!  No combination !!" << endl;

        }










}


int johanna::check_ZZ_polynomial(QVector<QVector<int> > possibility_list)
{
    int power_of_x = 0 ;

    for( int i=0 ;i< possibility_list.size();i++)
    {
        if(possibility_list[i].size()==2)
        {
            power_of_x ++ ;

        }

    }

    return power_of_x;




}

void johanna::normal_procedure(int layer_number , int fragment , int max_fragment_number ,QVector<QVector<QVector<QVector<int> > > > reduced_upper , QVector<QVector<QVector<QVector<int> > > > reduced_lower , char layer_type, QVector<QVector<QVector<int> > >  interface_permu)
{


        if ( (layer_type == 'N') || (layer_type == 'R') ) //上先
        {
            cout << " layer type= " << layer_type << endl;

            QVector<QString> temp_list;

            temp_list.resize(reduced_lower[fragment].size());

            for(int g=0 ; g<reduced_lower[fragment].size();g++)
            {
                 temp_list[g].append("");

                // cout << " add ok "<<endl;

            }


            for(int j=0 ; j < reduced_upper[fragment].size();j++)            // 上的possibility
            {


                // cout << " layer " << i << " has " << data[i].interface_permu.size() << " posssibility"<< endl;

                     for(int m=0 ; m<reduced_lower[fragment].size();m++)  // 下的possibility
                        {


                            // cout << " layer " << i+1 << " has " << reduced_lower[fragment].size()<< " possibility" << endl;
                          //   cout << " now down layer at possibility  " << m+1 <<" size = " << reduced_lower[fragment][m].size() <<  " m = " << m << endl;

                             for(int n=0 ; n<reduced_lower[fragment][m].size();n++)      // 下的元素
                                {

                                 // cout << "down  possibility " << m+1<< "  "  << " element " << n+1 << "   size = " << reduced_lower[fragment][m][n].size()<< endl;
                                 // cout << "up    possibility " << j+1 << "  " << " element" << n+1 << "   size = "  << data[i].interface_permu[j][n].size()<< endl;

                                     if(reduced_lower[fragment][m][n].size()==2)  // 若下的第n個元素是Ring
                                        {


                                         if( reduced_upper[fragment][j][n].size()==1) // 若上的第n個元素是double bond
                                        {
                                              if(reduced_upper[fragment][j][n][0] < reduced_lower[fragment][m][n][0] ) // check是否 上bond 位置 <  下ring[0] 位置      有→continue   沒→break
                                              {

                                                  cout << "up bond " << reduced_upper[fragment][j][n][0] << " " ;
                                                  cout << "down ring " <<reduced_lower[fragment][m][n][0] <<" " << reduced_lower[fragment][m][n][1] <<  "  ";
                                                  cout << " ------okok------" <<endl;



                                              }
                                              else
                                              {
                                                  cout<< "-----------n falied-------" << endl;
                                                  break;
                                              }

                                        }




                                           if(reduced_upper[fragment][j][n].size()==2) // 若上的第n個元素是Ring
                                          {
                                                if(reduced_upper[fragment][j][n][1] < reduced_lower[fragment][m][n][0] ) // check是否 上ring[1] 位置 <  下ring[0] 位置      有→continue   沒→break
                                                {

                                                    cout << "up ring " << reduced_upper[fragment][j][n][0] << " " << reduced_upper[fragment][j][n][1]<<endl << " ";
                                                    cout << "down ring " << reduced_lower[fragment][m][n][0] <<" " << reduced_lower[fragment][m][n][1] <<  "  ";
                                                    cout << " ------okok------" <<endl;
                                                }
                                                else
                                                {
                                                    cout<< "-----------n falied-------" << endl;
                                                    break;
                                                }

                                          }


                                   if(reduced_upper[fragment][j].size()>n+1)
                                       {
                                            if(reduced_upper[fragment][j][n+1].size()==2) // 若上的第n+1個元素是Ring
                                          {

                                                 // check是否 上ring[0] 位置 > 下ring[1]       有→continue   沒→break
                                                if(reduced_upper[fragment][j][n+1][0] > reduced_lower[fragment][m][n][1] )
                                               {

                                                    cout << "up ring n+1  " <<reduced_upper[fragment][j][n+1][0] << " " <<reduced_upper[fragment][j][n+1][1]<< "  ";
                                                    cout << "down ring " << reduced_lower[fragment][m][n][0] <<" " << reduced_lower[fragment][m][n][1] << "  ";
                                                    cout << " ------okok------" <<endl;

                                                    if( (max_fragment_number) != (fragment+1) )
                                                    {

                                                        cout << " max_fragment number != fragment +1 " << endl;
                                                        cout << " max = " << max_fragment_number << " fragment = " << fragment << endl;
                                                        fragment++;

                                          normal_procedure(layer_number,fragment,max_fragment_number,reduced_upper,reduced_lower,layer_type,interface_permu);

                                                    }

                                                    else
                                                    {




          if(n == (reduced_lower[fragment][m].size()-1)  )  // if at the last element at lower
          {
              if(ZZ_polynomial_int[layer_number-1][j].size()!=0)
{
            //

                       //


                    if(ZZ_polynomial_int[layer_number][m].size()< ZZ_polynomial_int[layer_number-1][j].size()+check_ZZ_polynomial(interface_permu[m]) )
                      {
                        ZZ_polynomial_int[layer_number][m].resize(ZZ_polynomial_int[layer_number-1][j].size()+check_ZZ_polynomial(interface_permu[m]));
                      }
                    for(int p=0 ; p<ZZ_polynomial_int[layer_number-1][j].size();p++ )
                    {

                        for(int r=0; r<ZZ_polynomial_int[layer_number-1][j][p].size(); r++  )
                        {
                            ZZ_polynomial_int[layer_number][m][p+check_ZZ_polynomial(interface_permu[m])].append(1);

                        }

                    }

  }
            }

                                                    }




                                                }
                                                else
                                                {

                                                    cout<< "-------------n+1 falied-------------" << endl;
                                                    break;
                                                }

                                          }

                                      }

                                    if(reduced_upper[fragment][j].size()>n+1)
                                        {
                                            if(reduced_upper[fragment][j][n+1].size()==1) // 若上的第n+1個元素是double bond
                                          {
                                              // check 是否 下ring[1] < 上bond         有→continue   沒→break
                                                if(reduced_upper[fragment][j][n+1][0] >  reduced_lower[fragment][m][n][1] )
                                                 {

                                                    cout << "up bond n+1 " <<  reduced_upper[fragment][j][n+1][0]<<" ";
                                                    cout << "down ring " << reduced_lower[fragment][m][n][0] <<" " << reduced_lower[fragment][m][n][1] << "  ";
                                                    cout << " ------okok------" <<endl;


                                                    if( (max_fragment_number) != (fragment+1) )
                                                    {

                                                        cout << " max_fragment number != fragment +1 " << endl;
                                                        cout << " max = " << max_fragment_number << " fragment = " << fragment << endl;
                                                        fragment++;

                                          normal_procedure(layer_number,fragment,max_fragment_number,reduced_upper,reduced_lower,layer_type,interface_permu);

                                                    }

                                                    else
                                                    {


                                                   if(n == (reduced_lower[fragment][m].size()-1)  )  // if at the last element at lower
                                                   {

                                                       if(ZZ_polynomial_int[layer_number-1][j].size()!=0)
                                   {
                                                     //


                                                                  //
                                                   if(ZZ_polynomial_int[layer_number][m].size()< ZZ_polynomial_int[layer_number-1][j].size()+check_ZZ_polynomial(interface_permu[m]) )
                                                     {
                                                       ZZ_polynomial_int[layer_number][m].resize(ZZ_polynomial_int[layer_number-1][j].size()+check_ZZ_polynomial(interface_permu[m]));
                                                     }
                                                   for(int p=0 ; p<ZZ_polynomial_int[layer_number-1][j].size();p++ )
                                                   {

                                                       for(int r=0; r<ZZ_polynomial_int[layer_number-1][j][p].size(); r++  )
                                                       {
                                                           ZZ_polynomial_int[layer_number][m][p+check_ZZ_polynomial(interface_permu[m])].append(1);

                                                       }

                                                   }

                                       }

                                                   }

                                                    }

                                                }
                                                else
                                                {

                                                    cout<< "-------------n+1 falied-------------" << endl;
                                                    break;
                                                }

                                          }
                                         }


                                    if(reduced_upper[fragment][j].size()== n+1) // 若上沒n+1
                                   {
                                        if( (max_fragment_number) != (fragment+1) )
                                        {

                                            cout << " max_fragment number != fragment +1 " << endl;
                                            cout << " max = " << max_fragment_number << " fragment = " << fragment << endl;
                                            fragment++;

                              normal_procedure(layer_number,fragment,max_fragment_number,reduced_upper,reduced_lower,layer_type,interface_permu);

                                        }
                                        else
                                        {

                            cout << " ok end " << endl;


        cout << "  no~" << endl;
        if(n == (reduced_lower[fragment][m].size()-1)  )  // if at the last element at lower
        {

            if(ZZ_polynomial_int[layer_number-1][j].size()!=0)
{
          //

                    //
        if(ZZ_polynomial_int[layer_number][m].size()< ZZ_polynomial_int[layer_number-1][j].size()+check_ZZ_polynomial(interface_permu[m]) )
          {
            ZZ_polynomial_int[layer_number][m].resize(ZZ_polynomial_int[layer_number-1][j].size()+check_ZZ_polynomial(interface_permu[m]));
          }

        for(int p=0 ; p<ZZ_polynomial_int[layer_number-1][j].size();p++ )
        {

            for(int r=0; r<ZZ_polynomial_int[layer_number-1][j][p].size(); r++  )
            {
                ZZ_polynomial_int[layer_number][m][p+check_ZZ_polynomial(interface_permu[m])].append(1);

            }

        }

   }

        }


                                        }

                                   }




                                    }


                                     else   // 若下的第n個元素是double bond

                                     {
                                         if(reduced_upper[fragment][j][n].size()==2) // 若上的第n個元素是Ring
                                        {
                                            // check是否 上ring[1] 位置 <  下 bond 位置      有→continue   沒→break

                                             if(reduced_upper[fragment][j][n][1] < reduced_lower[fragment][m][n][0] )
                                              {
                                                 cout << "up ring " << reduced_upper[fragment][j][n][0] << " " << reduced_upper[fragment][j][n][1]<<"  ";
                                                 cout << "down bond " << reduced_lower[fragment][m][n][0] << "  ";
                                                cout << " ------okok------" <<endl;

                                              }
                                             else
                                             {

                                                 cout<< "---------n falied-----------" << endl;
                                                 break;
                                             }

                                        }
                                         if(reduced_upper[fragment][j][n].size()==1) // 若上的第n個元素是double bond
                                        {

                                            // check是否 上bond位置 < 下bond             有→continue   沒→break
                                             if(reduced_upper[fragment][j][n][0] < reduced_lower[fragment][m][n][0] )
                                              {
                                                 cout << "up bond " << reduced_upper[fragment][j][n][0]<<"  ";
                                                 cout << "down bond " << reduced_lower[fragment][m][n][0] << "  ";
                                                cout << " ------okok------" <<endl;
                                              }
                                             else
                                             {

                                                 cout<< "---------n falied----------" << endl;
                                                 break;
                                             }
                                        }
                                      if(reduced_upper[fragment][j].size()>n+1)
                                      {
                                          if(reduced_upper[fragment][j][n+1].size()==2) // 若上的第n+1個元素是Ring
                                        {

                                            // check是否 上ring[0] 位置 > 下bond          有→continue   沒→break

                                              if(reduced_upper[fragment][j][n+1][0] > reduced_lower[fragment][m][n][0] )
                                               {
                                                  cout << "up ring n+1 " << reduced_upper[fragment][j][n+1][0] << " " << reduced_upper[fragment][j][n+1][1]<<"  ";
                                                  cout << "down bond " << reduced_lower[fragment][m][n][0] <<"  ";
                                                  cout << " ------okok------" <<endl;

                                                  if( (max_fragment_number) != (fragment+1) )
                                                  {

                                                      cout << " max_fragment number != fragment +1 " << endl;
                                                      cout << " max = " << max_fragment_number << " fragment = " << fragment << endl;
                                                      fragment++;

                                        normal_procedure(layer_number,fragment,max_fragment_number,reduced_upper,reduced_lower,layer_type,interface_permu);

                                                  }
                                                  else
                                                  {




                  if(n == (reduced_lower[fragment][m].size()-1)  )  // if at the last element at lower
                  {
                      if(ZZ_polynomial_int[layer_number-1][j].size()!=0)
  {

                    //

                               //
                  if(ZZ_polynomial_int[layer_number][m].size()< ZZ_polynomial_int[layer_number-1][j].size()+check_ZZ_polynomial(interface_permu[m]) )
                    {
                      ZZ_polynomial_int[layer_number][m].resize(ZZ_polynomial_int[layer_number-1][j].size()+check_ZZ_polynomial(interface_permu[m]));
                    }

                  for(int p=0 ; p<ZZ_polynomial_int[layer_number-1][j].size();p++ )
                  {

                      for(int r=0; r<ZZ_polynomial_int[layer_number-1][j][p].size(); r++  )
                      {
                          ZZ_polynomial_int[layer_number][m][p+check_ZZ_polynomial(interface_permu[m])].append(1);

                      }

                  }

                      }
                  }



                                                  }
                                               }
                                              else
                                              {

                                                  cout<< "-------------n+1 falied-------------" << endl;
                                                  break;
                                              }
                                        }

                                      }
                                       if(reduced_upper[fragment][j].size()>n+1)
                                       {

                                           if(reduced_upper[fragment][j][n+1].size()==1) // 若上的第n+1個元素是double bond
                                        {
                                            // check 是否 下bond < 上bond                   有→continue   沒→break
                                              if(reduced_lower[fragment][m][n][0] < reduced_upper[fragment][j][n+1][0] )
                                               {
                                                  cout << "up bond n+1 " << reduced_upper[fragment][j][n+1][0]<<"  "  ;
                                                  cout << "down bond " << reduced_lower[fragment][m][n][0] << "  ";
                                                  cout << " ------okok------" <<endl;

                                                  if( (max_fragment_number) != (fragment+1) )
                                                  {

                                                      cout << " max_fragment number != fragment +1 " << endl;
                                                      cout << " max = " << max_fragment_number << " fragment = " << fragment << endl;
                                                      fragment++;

                                        normal_procedure(layer_number,fragment,max_fragment_number,reduced_upper,reduced_lower,layer_type,interface_permu);

                                                  }
                                                  else
                                                  {





                  if(n == (reduced_lower[fragment][m].size()-1)  )  // if at the last element at lower
                  {

                    if(ZZ_polynomial_int[layer_number-1][j].size()!=0)
{
                    //

                               //
                  if(ZZ_polynomial_int[layer_number][m].size()< ZZ_polynomial_int[layer_number-1][j].size()+check_ZZ_polynomial(interface_permu[m]) )
                    {
                      ZZ_polynomial_int[layer_number][m].resize(ZZ_polynomial_int[layer_number-1][j].size()+check_ZZ_polynomial(interface_permu[m]));
                    }
                  for(int p=0 ; p<ZZ_polynomial_int[layer_number-1][j].size();p++ )
                  {

                      for(int r=0; r<ZZ_polynomial_int[layer_number-1][j][p].size(); r++  )
                      {
                          ZZ_polynomial_int[layer_number][m][p+check_ZZ_polynomial(interface_permu[m])].append(1);

                      }

                  }

      }
                  }


                                                  }
                                               }
                                              else
                                              {

                                                  cout<< "-------------n+1 falied-------------" << endl;
                                                  break;
                                              }

                                        }
                                      }

                                       if(reduced_upper[fragment][j].size()== n+1) // 若上沒n+1
                                      {
                                           if( (max_fragment_number) != (fragment+1) )
                                           {

                                               cout << " max_fragment number != fragment +1 " << endl;
                                               cout << " max = " << max_fragment_number << " fragment = " << fragment << endl;
                                               fragment++;

                                 normal_procedure(layer_number,fragment,max_fragment_number,reduced_upper,reduced_lower,layer_type,interface_permu);

                                           }
                                           else
                                           {



           if(n == (reduced_lower[fragment][m].size()-1)  )  // if at the last element at lower
           {

if(ZZ_polynomial_int[layer_number-1][j].size()!=0)
{
             //

                        //
           if(ZZ_polynomial_int[layer_number][m].size()< ZZ_polynomial_int[layer_number-1][j].size()+check_ZZ_polynomial(interface_permu[m]) )
             {
               ZZ_polynomial_int[layer_number][m].resize(ZZ_polynomial_int[layer_number-1][j].size()+check_ZZ_polynomial(interface_permu[m]));
             }
           for(int p=0 ; p<ZZ_polynomial_int[layer_number-1][j].size();p++ )
           {

               for(int r=0; r<ZZ_polynomial_int[layer_number-1][j][p].size(); r++  )
               {
                   ZZ_polynomial_int[layer_number][m][p+check_ZZ_polynomial(interface_permu[m])].append(1);

               }

           }


  }
           }



                                           }

                                      }

                                     }


                                }


                         }


                     if((j+1) == reduced_upper[fragment].size() )  // if upper finished than we can calculate the final zz at lower
                             {

                         for(int h=0 ; h<reduced_lower[fragment].size();h++)  // 下的possibility
                            {

                               //  ZZ_polynomial[layer_number][h].append(temp_list[h]);


      //  cout << " layer " << layer_number+1 << " possibility " << h+1 << " finished! ZZ = " << ZZ_polynomial[layer_number][h][0].toStdString() << endl;

        for(int i=0 ; i<ZZ_polynomial_int[layer_number][h].size();i++ )
        {

                  cout << " layer " << layer_number+1 << "  possibility " << h+1 << "power " << i << " has " << ZZ_polynomial_int[layer_number][h][i].size()<<endl;

        }

                         }



                               }

                }

             }





//sdsdsd

        if ( (layer_type == 'W') || (layer_type == 'L') ) //下先   sdsd
        {
            cout << " type = " <<layer_type << endl;

            for(int j=0 ; j<reduced_lower[fragment].size();j++)            // 下的possibility
            {
                QString temp_list;
                temp_list.clear();

                     for(int m=0 ; m<reduced_upper[fragment].size();m++)  // 上的possibility
                        {

                          for(int n=0 ; n<reduced_upper[fragment][m].size();n++)      // 上的元素
                                {

             //  cout << "up  possibility "     << m+1<< "  "  <<  " element " << "   size = " << reduced_upper[fragment][m].size()<< endl;
             //  cout << "down    possibility " << j+1 << "  " << " element "  << "   size = "  << reduced_lower[fragment][j].size()<< endl;

                                  if(reduced_upper[fragment][m][n].size()==2)  // 若上的第n個元素是Ring
                                      {

                                       if(reduced_lower[fragment][j][n].size()==2) // 若下的第n個元素是Ring
                                          {
                                                if(reduced_lower[fragment][j][n][1] < reduced_upper[fragment][m][n][0] ) // check是否 下ring[1] 位置 <  上ring[0] 位置      有→continue   沒→break
                                                {
                                                    if(reduced_lower[fragment][j].size()> n+1)
                                                      {
                                                           if(reduced_lower[fragment][j][n+1].size()==2) // 若下的第n+1個元素是Ring
                                                         {

                                                                // check是否 下ring[0] 位置 > 上ring[1]       有→continue   沒→break
                                                      if(reduced_lower[fragment][j][n+1][0] > reduced_upper[fragment][m][n][1] )
                                                              {
                                                                   cout << "up ring " << reduced_upper[fragment][m][n][0] << " " << reduced_upper[fragment][m][n][1]<<"  ";
                                                                   cout << "down ring " << reduced_lower[fragment][j][n][0] <<" " << reduced_lower[fragment][j][n][1] << "  ";
                                                                   cout << "down ring  n+1 " << reduced_lower[fragment][j][n+1][0] <<" " << reduced_lower[fragment][j][n+1][1] << "  ";
                                                                   cout << " ------okok------" <<endl;

                                                                   if( (max_fragment_number) != (fragment+1) )
                                                                   {

                                                                       cout << " max_fragment number != fragment +1 " << endl;
                                                                       cout << " max = " << max_fragment_number << " fragment = " << fragment << endl;
                                                                       fragment++;

                                                         normal_procedure(layer_number,fragment,max_fragment_number,reduced_upper,reduced_lower,layer_type,interface_permu);

                                                                   }

                                                                   else
                                                                   {


if(n == (reduced_upper[fragment][m].size()-1))
{

    if(ZZ_polynomial_int[layer_number-1][m].size()!=0)
    {
                   //

                     //

                     if(ZZ_polynomial_int[layer_number][j].size()<ZZ_polynomial_int[layer_number-1][m].size()+check_ZZ_polynomial(interface_permu[j]) )
                       {
                         ZZ_polynomial_int[layer_number][j].resize(ZZ_polynomial_int[layer_number-1][m].size()+check_ZZ_polynomial(interface_permu[j]));
                       }
                     for(int p=0 ; p<ZZ_polynomial_int[layer_number-1][m].size();p++ )
                     {

                         for(int r=0; r<ZZ_polynomial_int[layer_number-1][m][p].size(); r++  )
                         {
                             ZZ_polynomial_int[layer_number][j][p+check_ZZ_polynomial(interface_permu[j])].append(1);

                         }


                     }


    }
}


                                                                   }


                                                               }
                                                               else
                                                               {
                                                                   //cout<< "-------------n+1 falied-------------" << endl;
                                                                   break;
                                                               }





                                                         }



                                                     if(reduced_lower[fragment][j][n+1].size()==1) // 若下的第n+1個元素是double bond
                                                         {
                                                             // check 是否 上ring[1] < 下bond         有→continue   沒→break
                                                               if(reduced_upper[fragment][m][n][1] < reduced_lower[fragment][j][n+1][0] )
                                                                {

                                                                   cout << "up ring " << reduced_upper[fragment][m][n][0] << " " << reduced_upper[fragment][m][n][1]<<"  ";
                                                                   cout << "down ring " << reduced_lower[fragment][j][n][0] <<" " << reduced_lower[fragment][j][n][1] << "  ";
                                                                   cout << "down bond n+1 " << reduced_lower[fragment][j][n+1][0] << "  ";
                                                                   cout << " ------okok------" <<endl;

                                                                   if( (max_fragment_number) != (fragment+1) )
                                                                   {

                                                                       cout << " max_fragment number != fragment +1 " << endl;
                                                                       cout << " max = " << max_fragment_number << " fragment = " << fragment << endl;
                                                                       fragment++;

                                                         normal_procedure(layer_number,fragment,max_fragment_number,reduced_upper,reduced_lower,layer_type,interface_permu);

                                                                   }


                                                                   else
                                                                   {

                                                                       if(n == (reduced_upper[fragment][m].size()-1))
                                                                       {
                                                                           if(ZZ_polynomial_int[layer_number-1][m].size()!=0)
                                                                           {
                   //


                     //

                     if(ZZ_polynomial_int[layer_number][j].size()<ZZ_polynomial_int[layer_number-1][m].size()+check_ZZ_polynomial(interface_permu[j]) )
                       {
                         ZZ_polynomial_int[layer_number][j].resize(ZZ_polynomial_int[layer_number-1][m].size()+check_ZZ_polynomial(interface_permu[j]));
                       }
                     for(int p=0 ; p<ZZ_polynomial_int[layer_number-1][m].size();p++ )
                     {

                         for(int r=0; r<ZZ_polynomial_int[layer_number-1][m][p].size(); r++  )
                         {
                             ZZ_polynomial_int[layer_number][j][p+check_ZZ_polynomial(interface_permu[j])].append(1);

                         }

                     }

                                                                           }

                                                                       }


                                                                   }


                                                               }
                                                               else
                                                               {
                                                                  // cout<< "-------------n+1 falied-------------" << endl;
                                                                   break;
                                                               }


                                                         }


                                                        }

                                                    if(reduced_lower[fragment][j].size()== n+1) // 若下沒n+1
                                                   {

                                                        if( (max_fragment_number) != (fragment+1) )
                                                        {

                                                            cout << " max_fragment number != fragment +1 " << endl;
                                                            cout << " max = " << max_fragment_number << " fragment = " << fragment << endl;
                                                            fragment++;

                                              normal_procedure(layer_number,fragment,max_fragment_number,reduced_upper,reduced_lower,layer_type,interface_permu);

                                                        }

                                                        else
                                                        {
                                                               cout << " finished ! "<< endl;
                                                               if(n == (reduced_upper[fragment][m].size()-1))
                                                               {
                                                                   if(ZZ_polynomial_int[layer_number-1][m].size()!=0)
                                                                   {

                                   //

                                                                        //
                                                                        if(ZZ_polynomial_int[layer_number][j].size()<ZZ_polynomial_int[layer_number-1][m].size()+check_ZZ_polynomial(interface_permu[j]) )
                                                                          {
                                                                            ZZ_polynomial_int[layer_number][j].resize(ZZ_polynomial_int[layer_number-1][m].size()+check_ZZ_polynomial(interface_permu[j]));
                                                                          }
                                                                        for(int p=0 ; p<ZZ_polynomial_int[layer_number-1][m].size();p++ )
                                                                        {

                                                                            for(int r=0; r<ZZ_polynomial_int[layer_number-1][m][p].size(); r++  )
                                                                            {
                                                                                ZZ_polynomial_int[layer_number][j][p+check_ZZ_polynomial(interface_permu[j])].append(1);

                                                                            }

                                                                        }

                                                                   }

                                                               }



                                                        }


                                                   }



                                                    else
                                                    {
                                                    cout << "up ring " << reduced_upper[fragment][m][n][0] << " " << reduced_upper[fragment][m][n][1]<<"  ";
                                                    cout << "down ring " << reduced_lower[fragment][j][n][0] <<" " << reduced_lower[fragment][j][n][1] << "  ";
                                                    cout << " ------okok------" <<endl;
                                                    cout << " problem happend here !!!  down ring + up ring" << endl;
                                                    }
                                                }

                                              else
                                               {
                                                  // cout<< "----------n falied---------" << endl;
                                                   break;
                                               }

                                          }




                                   if(reduced_lower[fragment][j][n].size()==1) // 若下的第n個元素是double bond
                                        {

                                               if(reduced_lower[fragment][j][n][0] < reduced_upper[fragment][m][n][0] ) // check是否 下bond位置 < 上ring[0]   有→continue   沒→break
                                               {
                                                   if(reduced_lower[fragment][j].size()> n+1)
                                                     {
                                                          if(reduced_lower[fragment][j][n+1].size()==2) // 若下的第n+1個元素是Ring
                                                        {

                                                               // check是否 下ring[0] 位置 > 上ring[1]       有→continue   沒→break
                                                              if(reduced_lower[fragment][j][n+1][0] > reduced_upper[fragment][m][n][1] )
                                                             {
                                                                  cout << "up ring " << reduced_upper[fragment][m][n][0] << " " << reduced_upper[fragment][m][n][1]<<"  ";
                                                                  cout << "down bond " << reduced_lower[fragment][j][n][0] << "  ";
                                                                  cout << "down ring n+1 " << reduced_lower[fragment][j][n+1][0] <<" " << reduced_lower[fragment][j][n+1][1] << "  ";
                                                                  cout << " ------okok------" <<endl;

                                                                  if( (max_fragment_number) != (fragment+1) )
                                                                  {

                                                                      cout << " max_fragment number != fragment +1 " << endl;
                                                                      cout << " max = " << max_fragment_number << " fragment = " << fragment << endl;
                                                                      fragment++;

                                                        normal_procedure(layer_number,fragment,max_fragment_number,reduced_upper,reduced_lower,layer_type,interface_permu);

                                                                  }

                                                                  else
                                                                  {
                                                                      if(n == (reduced_upper[fragment][m].size()-1))
                                                                      {
                                                                          if(ZZ_polynomial_int[layer_number-1][m].size()!=0)
                                                                          {

                  //


                    //

                    if(ZZ_polynomial_int[layer_number][j].size()<ZZ_polynomial_int[layer_number-1][m].size()+check_ZZ_polynomial(interface_permu[j]) )
                      {
                        ZZ_polynomial_int[layer_number][j].resize(ZZ_polynomial_int[layer_number-1][m].size()+check_ZZ_polynomial(interface_permu[j]));
                      }
                    for(int p=0 ; p<ZZ_polynomial_int[layer_number-1][m].size();p++ )
                    {

                        for(int r=0; r<ZZ_polynomial_int[layer_number-1][m][p].size(); r++  )
                        {
                            ZZ_polynomial_int[layer_number][j][p+check_ZZ_polynomial(interface_permu[j])].append(1);

                        }

                    }

                                                                          }
                                                                      }
                                                                  }


                                                              }
                                                              else
                                                              {
                                                                 // cout<< "-------------n+1 falied-------------" << endl;
                                                                  break;
                                                              }

                                                        }



                                                         if(reduced_lower[fragment][j][n+1].size()==1) // 若下的第n+1個元素是double bond
                                                        {
                                                            // check 是否 上ring[1] < 下bond         有→continue   沒→break
                                                              if(reduced_upper[fragment][m][n][1] < reduced_lower[fragment][j][n+1][0] )
                                                               {

                                                                  cout << "up ring " << reduced_upper[fragment][m][n][0] << " " << reduced_upper[fragment][m][n][1]<<"  ";
                                                                  cout << "down bond " << reduced_lower[fragment][j][n][0] << "  ";
                                                                  cout << "down bond n+1  " << reduced_lower[fragment][j][n+1][0] << "  ";
                                                                  cout << " ------okok------" <<endl;

                                                                  if( (max_fragment_number) != (fragment+1) )
                                                                  {

                                                                      cout << " max_fragment number != fragment +1 " << endl;
                                                                      cout << " max = " << max_fragment_number << " fragment = " << fragment << endl;
                                                                      fragment++;

                                                        normal_procedure(layer_number,fragment,max_fragment_number,reduced_upper,reduced_lower,layer_type,interface_permu);

                                                                  }

                                                                  else
                                                                  {



                                                                      if(n == (reduced_upper[fragment][m].size()-1))
                                                                      {
                                                                          if(ZZ_polynomial_int[layer_number-1][m].size()!=0)
                                                                          {
                  //


                    //

                    if(ZZ_polynomial_int[layer_number][j].size()<ZZ_polynomial_int[layer_number-1][m].size()+check_ZZ_polynomial(interface_permu[j]) )
                      {
                        ZZ_polynomial_int[layer_number][j].resize(ZZ_polynomial_int[layer_number-1][m].size()+check_ZZ_polynomial(interface_permu[j]));
                      }
                    for(int p=0 ; p<ZZ_polynomial_int[layer_number-1][m].size();p++ )
                    {

                        for(int r=0; r<ZZ_polynomial_int[layer_number-1][m][p].size(); r++  )
                        {
                            ZZ_polynomial_int[layer_number][j][p+check_ZZ_polynomial(interface_permu[j])].append(1);

                        }

                    }
                                                                          }

                                                                      }

                                                                  }


                                                              }
                                                              else
                                                              {
                                                                 // cout<< "-------------n+1 falied-------------" << endl;
                                                                  break;
                                                              }

                                                        }

                                                      }

                                                   if(reduced_lower[fragment][j].size()== n+1) // 若下沒n+1
                                                  {

                                                       if( (max_fragment_number) != (fragment+1) )
                                                       {

                                                           cout << " max_fragment number != fragment +1 " << endl;
                                                           cout << " max = " << max_fragment_number << " fragment = " << fragment << endl;
                                                           fragment++;

                                             normal_procedure(layer_number,fragment,max_fragment_number,reduced_upper,reduced_lower,layer_type,interface_permu);

                                                       }

                                                       else
                                                       {
                                                              cout << " finished ! "<< endl;

                                                              if(n == (reduced_upper[fragment][m].size()-1))
                                                              {

                                                                  if(ZZ_polynomial_int[layer_number-1][m].size()!=0)
                                                                  {
                                  //

                                                                       //

                                                                       if(ZZ_polynomial_int[layer_number][j].size()<ZZ_polynomial_int[layer_number-1][m].size()+check_ZZ_polynomial(interface_permu[j]) )
                                                                         {
                                                                           ZZ_polynomial_int[layer_number][j].resize(ZZ_polynomial_int[layer_number-1][m].size()+check_ZZ_polynomial(interface_permu[j]));
                                                                         }
                                                                       for(int p=0 ; p<ZZ_polynomial_int[layer_number-1][m].size();p++ )
                                                                       {

                                                                           for(int r=0; r<ZZ_polynomial_int[layer_number-1][m][p].size(); r++  )
                                                                           {
                                                                               ZZ_polynomial_int[layer_number][j][p+check_ZZ_polynomial(interface_permu[j])].append(1);

                                                                           }

                                                                       }

                                                                  }

                                                              }




                                                       }


                                                  }

                                                   else
                                                   {
                                                   cout << "up ring " << reduced_upper[fragment][m][n][0] << " " << reduced_upper[fragment][m][n][1]<<"  ";
                                                   cout << "down bond " << reduced_lower[fragment][j][n][0] << "  ";
                                                   cout << " ------okok------" <<endl;
                                                   cout << " problem happend here !!!  down ring + up ring" << endl;
                                                   }
                                               }
                                               else
                                               {
                                                   //cout<< "----------n falied-----------" << endl;
                                                   break;
                                               }
                                          }



                                   }



                  else   // 若上的第n個元素是double bond

                        {

                                if(reduced_lower[fragment][j][n].size()==2) // 若下的第n個元素是Ring
                                        {
                                            // check是否 下ring[1] 位置 <  上 bond 位置      有→continue   沒→break

                                             if(reduced_lower[fragment][j][n][1] < reduced_upper[fragment][m][n][0] )
                                              {



                                                 if(reduced_lower[fragment][j].size()>n+1)
                                                    {


                                                        if(reduced_lower[fragment][j][n+1].size()==2) // 若下的第n+1個元素是Ring
                                                            {

                                                                // check是否 下ring[0] 位置 > 上bond          有→continue   沒→break

                                                                  if(reduced_lower[fragment][j][n+1][0] > reduced_upper[fragment][m][n][0] )
                                                                   {
                                                                      cout << "up bond " << reduced_upper[fragment][m][n][0] <<"  ";
                                                                      cout << "down ring n+1 " << reduced_lower[fragment][j][n+1][0] <<" " << reduced_lower[fragment][j][n+1][1] << "  ";
                                                                      cout << "down ring " << reduced_lower[fragment][j][n][0] <<" " << reduced_lower[fragment][j][n][1] << "  ";
                                                                      cout << " ------okok------" <<endl;

                                                                      if( (max_fragment_number) != (fragment+1) )
                                                                      {

                                                                          cout << " max_fragment number != fragment +1 " << endl;
                                                                          cout << " max = " << max_fragment_number << " fragment = " << fragment << endl;
                                                                          fragment++;

                                                            normal_procedure(layer_number,fragment,max_fragment_number,reduced_upper,reduced_lower,layer_type,interface_permu);

                                                                      }

                                                                      else
                                                                      {

                                                                          if(n == (reduced_upper[fragment][m].size()-1))
                                                                          {
                                                                              if(ZZ_polynomial_int[layer_number-1][m].size()!=0)
                                                                              {
                      //

                        //

                        if(ZZ_polynomial_int[layer_number][j].size()<ZZ_polynomial_int[layer_number-1][m].size()+check_ZZ_polynomial(interface_permu[j]) )
                          {
                            ZZ_polynomial_int[layer_number][j].resize(ZZ_polynomial_int[layer_number-1][m].size()+check_ZZ_polynomial(interface_permu[j]));
                          }
                        for(int p=0 ; p<ZZ_polynomial_int[layer_number-1][m].size();p++ )
                        {

                            for(int r=0; r<ZZ_polynomial_int[layer_number-1][m][p].size(); r++  )
                            {
                                ZZ_polynomial_int[layer_number][j][p+check_ZZ_polynomial(interface_permu[j])].append(1);

                            }

                        }
                                                                              }

                                                                          }



                                                                      }


                                                                   }
                                                                  else
                                                                  {
                                                                     // cout<< "-------------n+1 falied-------------" << endl;
                                                                      break;
                                                                  }
                                                            }

                                                         if(reduced_lower[fragment][j][n+1].size()==1) // 若下的第n+1個元素是double bond
                                                            {
                                                                // check 是否 上bond < 下bond                   有→continue   沒→break
                                                                  if(reduced_upper[fragment][m][n][0] < reduced_lower[fragment][j][n+1][0] )
                                                                   {
                                                                      cout << "up bond " << reduced_upper[fragment][m][n][0] <<" ";
                                                                      cout << "down ring " << reduced_lower[fragment][j][n][0] <<" " << reduced_lower[fragment][j][n][1] << "  ";
                                                                      cout << "down bond n+1 " << reduced_lower[fragment][j][n+1][0];
                                                                      cout << " ----okok------" <<endl;

                                                                      if( (max_fragment_number) != (fragment+1) )
                                                                      {

                                                                          cout << " max_fragment number != fragment +1 " << endl;
                                                                          cout << " max = " << max_fragment_number << " fragment = " << fragment << endl;
                                                                          fragment++;

                                                            normal_procedure(layer_number,fragment,max_fragment_number,reduced_upper,reduced_lower,layer_type,interface_permu);

                                                                      }

                                                                      else
                                                                      {

                                                                          if(n == (reduced_upper[fragment][m].size()-1))
                                                                          {
                                                                              if(ZZ_polynomial_int[layer_number-1][m].size()!=0)
                                                                              {
                      //


                        //

                        if(ZZ_polynomial_int[layer_number][j].size()<ZZ_polynomial_int[layer_number-1][m].size()+check_ZZ_polynomial(interface_permu[j]) )
                          {
                            ZZ_polynomial_int[layer_number][j].resize(ZZ_polynomial_int[layer_number-1][m].size()+check_ZZ_polynomial(interface_permu[j]));
                          }
                        for(int p=0 ; p<ZZ_polynomial_int[layer_number-1][m].size();p++ )
                        {

                            for(int r=0; r<ZZ_polynomial_int[layer_number-1][m][p].size(); r++  )
                            {
                                ZZ_polynomial_int[layer_number][j][p+check_ZZ_polynomial(interface_permu[j])].append(1);

                            }

                        }
                                                                              }

                                                                          }

                                                                      }


                                                                   }
                                                                  else
                                                                  {
                                                                    //  cout<< "-------------n+1 falied-------------" << endl;
                                                                      break;
                                                                  }

                                                            }

                                                     }


                                                 if(reduced_lower[fragment][j].size()== n+1) // 若下沒n+1
                                                {

                                                     if( (max_fragment_number) != (fragment+1) )
                                                     {

                                                         cout << " max_fragment number != fragment +1 " << endl;
                                                         cout << " max = " << max_fragment_number << " fragment = " << fragment << endl;
                                                         fragment++;

                                           normal_procedure(layer_number,fragment,max_fragment_number,reduced_upper,reduced_lower,layer_type,interface_permu);

                                                     }

                                                     else
                                                     {
                                                            cout << " finished ! "<< endl;
                                                            if(n == (reduced_upper[fragment][m].size()-1))
                                                            {
                                                                if(ZZ_polynomial_int[layer_number-1][m].size()!=0)
                                                                {

                                //

                                                                     //

                                                                     if(ZZ_polynomial_int[layer_number][j].size()<ZZ_polynomial_int[layer_number-1][m].size()+check_ZZ_polynomial(interface_permu[j]) )
                                                                       {
                                                                         ZZ_polynomial_int[layer_number][j].resize(ZZ_polynomial_int[layer_number-1][m].size()+check_ZZ_polynomial(interface_permu[j]));
                                                                       }
                                                                     for(int p=0 ; p<ZZ_polynomial_int[layer_number-1][m].size();p++ )
                                                                     {

                                                                         for(int r=0; r<ZZ_polynomial_int[layer_number-1][m][p].size(); r++  )
                                                                         {
                                                                             ZZ_polynomial_int[layer_number][j][p+check_ZZ_polynomial(interface_permu[j])].append(1);

                                                                         }

                                                                     }
                                                                     }
                                                            }



                                                     }


                                                }

                                                else
                                                 {
                                                 cout << "up bond " << reduced_upper[fragment][m][n][0] <<"  ";
                                                 cout << "down ring " << reduced_lower[fragment][j][n][0] <<" " << reduced_lower[fragment][j][n][1] << "  ";
                                                 cout << " ------okok------" <<endl;
                                                 cout << " problem happend!! up ring + down ring" << endl;
                                                 }

                                             }
                                             else
                                             {
                                                 //cout<< "--------n falied----------" << endl;
                                                 break;
                                             }

                                        }


                                   if(reduced_lower[fragment][j][n].size()==1) // 若下的第n個元素是double bond
                                        {



                                            // check是否 下bond位置 < 上bond             有→continue   沒→break
                                             if(reduced_lower[fragment][j][n][0] < reduced_upper[fragment][m][n][0] )

                                              {

                                                 cout << "  pos check ok " << endl;
                                                 cout << " now n+1 = " << n+1 << " lower element size = " <<  reduced_lower[fragment][j].size() << endl;

                                                 if(reduced_lower[fragment][j].size()>n+1)   // 若下有n+1
                                                    {
                                                        if(reduced_lower[fragment][j][n+1].size()==2) // 若下的第n+1個元素是Ring
                                                            {

                                                                // check是否 下ring[0] 位置 > 上bond          有→continue   沒→break

                                                                  if(reduced_lower[fragment][j][n+1][0] > reduced_upper[fragment][m][n][0] )
                                                                   {
                                                                      cout << "up bond " << reduced_upper[fragment][m][n][0] <<"  ";
                                                                      cout << "down ring n+1 " << reduced_lower[fragment][j][n+1][0] <<" " << reduced_lower[fragment][j][n+1][1] << "  ";
                                                                      cout << "down bond " << reduced_lower[fragment][j][n][0]  << "  ";
                                                                      cout << " ------okok------" <<endl;

                                                                      if( (max_fragment_number) != (fragment+1) )
                                                                      {

                                                                          cout << " max_fragment number != fragment +1 " << endl;
                                                                          cout << " max = " << max_fragment_number << " fragment = " << fragment << endl;
                                                                          fragment++;

                                                            normal_procedure(layer_number,fragment,max_fragment_number,reduced_upper,reduced_lower,layer_type,interface_permu);

                                                                      }

                                                                      else
                                                                      {
                                                                          if(n == (reduced_upper[fragment][m].size()-1))
                                                                          {
                                                                              if(ZZ_polynomial_int[layer_number-1][m].size()!=0)
                                                                              {
                      //


                        //
                      if(ZZ_polynomial_int[layer_number][j].size()<ZZ_polynomial_int[layer_number-1][m].size()+check_ZZ_polynomial(interface_permu[j]) )
                        {
                          ZZ_polynomial_int[layer_number][j].resize(ZZ_polynomial_int[layer_number-1][m].size()+check_ZZ_polynomial(interface_permu[j]));
                        }
                        for(int p=0 ; p<ZZ_polynomial_int[layer_number-1][m].size();p++ )
                        {

                            for(int r=0; r<ZZ_polynomial_int[layer_number-1][m][p].size(); r++  )
                            {
                                ZZ_polynomial_int[layer_number][j][p+check_ZZ_polynomial(interface_permu[j])].append(1);

                            }

                        }
                                                                              }
                                                                          }



                                                                      }


                                                                   }
                                                                  else
                                                                  {
                                                                    //  cout<< "-------------n+1 falied-------------" << endl;
                                                                      break;
                                                                  }
                                                            }

                                                         if(reduced_lower[fragment][j][n+1].size()==1) // 若下的第n+1個元素是double bond
                                                            {
                                                                // check 是否 上bond < 下bond                   有→continue   沒→break
                                                                  if(reduced_upper[fragment][m][n][0] < reduced_lower[fragment][j][n+1][0] )
                                                                   {
                                                                      cout << "up bond " << reduced_upper[fragment][m][n][0] <<" ";
                                                                      cout << "down bond " << reduced_lower[fragment][j][n][0]  << "  ";
                                                                      cout << "down bond n+1 " << reduced_lower[fragment][j][n+1][0];
                                                                      cout << " ----okok------" <<endl;

                                                                      if( (max_fragment_number) != (fragment+1) )
                                                                      {

                                                                          cout << " max_fragment number != fragment +1 " << endl;
                                                                          cout << " max = " << max_fragment_number << " fragment = " << fragment << endl;
                                                                          fragment++;

                                                            normal_procedure(layer_number,fragment,max_fragment_number,reduced_upper,reduced_lower,layer_type,interface_permu);

                                                                      }

                                                                      else
                                                                      {
                                                                             cout << " finished ! "<< endl;
                                                                             if(n == (reduced_upper[fragment][m].size()-1))
                                                                             {
                                                                                 if(ZZ_polynomial_int[layer_number-1][m].size()!=0)
                                                                                 {
                                                 //

                                                  //
                                                  if(ZZ_polynomial_int[layer_number][j].size()<ZZ_polynomial_int[layer_number-1][m].size()+check_ZZ_polynomial(interface_permu[j]) )
                                                    {
                                                      ZZ_polynomial_int[layer_number][j].resize(ZZ_polynomial_int[layer_number-1][m].size()+check_ZZ_polynomial(interface_permu[j]));
                                                    }

                                                  for(int p=0 ; p<ZZ_polynomial_int[layer_number-1][m].size();p++ )
                                                  {

                                                      for(int r=0; r<ZZ_polynomial_int[layer_number-1][m][p].size(); r++  )
                                                      {
                                                          ZZ_polynomial_int[layer_number][j][p+check_ZZ_polynomial(interface_permu[j])].append(1);

                                                      }

                                                  }
                                                                                 }
                                                                             }





                                                                      }


                                                                   }
                                                                  else
                                                                  {
                                                                     // cout<< "-------------n+1 falied-------------" << endl;
                                                                      break;
                                                                  }

                                                            }

                                                    }

                                                 if(reduced_lower[fragment][j].size()== n+1) // 若下沒n+1
                                                {

                                                     if( (max_fragment_number) != (fragment+1) )
                                                     {

                                                         cout << " max_fragment number != fragment +1 " << endl;
                                                         cout << " max = " << max_fragment_number << " fragment = " << fragment << endl;
                                                         fragment++;

                                           normal_procedure(layer_number,fragment,max_fragment_number,reduced_upper,reduced_lower,layer_type,interface_permu);

                                                     }

                                                     else
                                                     {
                                                            cout << " finished ! "<< endl;
                                                            if(n == (reduced_upper[fragment][m].size()-1))
                                                            {
                                                                if(ZZ_polynomial_int[layer_number-1][m].size()!=0)
                                                                {
                                //

                                                                     //

                                                                     if(ZZ_polynomial_int[layer_number][j].size()<ZZ_polynomial_int[layer_number-1][m].size()+check_ZZ_polynomial(interface_permu[j]) )
                                                                       {
                                                                         ZZ_polynomial_int[layer_number][j].resize(ZZ_polynomial_int[layer_number-1][m].size()+check_ZZ_polynomial(interface_permu[j]));
                                                                       }
                                                                     for(int p=0 ; p<ZZ_polynomial_int[layer_number-1][m].size();p++ )
                                                                     {

                                                                         for(int r=0; r<ZZ_polynomial_int[layer_number-1][m][p].size(); r++  )
                                                                         {
                                                                             ZZ_polynomial_int[layer_number][j][p+check_ZZ_polynomial(interface_permu[j])].append(1);

                                                                         }

                                                                     }

                                                                }

                                                            }

                                                     }


                                                }


                                                 else
                                                 {
                                                 cout << "up bond " << reduced_upper[fragment][m][n][0] <<"  ";
                                                 cout << "down bond " << reduced_lower[fragment][j][n][0]  << "  ";
                                                 cout << " ------okok------" <<endl;
                                                 cout << " problem happend! up bond + down bond" << endl;
                                                   }


                                           } //  上double > 下 double?


                                             else
                                             {
                                                // cout<< "---------n falied--------" << endl;
                                                 break;
                                             }


                                       }  //  if 下n = double , 或 ring


                          } //  if 上n = double


                         }   //  for 上的元素 n




                          if((m+1) ==reduced_upper[fragment].size() )  // if upper finished than we can calculate the final zz at lower
                                  {
                          for( int h=0; h<reduced_lower[fragment].size();h++)
                          {
                              for(int i=0 ; i<ZZ_polynomial_int[layer_number][h].size();i++ )
                              {

                                        cout << " layer " << layer_number+1 << "  possibility " << h+1 << "power " << i << " has " << ZZ_polynomial_int[layer_number][h][i].size()<<endl;

                              }

                          }



           //  cout << " layer " << layer_number+1 << " possibility " << j+1 << " finished! ZZ = " << ZZ_polynomial[layer_number][j][0].toStdString() << endl;

                                    }



                } //  for 上的poss m

             }   //  for 下的poss j


        }  // if W.L










}



void johanna::c_recur(int k ,int n,int m, QVector<QVector<int> > list , int a ,int b)
{
   // a = 現在在第幾層

         cout << " now k = " << k << " n = " << n << " a = " << a << endl;
//         layer_permu[a][p].append(layer[a][k-1]);
            list.append(layer[a][k-1]);

          for(int c=0 ; c<layer[a][k-1].size();c++)
          {
            cout << "add" << layer[a][k-1][c] <<endl;
          }
         //         if( n>0)
         //         {
         //             for(int i=0 ; i < m-n-k-1 ; i++)
         //             {
         //                                  cout << "add " << layer[a][k-1] << endl ;
         //                                layer_permu[a][p+i+1].append(layer[a][k-1]);

         //             }

         //         }

//          int g=0;
//          cout << "at " << a << b <<  "add" << list[a][p][g] << endl;
//          g++;

         for(int i=k;i<=(m-n) && n>0;i++)
         {

              cout << "do inter crecur one time " << " i = " << i << endl;
              cout << " do k = " << i+1 << " n = " << n-1 << " a = " << a << endl;


              c_recur(i+1,n-1,m,list,a,b);
         }

         if(n==0)   //剛抓完一組  print出來
         {


                  for(int k=0 ; k<list.size() ; k++)
                  {
                    if(layer_permu[a].size() < p+1)
                    {

                         layer_permu[a].resize(p+1);


                    }

                      layer_permu[a][p].append(list[k]) ;
                  }



                  p++;




                cout << "end one  ~~~~~~~~~" << endl;
//              for(int i=0;i<list[a][k-1].size();i++)
//              {
//                   cout<< list[a][k-1][i]<<"  ";
//              }


         }


}






void johanna::combinationUtil(int arr[], int data[], int start, int end,int index, int r)
{
if (index == r)
    {
        for (int j=0; j<r; j++)
        {
       printf("%d ", data[j]);
//        cout << data[j] << "  ";

      printf("\n");
        return;
        }
    }

    for (int i=start; i<=end && end-i+1 >= r-index; i++)
    {
        data[index] = arr[i];
        combinationUtil(arr, data, i+1, end, index+1, r);
        
    }

}


int johanna::factorial(int n)
{
    int temp=1,x=1;
    for( x = 1 ; x <=n ; x++ )
    {
        temp*=x;
    }
    return temp;
}






void johanna::exportSVG(QString filename, bool compressed)
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




void johanna::mouseDoubleClickEvent(QMouseEvent *event)
{
    johanna::mouseDoubleClickEvent(event);
}


void johanna::mouseMoveEvent(QMouseEvent *event)
{
    johanna::mouseMoveEvent(event);
}
void johanna::mousePressEvent(QMouseEvent *event)
{

  johanna::mousePressEvent(event);
}


void johanna::paintEvent(QPaintEvent *e)
{
   QPainter painter(this);

   painter.setPen(Qt::green);               //指定畫筆顏色

   painter.setPen(QPen(Qt::red, 5));        //指定畫筆顏色和粗細
   painter.setBrush(Qt::red);              //指定筆刷顏色，可以想成物體的填充色
   painter.drawEllipse(100, 300, 20, 20);//指定x、y、width、height的矩形，繪製橢圓於內

 }


   void johanna::clear_all_things()
   {

       scene->clear();
       red_atom_coordinate.clear();
       blue_atom_coordinate.clear();
       spin_polynomial_blue.clear();
       spin_polynomial_red.clear();
       atom_polynomial.clear();
       m_textItems.clear();
       m_textItems2.clear();
       red_circle.clear();
       red_circle2.clear();
       blue_circle.clear();
       blue_circle2.clear();


   }


void johanna::clearText()
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
void johanna::clearText2()
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






void johanna::resizeEvent(QResizeEvent *)
{
    if (graph_item!=nullptr)
    {
//        view->ensureVisible(graph_item);
        view->centerOn(graph_item);
    }
}




