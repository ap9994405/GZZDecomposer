
#include "decomposer.h"
#include "layoutabletree.h"
#include "graphmodel.h"
#include "graphmodeltreenode.h"
#include "graphmodelgraphicsitem.h"

#include "zoomableview.h"
#include <QtWidgets>
#include <QHash>

#include "graphitemconnectingline.h"

#include "graphdecomposecommand.h"
#include "uniquetaggenerator.h"
#include "graphmodel.h"

#include <QtSvg>
#include "undoredomanager.h"

#include "GraphModelGraphicsItemMarkerToggleVistor.h"
#include "gzip_helper.h"
#include <QDebug>

Decomposer::Decomposer(UniqueTagGenerator *tagGen, QWidget *parent): QWidget(parent)
{
    //:QWidget(parent) might equal to this -> parent = parent
    m_rotateGrid = false;
    m_undoRedoManager = new UndoRedoManager();
    if ( tagGen == NULL )
    {
        m_tagGenerator = new UniqueTagGenerator();
    }
    else
    {
        m_tagGenerator = tagGen;
    }
    m_allowFragments = true;
    m_root_graph = NULL;
    m_graphtree = NULL ;
    QHBoxLayout *layout = new QHBoxLayout();
    layout->setMargin(0);
//    scene = new QGraphicsScene(-2000,-50, 4000, 8000, this);
    scene = new QGraphicsScene(this);

//    scene->addLine(-2000,0,2000,0);
//    scene->addLine(0,-2000,0,2000);


    view = new ZoomableView(scene);
    view->setMouseTracking(true);

    layout->addWidget(view);
    this->setLayout(layout);
}

Decomposer::~Decomposer()
{
    //    clear();
}

// in the following function, two getZZPolynomial is different function with different # of parameter
QString Decomposer::getZZPolynomial()
{
    if (m_nodeMapping.contains(m_root_graph))   //m_nodeMapping is a QHash<GraphModel*, GraphModelTreeNode*>
    {
        return QString("ZZ = %1" ).arg(getZZPolynomial(m_nodeMapping[m_root_graph]));   //m_nodeMapping[m_root_graph] == GraphModelTreeNode
    }
    else
    {
        return "0";
    }
}

void Decomposer::setRootGraph(GraphModel *graph)    //Graphmodel defined in graphmodel
{
    m_root_graph = graph;

    m_root_graph->prepare();
    connect(m_root_graph, SIGNAL(SelectionChanged(GraphModel*)), this, SLOT(graphSelectionChanged(GraphModel*)));
    //connect(sender, SIGNAL(signal()), receiver, SLOT(slot()));
    m_root_graph->setTag(m_tagGenerator->getTagFromModel(m_root_graph));


    GraphModelGraphicsItem *graph_item = new GraphModelGraphicsItem(m_root_graph);
    connect(graph_item, SIGNAL(tagChanged()), this, SLOT(tagChanged()));
    if (m_rotateGrid)
    {
        graph_item->setGridRotated(m_rotateGrid);   //call setGridRotated() in graph_item
    }

    connect(graph_item, SIGNAL(ZZPolynomialRequest(GraphModel*)), this, SLOT(childZZPolynomialRequest(GraphModel*)));

    scene->addItem(graph_item);
    view->centerOn(graph_item);
    GraphModelTreeNode *node = new GraphModelTreeNode(graph_item);
    m_graphtree = new LayoutableTree(node);
    m_nodeMapping.insert(m_root_graph, node);



    if (m_allowFragments)
    {
        if (graph->isDisconnected())
        {
            QList<GraphModel*> fragments = graph->getFragments();


            QListIterator<GraphModel*> fit(fragments);
            while(fit.hasNext())
            {
                addChild(graph, fit.next());
            }
        }
    }
    else
    {
        graph_item->setEnabled(true);
        if (graph->isDisconnected())
        {
            graph_item->setShowTagWhenDisconnected(true);
        }
    }


    m_graphtree->reposition();

    scene->setSceneRect(scene->itemsBoundingRect());
}

QList<GraphModel *> Decomposer::getLeafs()
{
    QList<GraphModel*> res;


    QQueue<LayoutableTreeNode*> queue;

    queue.append(m_graphtree->getRootNode());

    while(!queue.isEmpty())
    {
        LayoutableTreeNode* node = queue.first();
        queue.pop_front();
        QListIterator<LayoutableTreeNode*> it(m_graphtree->getAllChildren(node));
        if (it.hasNext())
        {
            while(it.hasNext())
            {
                queue.push_back(it.next());
            }
        }
        else
        {
            GraphModelTreeNode *gmnode = dynamic_cast<GraphModelTreeNode*>(node);
            if ( gmnode )
            {
                GraphModel* item = gmnode->getGraphicsItem()->getModel();
//                if (!item->isDead())
                res.append(item);
            }
        }
    }


    return res;
}

void Decomposer::clear()
{
    m_tagGenerator->clear();
    if (m_root_graph!=NULL)
    {
        m_root_graph = NULL;
    }
    if (m_graphtree != NULL)
    {
        delete m_graphtree;
        m_graphtree = NULL;
    }
    scene->clear();
    m_nodeMapping.clear();
    m_undoRedoManager->clear();
}

void Decomposer::setAllowFragments(bool enable)
{
    m_allowFragments = enable;
}

bool Decomposer::allowFragments()
{
    return m_allowFragments;
}

void Decomposer::exportSVG(QString filename, bool compressed)
{
    QSvgGenerator svgGen;

    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    svgGen.setOutputDevice(&buffer);


    QRectF rect = scene->itemsBoundingRect();
    QGraphicsRectItem *bg=new QGraphicsRectItem(rect.x()-50, rect.y()-50, rect.width()+100, rect.height()+100,0);
    bg->setPen(QPen(Qt::NoPen));
    bg->setBrush(QBrush(QColor("White")));
    bg->setZValue(-50);

    scene->addItem(bg);

    QRectF rr = bg->rect();
    svgGen.setTitle("ZZ Decomposition Export");
//    svgGen.setResolution(300);
    svgGen.setSize(QSize(rr.width(),rr.height()));
    svgGen.setViewBox(rr);
    QPainter painter;
    painter.begin(&svgGen);

    GraphModelGraphicsItemMarkerToggleVistor vistor;
    vistor.setShowMarker(true);
    this->m_graphtree->visitTreeNodes(&vistor);


    scene->render(&painter,rr,rr);

    painter.end();

    vistor.setShowMarker(false);
    this->m_graphtree->visitTreeNodes(&vistor);

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

void Decomposer::setGridRotate(bool rotate)
{   
    m_rotateGrid = rotate;
    QListIterator<GraphModelTreeNode*> it(m_nodeMapping.values());
    while(it.hasNext())
    {
        GraphModelGraphicsItem* item = it.next()->getGraphicsItem();
        item->setGridRotated(m_rotateGrid);
    }
    if (!m_nodeMapping.isEmpty())
    {
        m_graphtree->reposition();
    }
}

void Decomposer::reposition()
{
    m_graphtree->reposition();
}

void Decomposer::graphSelectionChanged(GraphModel *model)
{
//    qDebug() << model->isBondSelected() ;
//    if (model->isBondSelected())
//    {
//        qDebug() << model->getSelectedBond().toString();
//    }

    if (  model->isBondSelected() )
    {
        ICommand* command = new GraphDecomposeCommand(this, model);
        command->Execute();
    }
    else
    {
        QList<LayoutableTreeNode*> all_children = m_graphtree->getAllChildren(m_nodeMapping[model]);
        QListIterator<LayoutableTreeNode*> it(all_children);
        while(it.hasNext())
        {
            LayoutableTreeNode* item = it.next();
            m_graphtree->deleteChild(m_nodeMapping[model],item);
            GraphModelTreeNode* node = dynamic_cast<GraphModelTreeNode*>(item);
            if (node && m_nodeMapping.contains(node->getModel()))
            {
                m_nodeMapping.remove(node->getModel());
            }
            delete item;
        }

    }

    m_graphtree->reposition();

//    qDebug() << scene->itemsBoundingRect();
    scene->setSceneRect(scene->itemsBoundingRect().adjusted(-100,-100,200,200));
    view->centerOn(dynamic_cast<GraphModelTreeNode*>(m_nodeMapping[model])->getGraphicsItem());

}

void Decomposer::addChild(GraphModel *parent, GraphModel *child)
{

    child->setTag(m_tagGenerator->getTagFromModel(child));
    connect(child, SIGNAL(SelectionChanged(GraphModel*)), this, SLOT(graphSelectionChanged(GraphModel*)));
    GraphModelGraphicsItem *graph_item = new GraphModelGraphicsItem(child);   
    // qDebug() << "setGridRotate1";
    if (m_rotateGrid)
    {
        // qDebug() << "setGridRotate1_2";  //never see this output
        graph_item->setGridRotated(m_rotateGrid);
    }
    connect(graph_item, SIGNAL(tagChanged()), this, SLOT(tagChanged()));
    connect(graph_item, SIGNAL(ZZPolynomialRequest(GraphModel*)), this, SLOT(childZZPolynomialRequest(GraphModel*)));


    if (!allowFragments())
    {
        graph_item->setEnabled(true);
        if (child->isDisconnected())
        {
            graph_item->setShowTagWhenDisconnected(true);
        }
    }

    scene->addItem(graph_item);
    GraphModelTreeNode *node = new GraphModelTreeNode(graph_item);  //lost

    new GraphItemConnectingLine(m_nodeMapping[parent], node);

    m_graphtree->appendChild(m_nodeMapping[parent], node);
    m_nodeMapping[child]=node;
}

void Decomposer::tagChanged()
{
    m_graphtree->reposition();
}

QString Decomposer::getZZPolynomial(GraphModelTreeNode *node)   //m_nodeMapping[m_root_graph] == GraphModelTreeNode
{
    GraphModel* model = node->getModel();   
    QStringList list;
    if ( model->isDead())
    {
        return QString("0");
    }
    else if ( model->isFinished())
    {
        if ( model->getType() == GraphModel::Ring)  //getType in graphmodel
        {
            return QString("x");
        }
        else if ( model->getType() == GraphModel::BisRing)
        {
            return QString("y");
        }
        else
        {
            return QString("1");
        }
    }


    if (node->hasChildren())
    {
        QListIterator<GraphModelTreeNode*> it(node->getAllChildren());
        while(it.hasNext())
        {
            GraphModelTreeNode* child = it.next();
            QString tmp = getZZPolynomial(child);
            if ( tmp != "0")
            {
                list << tmp;
            }
        }
        QString prefix = "";
        if (model->getType() == GraphModel::Ring)
            prefix = "x*";
        if (model->getType() == GraphModel::BisRing)
            prefix = "y*";
        if (!list.isEmpty())
        {
            QString tmp;
            if (model->isDisconnected())
            {
                tmp = list.join(" * ");
            }
            else
            {
                tmp = list.join(" + ");
                if (list.size() > 1)
                    tmp = "( " + tmp + " )";
            }
            tmp = prefix + tmp ;
            return tmp;
        }
        else
        {
            return "0";
        }
    }
    else
    {
        if ( model->getType() == GraphModel::Ring)
        {
            return "x*" + model->getFullTag();
        }
        else if ( model->getType() == GraphModel::BisRing)
        {
            return "y*" + model->getFullTag();
        } 
        else
        {
            return model->getFullTag();
        }
    }
}

void Decomposer::childZZPolynomialRequest(GraphModel *model)
{
    emit ZZPolynomialRequest(model);
}