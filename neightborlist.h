#ifndef NEIGHTBORLIST_H
#define NEIGHTBORLIST_H

#include "edgemodel.h"
#include <QList>
#include <QList>
//#include <QBitArray>
#include <QVector>

class NeightborList
{
public:
    NeightborList(const QList<EdgeModel> &edges, const QList<EdgeModel> &hidden_edges);
private:
    QVector<QPair<int, int> > m_atomlink;
    QVector<bool> m_atomAlive;

    QHash<QPoint, int> m_mapping;

    QList<int> getNeighbors(int index);
    void removeNeighborRelation(int index_a, int index_b);
public:
    bool isNeighbor(int index_a, int index_b) const;
    int getIndex(const QPoint& atom_pos) const;
    void removeAtom(const QPoint& atom_pos);
    bool hasIsolatedAtom();
    int numOfAtoms() const;
    bool isAtomAlive(const QPoint& atom_pos) const;
    QString toString() const;
    void clearLink();
    bool addLink(const QList<QPair<int, int> > &links);
    QHash<QPoint, int> mapping() const;

    int getNeighborCount(const QPoint& atom_pos) const;
    QList<QPair<int, int> > getAllConnections() const;
    QList<bool> red_atom;
    QVector<QList<int> > neighborlist;
    QVector<QList<int> > m_neighborlist;

};

#endif // NEIGHTBORLIST_H
