#include "neightborlist.h"
#include <QSet>
#include <QPoint>
#include <QDebug>
#include <QStringList>
#include <algorithm>
#include <iostream>
using namespace std;

inline uint qHash(const QPoint &key)
{
    QString str = QString("(%1,%2)").arg(key.x()).arg(key.y());
    QString hkey = QString(QCryptographicHash::hash(str.toStdString().c_str(),QCryptographicHash::Md5).toHex());
    return qHash(hkey);
}
NeightborList::NeightborList(const QList<EdgeModel>& edges, const QList<EdgeModel> &hidden_edges)
{
    QSet<QPoint> atoms;
    for(int i=0; i<edges.size();++i)
    {
        atoms.insert(edges[i].startPoint());
        atoms.insert(edges[i].endPoint());
    }

    QSet<QPoint> hidden_atoms;
    for(int i=0; i<hidden_edges.size();++i)
    {
        hidden_atoms.insert(hidden_edges[i].startPoint());
        hidden_atoms.insert(hidden_edges[i].endPoint());
    }

    QSet<QPoint> all_atoms = atoms + hidden_atoms;

    QList<QPoint> atom_list = all_atoms.toList();

    std::sort(atom_list.begin(), atom_list.end(), []
              (const QPoint& a, const QPoint& b) -> bool
        {
            if (a.y() != b.y())
            {
                return a.y() < b.y();
            }
            else
            {
                return a.x() < b.x();
            }
        }
    );

    for(int i = 0; i< atom_list.size(); ++i)
    {
        m_mapping.insert(atom_list[i], i);
    }

    m_neighborlist.resize(atom_list.size());
    m_atomAlive.resize(atom_list.size());

    m_atomAlive.fill(false);
    QSetIterator<QPoint> it(atoms);

    while(it.hasNext())
    {
        m_atomAlive[m_mapping[it.next()]] = true;
    }

    for(int i=0; i<edges.size();++i)
    {
        int be = m_mapping[edges[i].startPoint()];
        int en = m_mapping[edges[i].endPoint()];
        m_neighborlist[be].append(en);
        m_neighborlist[en].append(be);
    }


    for (int i=0 ; i<m_mapping.size() ; i++)
    {
        red_atom.append(true) ;
    }


    for(int i=0 ; i<m_neighborlist.size();i++)
    {
        if(red_atom[i] == true)
        {
          for (int j=0 ; j<m_neighborlist[i].size();j++)
           {
                     red_atom[m_neighborlist[i][j]] = false ;
           }

        }
    }


//    for(int i=0 ; i<red_atom.size() ; i++)
//    {
//        cout << "atom " << i << "=" << red_atom[i] << endl ;
//    }


    for(int i=0; i<m_neighborlist.size(); ++i)
    {
        if (m_neighborlist[i].size() > 3)
        {
            qDebug() << "Too many neighbors in NeighborList class";
        }
    }








}
QHash<QPoint, int> NeightborList::mapping() const
{
    return m_mapping;
}

int NeightborList::getNeighborCount(const QPoint &atom_pos) const
{
    int index = getIndex(atom_pos);
    if (index == -1)
    {
        return 0;
    }
    return m_neighborlist[index].size();
}

QList<QPair<int, int> > NeightborList::getAllConnections() const
{
    QList<QPair<int, int> > list;
    int total_edge=0;

    for(int index1=0; index1<m_neighborlist.size();++index1)
    {
        total_edge += m_neighborlist[index1].size();
        QListIterator<int> it2(m_neighborlist[index1]);
        while(it2.hasNext())
        {
            int index2 = it2.next();
            if (index2<index1)
            {
                list.append(qMakePair(index1, index2));
            }
        }
    }
    return list;
}

bool NeightborList::isNeighbor(int index_a, int index_b) const
{
    if ( m_neighborlist[index_a].contains(index_b) && m_neighborlist[index_b].contains(index_a))
        return true;
    return false;
}

QList<int> NeightborList::getNeighbors(int index)
{
    return m_neighborlist[index];
}

void NeightborList::removeNeighborRelation(int index_a, int index_b)
{
    m_neighborlist[index_a].removeOne(index_b);
    m_neighborlist[index_b].removeOne(index_a);
}

int NeightborList::getIndex(const QPoint& atom_pos) const
{
    if (m_mapping.contains(atom_pos))
    {
        return m_mapping[atom_pos];
    }
    else
        return -1;
}

void NeightborList::removeAtom(const QPoint& atom_pos)
{
    int index = getIndex(atom_pos);
    if (index == -1)
        return;
    QList<int> neighbors = getNeighbors(index);
    QListIterator<int> it(neighbors);
    while(it.hasNext())
    {
        removeNeighborRelation(index, it.next());
    }
    m_atomAlive[index] = false;
}

bool NeightborList::hasIsolatedAtom()
{
    for(int i=0; i<m_neighborlist.size(); ++i)
    {
        if (m_neighborlist[i].isEmpty() && m_atomAlive.at(i))
        {
            return true;
        }
    }
    return false;
}

int NeightborList::numOfAtoms() const
{
    return m_atomAlive.count(true);
}

bool NeightborList::isAtomAlive(const QPoint &atom_pos) const
{
    int index = getIndex(atom_pos);
    if (index < 0)
        return false;
    return m_atomAlive[index];
}

QString NeightborList::toString() const
{
    QStringList list;
    int total_edge=0;

    for(int index1=0; index1<m_neighborlist.size();++index1)
    {
        total_edge += m_neighborlist[index1].size();
        QListIterator<int> it2(m_neighborlist[index1]);
        while(it2.hasNext())
        {
            int index2 = it2.next();
            if (index2<index1)
            {
                list.append(QString("%1 %2").arg(index1+1).arg(index2+1));
            }
        }
    }
    return QString("%1").arg(total_edge/2) + "\n" + list.join("\n");
}

void NeightborList::clearLink()
{
    m_atomlink.clear();
}

bool NeightborList::addLink(const QList<QPair<int, int> >& links)
{
    bool succ = true;
    for(int i=0; i<links.size();++i)
    {
        int index1 = links[i].first;
        int index2 = links[i].second;
        if (index1 > index2)
            std::swap(index1, index2);

        if (index1 == index2 || isNeighbor(index1, index2))
        {
            continue;
        }

        auto list = getNeighbors(index2);
        for (int n1 : list)
        {
            removeNeighborRelation(index2, n1);
            if (!m_neighborlist[index1].contains(n1))
            {
                m_neighborlist[index1].append(n1);
            }
            if (!m_neighborlist[n1].contains(index1))
            {
                m_neighborlist[n1].append(index1);
            }
        }
        m_atomAlive[index2] = false;
    }

    for(int i=0; i<m_neighborlist.size(); ++i)
    {
        if (m_neighborlist[i].size() > 3)
        {
            qDebug() << "Too many neighbors in NeighborList class";
            succ = false;
            break;
        }
    }

    return succ;
}
