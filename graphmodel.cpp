#include "graphmodel.h"
#include <QHash>
#include <QQueue>
#include <QPolygon>
#include <QBitArray>
#include <QSet>
#include <array>
#include "utils.h"
#include <iostream>
#include <QDebug>

using namespace std;

inline uint qHash(const QPoint &key)
{
    QString str = QString("(%1,%2)").arg(key.x()).arg(key.y());
    QString hkey = QString(QCryptographicHash::hash(str.toStdString().c_str(),QCryptographicHash::Md5).toHex());
    return qHash(hkey);
}



bool GraphModel::isDisconnected()
{
    return m_isDisconnected;
}

GraphModel::DecompositionType GraphModel::getType()
{
    return m_type;
}

const Polynomial<long long> &GraphModel::getPoly() const
{
    //something happened when decompose
    // qDebug() << "test";
    return m_poly;
}

void GraphModel::setPoly(const Polynomial<long long> &poly)
{
    //nothing happened when decompose
    m_poly = poly;
    // qDebug() << poly.toString2(); //always the same 
    // qDebug() << m_poly.toString2(); //always the same 

    emit PolynomialChanged(this);
}

QList<GraphModel *> GraphModel::getDaughters(EdgeModel edge)
{
    QList<GraphModel *> res;
    res.append(getNoBondDaughter(edge));
    res.append(getNoAtomsDaughter(edge));
    res.append(getNoRingDaughter(edge));  
    res.append(getNoBisRingDaughter(edge));  
    return res;
}

void GraphModel::selectBond(EdgeModel edge)
{
    m_isBondSelected = true;
    m_selectedBond = edge;
    emit SelectionChanged(this);    //emit a signal
//    emit BondSelected(this, edge);
}

void GraphModel::unselectBond()
{
//    emit BondUnselected(this, edge);
    bool oldse = m_isBondSelected;
    m_isBondSelected = false;
    if (oldse)
        emit SelectionChanged(this);
}

bool GraphModel::isBondSelected()
{
    return m_isBondSelected;
}

EdgeModel GraphModel::getSelectedBond()
{
    return m_selectedBond;
}

bool GraphModel::isDead()
{
    return m_isDead;
}

bool GraphModel::isEmpty()
{
    return (m_edges.isEmpty() && m_hidden_edges.isEmpty());
}

bool GraphModel::isFinished()
{
    return m_isFinished;
}

QList<EdgeModel> GraphModel::getAllEdges() const
{
    return m_edges + m_hidden_edges;
}

const QList<EdgeModel>& GraphModel::getEdges() const
{
    return m_edges;
}

const QList<EdgeModel> &GraphModel::getHiddenEdges()
{
    return m_hidden_edges;
}


GraphModel::GraphModel(const QList<EdgeModel> &edges, const QList<EdgeModel> &hiddenEdges, const GraphModel *modelParent,
                       GraphModel::DecompositionType type, QObject *parent):QObject(parent), m_neighborlist(edges, hiddenEdges)
{
    m_modelParent = modelParent;
    m_tag = "";
    m_customTag = "";
    m_edges = edges;    //exist edges
    m_hidden_edges = hiddenEdges;   //removed edges
    m_isFinished = (edges.isEmpty() && !hiddenEdges.isEmpty());
    m_isDisconnected = false;
    m_isBondSelected = false;
    m_isDead = false;

    m_poly.addTerm(1,0,0);
    if ( modelParent != NULL)
    {   
        m_doublebonds += modelParent->m_doublebonds;
        m_rings += modelParent->m_rings;
        m_rings += modelParent->m_bisrings;
        m_poly = modelParent->m_poly;
    }
    m_type = type;

    if (m_type == Ring)
    {   
        m_poly.multiplyTerm(1,1,0);
    }
    if (m_type == BisRing)
    {
        m_poly.multiplyTerm(1,0,1);
    }
    if (m_neighborlist.numOfAtoms() % 2 == 1)
        m_isDead = true;
}

GraphModel::~GraphModel()
{
//    qDebug() << "GraphModel::~GraphModel";
}
void GraphModel::cutDanglingBonds()
{
    bool cutAny = false;
    QHash<QPoint, int> count;
    for(int i=0; i<m_edges.size();++i)
    {
        count[m_edges[i].startPoint()] += 1;
        count[m_edges[i].endPoint()] += 1;
    }
    QHashIterator<QPoint, int> it(count);   //it.key() == QPoint, it.value() == int
    QList<QPoint> alone_atoms;
    QList<EdgeModel> alone_bonds;
    while(it.hasNext())
    {
        it.next();
        if (it.value() == 1)    //maybe it.value is # of neighbors
        {
            alone_atoms.append(it.key());
        }

    }
    if (alone_atoms.size() > 0 )
    {      
        for(int i=0; i<m_edges.size();++i)
        {
            for(int j=0; j<alone_atoms.size();++j)
            {
                if (m_edges[i].startPoint() == alone_atoms[j] ||
                       m_edges[i].endPoint() == alone_atoms[j] )
                {
                    alone_bonds.append(m_edges[i]);
                }
            }
        }

        for(int i=0; i<alone_bonds.size();++i)
        {
            if (m_neighborlist.isAtomAlive(alone_bonds[i].startPoint()) &&
                m_neighborlist.isAtomAlive(alone_bonds[i].endPoint()))
            {
                removeAtoms(alone_bonds[i],this->m_edges, this->m_hidden_edges);
                addDoubleBond(alone_bonds[i]);
                m_neighborlist.removeAtom(alone_bonds[i].startPoint());
                m_neighborlist.removeAtom(alone_bonds[i].endPoint());
                cutAny = true;
            }
        }
    }
    if (cutAny)
    {
        cutDanglingBonds();
    }
}


void GraphModel::removeAtoms(const EdgeModel& edge, QList<EdgeModel> &alive_edges, QList<EdgeModel> &dead_edges)
{
    QList<EdgeModel> new_model;
    for(int i=0; i<alive_edges.size(); ++i)
    {
        if ( alive_edges[i].startPoint() == edge.startPoint() || alive_edges[i].startPoint() == edge.endPoint())
        {
            if (!dead_edges.contains(alive_edges[i]))
                dead_edges.append(alive_edges[i]);
            continue;
        }
        else if ( alive_edges[i].endPoint() == edge.startPoint() || alive_edges[i].endPoint() == edge.endPoint())
        {
            if (!dead_edges.contains(alive_edges[i]))
                dead_edges.append(alive_edges[i]);
            continue;
        }
        else
        {
            new_model.append(alive_edges[i]);
        }
    }
    alive_edges = new_model;
//    this->m_neighborlist.removeAtom(edge.startPoint());
//    this->m_neighborlist.removeAtom(edge.endPoint());
}
QList<GraphModel*> GraphModel::split(const QVector<QList<EdgeModel> >& parts)
{
    QList<GraphModel*> res;
    if (parts.size() > 1)
    {
        m_isDisconnected = true;
        for(int i=0; i<parts.size();++i)
        {
            QList<EdgeModel> remained_edges = m_hidden_edges;
            for(int j=0; j<m_edges.size();++j)
            {
                if (!parts[i].contains(m_edges[j]))
                {
                    remained_edges.append(m_edges[j]);
                }
            }
            GraphModel* newModel = new GraphModel(parts[i], remained_edges, this, GraphModel::Fragment, 0);
            QSet<QPoint> atomPos;
            for(int j=0; j< newModel->getEdges().size();++j)
            {
                EdgeModel edge = newModel->getEdges().at(j);
                atomPos.insert(edge.startPoint());
                atomPos.insert(edge.endPoint());
            }
            if (atomPos.size() % 2 != 0)
            {
                newModel->setDead(true);
            }
            res.append(newModel);
        }
    }
    return res;
}
QVector<QList<EdgeModel> > GraphModel::checkIfDisconnected(QList<EdgeModel> edges)
{
    QVector<QList<EdgeModel> > res;
    if (edges.size() == 0)
    {
        res.append(edges);
        return res;
    }

    QList<EdgeModel> part1;
    QList<EdgeModel> part2;
    QVector<QList<int> > neighborlist(edges.size());

    for(int i=0; i<edges.size();++i)
    {
        for(int j=0; j<i; ++j)
        {
            if (edges[i].connected(edges[j]))
            {
                neighborlist[i].append(j);
                neighborlist[j].append(i);
            }
        }
    }
    QBitArray visited(edges.size());
    QQueue<int> queue;
    queue.append(0);
    while(!queue.isEmpty())
    {
        int cur = queue.first();
        queue.pop_front();
        if ( visited[cur] == true)
        {
            continue;
        }
        visited.setBit(cur,true);
        QListIterator<int> it(neighborlist[cur]);
        while(it.hasNext())
        {
            queue.append(it.next());
        }
    }
    if (visited.count(false) > 0)
    {
        for(int i=0; i<visited.size();++i)
        {
            if (visited[i])
            {
                part1.append(edges[i]);
            }
            else
            {
                part2.append(edges[i]);
            }
        }
        res.append(part1);
        res += checkIfDisconnected(part2);
    }
    else
    {
        res.append(edges);
    }
    return res;
}
void GraphModel::addDoubleBond(const EdgeModel &line)
{
    m_doublebonds.append(line);
}
GraphModel *GraphModel::getNoBondDaughter(EdgeModel edge)
{
    QList<EdgeModel> model = this->m_edges;
    QList<EdgeModel> hidden = this->m_hidden_edges;
    int index = model.indexOf(edge);
    if (index != -1)
    {
        hidden.append(model[index]);
        model.removeAt(index);
    }
    return new GraphModel(model, hidden, this, GraphModel::Single, 0);
}

GraphModel *GraphModel::getNoAtomsDaughter(EdgeModel edge)
{
    QList<EdgeModel> all_edges = this->m_edges;
    QList<EdgeModel> hidden_edges = this->m_hidden_edges;
    removeAtoms(edge, all_edges, hidden_edges);
    GraphModel* gm_child = new GraphModel(all_edges, hidden_edges, this, GraphModel::Double, 0);
    gm_child->addDoubleBond(edge);
    return gm_child;
}

QList<GraphModel *> GraphModel::getNoRingDaughter(EdgeModel edge)
{
    QList<GraphModel*> rings;
    QList<QList<EdgeModel> > pathes = getRingEdges(edge);
    // qDebug() << "use getNoRingDaughter1";
    for(int i=0; i<pathes.size();++i)
    {
        QList<EdgeModel> all_edges = this->m_edges;
        QList<EdgeModel> removed_edges = this->m_hidden_edges;
        for(int j=0; j<pathes[i].size();++j)
        {
            removeAtoms(pathes[i][j],all_edges,removed_edges);
        }
        GraphModel* gm_child = new GraphModel(all_edges,removed_edges,this,GraphModel::Ring, 0);
        gm_child->addRing(pathes[i]);
        rings.append(gm_child);
    }
    return rings;
}

QList<GraphModel *> GraphModel::getNoBisRingDaughter(EdgeModel edge)
{
    QList<GraphModel*> bisrings;
    QList<QList<EdgeModel> > pathes = getBisRingEdges(edge);// change to getBisringEdge(edge)
    for(int i=0; i<pathes.size();++i)
    {
        QList<EdgeModel> all_edges = this->m_edges;
        QList<EdgeModel> removed_edges = this->m_hidden_edges;
        for(int j=0; j<pathes[i].size();++j)
        {
            removeAtoms(pathes[i][j],all_edges,removed_edges);
        }
        GraphModel* gm_child = new GraphModel(all_edges,removed_edges,this,GraphModel::BisRing, 0);
        gm_child->addBisRing(pathes[i]); //find how to addbisRing
        bisrings.append(gm_child);
    }
    return bisrings;
}

QList<QList<EdgeModel> > GraphModel::getRingEdges(EdgeModel edge)
{
    QList<QList<EdgeModel> > res;
    QSet<EdgeModel> all_edges;
    for(int i=0; i<m_edges.size();++i)
    {
        all_edges.insert(m_edges[i]);
    }
    QList<QPolygon> pathes;


    QPolygon path;
    path << QPoint(-1,0) <<  QPoint(-1,-1) << QPoint(0,-1)<< QPoint(1,0)<< QPoint(1,1)<< QPoint(0,1) ;
    pathes.append(path);
    path.clear();
    path << QPoint(0, -1) <<  QPoint(1,0) << QPoint(1,1)<< QPoint(0,1)<< QPoint(-1,0)<< QPoint(-1,-1) ;
    pathes.append(path);
    path.clear();
    path << QPoint(1,1) <<  QPoint(0,1) << QPoint(-1,0)<< QPoint(-1,-1)<< QPoint(0,-1)<< QPoint(1,0) ;
    pathes.append(path);
    path.clear();
    path << QPoint(-1,-1) <<  QPoint(0,-1) << QPoint(1,0)<< QPoint(1,1)<< QPoint(0,1)<< QPoint(-1,0) ;
    pathes.append(path);
    path.clear();
    path << QPoint(1,0) <<  QPoint(1,1) << QPoint(0,1)<< QPoint(-1,0)<< QPoint(-1,-1)<< QPoint(0,-1) ;
    pathes.append(path);
    path.clear();
    path << QPoint(0,1) <<  QPoint(-1,0) << QPoint(-1,-1)<< QPoint(0,-1)<< QPoint(1,0)<< QPoint(1,1) ;
    pathes.append(path);
    path.clear();

    QList<EdgeModel> tmpPath;
    for(int i=0; i<pathes.size();++i)
    {
        EdgeModel curEdge = edge;
        bool find = true;
        QPolygon curPath = pathes[i];
        tmpPath.clear();
        for(int j=0; j<curPath.size();++j)
        {
            //defalt of stratPoint and EndPoint are QPoint(0,0)
            curEdge.setEndPoint(curEdge.startPoint()+curPath.point(j));
            //all_edges is a set of EdgeModel
            if (!all_edges.contains(curEdge))   //if all_edges did not include curEdge then break
            {
                find = false;
                break;
            }
            tmpPath.append(curEdge);
            curEdge.setStartPoint(curEdge.endPoint());
        }
        if (find)
        {
            if (tmpPath.contains(edge))
            {   
                // qDebug() << pathes[i];
                res.append(tmpPath);
            }
        }
    }
    if (res.size() > 2)
    {
        qDebug() << "Something is fucking wrong";
    }
    return res;
}

QList<QList<EdgeModel> > GraphModel::getBisRingEdges(EdgeModel edge)
{
    QList<QList<EdgeModel> > res;
    QSet<EdgeModel> all_edges;
    for(int i=0; i<m_edges.size();++i)
    {
        all_edges.insert(m_edges[i]);
    }
    QList<QPolygon> pathes;


    QPolygon path;
    QVector<QPoint> shifts = {QPoint(0,1), QPoint(-1,0),QPoint(-1,-1), QPoint(0,-1), QPoint(1,0),
                              QPoint(0,-1), QPoint(1,0), QPoint(1,1), QPoint(0,1), QPoint(-1,0)};
    for (int i = 0; i < shifts.size(); ++i) {   //this part creat most four daughters
        path.clear();
        for (int j = 0; j < shifts.size(); ++j) {
            path << shifts[(i + j) % shifts.size()];
        }
        pathes.append(path);
    }

    shifts = {QPoint(-1,-1), QPoint(-1,0), QPoint(0,1), QPoint(1,1), QPoint(0,1),
              QPoint(1,1), QPoint(1,0), QPoint(0,-1), QPoint(-1,-1), QPoint(0,-1)};
    for (int i = 0; i < shifts.size(); ++i) {   //this part creat most four daughters
        path.clear();
        for (int j = 0; j < shifts.size(); ++j) {
            path << shifts[(i + j) % shifts.size()];
        }
        pathes.append(path);
    }

    shifts = {QPoint(-1,0), QPoint(-1,-1), QPoint(0,-1), QPoint(1,0), QPoint(1,1),
              QPoint(1,0), QPoint(1,1), QPoint(0,1), QPoint(-1,0), QPoint(-1,-1)};
    for (int i = 0; i < shifts.size(); ++i) {   //this part creat most three daughters
        path.clear();
        for (int j = 0; j < shifts.size(); ++j) {
            path << shifts[(i + j) % shifts.size()];
        }
        pathes.append(path);
    }
    path.clear();
    //still lost bisring for twohexagnol
    QList<EdgeModel> tmpPath;

    for(int i=0; i<pathes.size();++i)
    {
        EdgeModel curEdge = edge;
        // QPoint InitialPoint = edge.startPoint();
        bool find = true;
        QPolygon curPath = pathes[i];
        tmpPath.clear();
        for(int j=0; j<curPath.size();++j)
        {
            //defalt of seratPoint and EndPoint are QPoint(0,0)
            curEdge.setEndPoint(curEdge.startPoint()+curPath.point(j));
            //all_edges is a set of EdgeModel
            if (!all_edges.contains(curEdge))   //if all_edges did not include curEdge then break
            {
                find = false;
                break;
            }
            tmpPath.append(curEdge);
            curEdge.setStartPoint(curEdge.endPoint());
        }
        if (find)//|| curEdge.endPoint() == InitialPoint
        {
            if (tmpPath.contains(edge))
            {
                // qDebug() << pathes[i];
                res.append(tmpPath);
            }
            else
            {
                QPointF edge_center,ring_centet;
                edge_center = (edge.startPoint()+edge.endPoint())*5;
                for(int j=0; j<tmpPath.size();++j)
                {   
                    ring_centet += tmpPath[j].startPoint();
                }
                if (edge_center == ring_centet)
                {
                    res.append(tmpPath);
                }

            }
        }
    }
    return res;
}

// getAllRings() use in ZZAromaticityCalculatorPanel.cpp
// QList<QList<EdgeModel> > GraphModel::getAllRings() const
// {
//     QList<QList<EdgeModel> > res;
//     QSet<EdgeModel> all_edges;
//     for(int i=0; i<m_edges.size();++i)
//     {
//         all_edges.insert(m_edges[i]);
//     }
//     QList<QPolygon> pathes;


//     QPolygon path;
//     path << QPoint(0,-1) <<  QPoint(-1,-1) << QPoint(-1,0)<< QPoint(0,1)<< QPoint(1,1)<< QPoint(1,0) ;
// //    path << QPoint(-1,0) <<  QPoint(-1,-1) << QPoint(0,-1)<< QPoint(1,0)<< QPoint(1,1)<< QPoint(0,1) ;
//     pathes.append(path);
//     path.clear();
// //    path << QPoint(0, -1) <<  QPoint(1,0) << QPoint(1,1)<< QPoint(0,1)<< QPoint(-1,0)<< QPoint(-1,-1) ;
//     path << QPoint(1,1) << QPoint(1,0)<< QPoint(0,-1)<< QPoint(-1,-1)<< QPoint(-1,0) << QPoint(0,1) ;
//     pathes.append(path);
//     path.clear();
// //    path << QPoint(1,1) <<  QPoint(0,1) << QPoint(-1,0)<< QPoint(-1,-1)<< QPoint(0,-1)<< QPoint(1,0) ;
//     path << QPoint(-1,0)<< QPoint(0,1)<< QPoint(1,1)<< QPoint(1,0) << QPoint(0,-1) <<  QPoint(-1,-1) ;
//     pathes.append(path);
//     path.clear();
// //    path << QPoint(-1,-1) <<  QPoint(0,-1) << QPoint(1,0)<< QPoint(1,1)<< QPoint(0,1)<< QPoint(-1,0) ;
//     path << QPoint(-1,-1) << QPoint(-1,0)<< QPoint(0,1)<< QPoint(1,1)<< QPoint(1,0) << QPoint(0,-1) ;
//     pathes.append(path);
//     path.clear();
// //    path << QPoint(1,0) <<  QPoint(1,1) << QPoint(0,1)<< QPoint(-1,0)<< QPoint(-1,-1)<< QPoint(0,-1) ;
//     path << QPoint(0,1) << QPoint(1,1) << QPoint(1,0)<< QPoint(0,-1)<< QPoint(-1,-1)<< QPoint(-1,0) ;
//     pathes.append(path);
//     path.clear();
// //    path << QPoint(0,1) <<  QPoint(-1,0) << QPoint(-1,-1)<< QPoint(0,-1)<< QPoint(1,0)<< QPoint(1,1) ;
//     path << QPoint(1,0) << QPoint(0,-1) <<  QPoint(-1,-1) << QPoint(-1,0)<< QPoint(0,1)<< QPoint(1,1) ;
//     pathes.append(path);
//     path.clear();

//     QList<EdgeModel> tmpPath;
//     QSet<QPoint> ringCenters;

//     QSetIterator<EdgeModel> it(all_edges);
//     while(it.hasNext())
//     {
//         EdgeModel edge = it.next();
//         for(int i=0; i<pathes.size();++i)
//         {
//             EdgeModel curEdge = edge;
//             bool find = true;
//             QPolygon curPath = pathes[i];
//             curEdge.setStartPoint(curEdge.endPoint());
//             tmpPath.clear();
//             for(int j=0; j<curPath.size();++j)
//             {

//                 curEdge.setEndPoint(curEdge.startPoint()+curPath.point(j));
//                 if (!all_edges.contains(curEdge))
//                 {
//                     EdgeModel revEdge(curEdge.endPoint(), curEdge.startPoint());
//                     if (!all_edges.contains(revEdge))
//                     {
//                         find = false;
//                         break;
//                     }
//                 }
//                 tmpPath.append(curEdge);
//                 curEdge.setStartPoint(curEdge.endPoint());
//             }
//             if (find)
//             {
//                 if (tmpPath.contains(edge))
//                 {
//                     QSet<QPoint> points;
//                     for(int i=0; i<tmpPath.size();++i)
//                     {
//                         points.insert(tmpPath[i].startPoint());
//                         points.insert(tmpPath[i].endPoint());
//                     }
//                     QSetIterator<QPoint> it(points);
//                     QPoint cm = QPoint(0,0);
//                     while(it.hasNext())
//                     {
//                         QPoint p = it.next();
//                         cm += p;
//                     }
//                     cm /= points.size();
//                     if (!ringCenters.contains(cm))
//                     {
//                         res.append(tmpPath);
//                         ringCenters.insert(cm);
//                     }
//                 }
//             }
//         }
//     }

//     return res;
// }


void GraphModel::addRing(const QList<EdgeModel>& bonds)
{
    if ( bonds.size() != 6 )
        return ;
    m_rings.append(bonds);
}
void GraphModel::addBisRing(const QList<EdgeModel>& bonds)
{
    if ( bonds.size() != 10 )
        return ;
    m_rings.append(bonds);
    // m_bisrings.append(bonds);
}

const QList<EdgeModel> &GraphModel::getDoubleBonds() const
{
    return m_doublebonds;
}

const QList<QList<EdgeModel> > &GraphModel::getRings() const
{
    return m_rings;
}

const QList<QList<EdgeModel> > &GraphModel::getBisRings() const
{
    return m_bisrings;
}

QList<GraphModel *> GraphModel::getFragments()
{
    return split(m_parts);
}

bool GraphModel::hasCustomTag()
{
    return !m_customTag.isEmpty();
}

void GraphModel::setTag(const QString& tag)
{
    m_tag = tag;
}

void GraphModel::setCustomTag(const QString &tag)
{
    m_customTag = tag;
    emit TagChanged(this);
}

QString GraphModel::getTag()
{
    return m_tag;
}

QString GraphModel::getCustomTag()
{
    return m_customTag;
}

QString GraphModel::getFullTag()
{
    if (hasCustomTag())
    {
        return m_customTag;
    }
    else
    {
        return m_tag;
    }
}

// const GraphModel * GraphModel::getModelParent()
// {
//     return m_modelParent;
// }

const NeightborList &GraphModel::getNeighborList() const
{
    return m_neighborlist;
}

void GraphModel::clearLink()
{
    m_neighborlist.clearLink();
}

bool GraphModel::addLink(const QList<QPair<int, int> > &links)
{
    return m_neighborlist.addLink(links);
}

QString GraphModel::getZZInput(bool connections, bool hydrogens) const
{
    QStringList input;

    QPointF cm(0.0,0.0);


    QVector<QPointF> final_points(this->m_neighborlist.numOfAtoms());
    QMap<int, int> final_mapping;
    QHashIterator<QPoint, int> it(this->m_neighborlist.mapping());
    // QHash<Key, Value>
    QHash<QPoint, QPointF> l_hydrogens;

    int final_index = 0;

    const std::array<QPoint, 3> vectors_opbenz = {{{-1,0}, {0,-1}, {1,1}}};
    const std::array<QPoint, 3> vectors_benz = {{{0,1}, {1,0}, {-1,-1}}};

    while(it.hasNext())
    {
        it.next();
        if (!this->m_neighborlist.isAtomAlive(it.key()))
            continue;

        int num_h = 0;
        for(int i=0; i<3; ++i)
        {
            bool benz = false;
            QPoint pot = it.key();
            QPoint vec;
            int to = pot.x() + pot.y();
            if (to % 3 == 1)
            {
                benz = true;
            }
            else if (to % 3 == 0)
            {
                return "";
            }

            if (benz)
                vec = vectors_benz[i];
            else
                vec= vectors_opbenz[i];
            pot += vec;
            if (!this->m_neighborlist.isAtomAlive(pot))
            {
                QPointF hydro_coord = vertexXY2XY(it.key(),1.4) + vertexXY2XY(vec, 1.0);
                l_hydrogens.insert(pot, hydro_coord);
                num_h ++;
            }
        }
        if (hydrogens && (num_h != (3- this->m_neighborlist.getNeighborCount(it.key()))))
        {
            return "";
        }


        QPointF p =  vertexXY2XY(it.key(),1.4); // vertexXY2XY(QPoint,bondlength)
        int index = it.value();

        final_mapping[index] = final_index;
        final_points[final_index] = p;
        ++final_index;
        cm += p;

    }
    cm /= static_cast<double>(final_points.size());


    if (hydrogens)
    {
        input.append(QString("%1").arg(final_points.size() + l_hydrogens.size() ));
    }
    else
    {
        input.append(QString("%1").arg(final_points.size()));
    }
    input.append("");

    QVectorIterator<QPointF> it3(final_points);
    while(it3.hasNext())
    {
        QPointF p = it3.next()-cm;
        input.append(QString("C %1 %2 0.000000").arg(p.x(),0,'f',6).arg(p.y(),0,'f',6));
    }
    if (hydrogens)
    {
        QHashIterator<QPoint, QPointF> hit(l_hydrogens);
        while(hit.hasNext())
        {
            hit.next();
            QPointF p = hit.value()-cm;
            input.append(QString("H %1 %2 0.000000").arg(p.x(),0,'f',6).arg(p.y(),0,'f',6));
        }
    }


    if (connections)
    {
        QList<QPair<int, int> > conns = m_neighborlist.getAllConnections();
        input.append(QString::number(conns.size()));
        for(int i=0; i<conns.size();++i)
        {
            input.append(QString("%1 %2").arg(final_mapping[conns[i].first]+1)
                    .arg(final_mapping[conns[i].second]+1));
        }
    }
    return input.join("\n");
}

void GraphModel::setDead(bool isDead)
{
    if (m_isDead != isDead)
    {
        m_isDead = isDead;
        emit StateChanged(this);
    }
}

void GraphModel::prepare()
{
    cutDanglingBonds();
    if (m_neighborlist.numOfAtoms() == 0)
    {
        m_isFinished = true;
    }
    if (m_neighborlist.hasIsolatedAtom())
        m_isDead = true;

    if (!m_isDead || m_isFinished)
    {
        m_parts = checkIfDisconnected(m_edges);
        if (m_parts.size()> 1)
        {
            m_isDisconnected = true;
        }
    }
}








