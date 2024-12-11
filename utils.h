#ifndef UTILS_H
#define UTILS_H

#include <QPoint>
#include <cmath>
#include "edgemodel.h"

QPoint ringXY2vertexXY(QPoint old_p);

QPointF vertexXY2XY(QPointF old_p, double r);

QPoint XY2VertexXY(QPointF old_p, double r);

QPointF rotate(const QPointF& old_p, const QPointF &center, int fold);

void getCenter(const QList<EdgeModel>& all_edges, QList<QPointF> &all_points,
                QPointF& graph_center);

void getRingCenters(const QList<QList<EdgeModel> >& rings, QList<QPointF> &ring_centers);

bool compareQPointF(const QPointF& p1, const QPointF& p2);
bool isIsomorphic(const QList<QPointF> &graph1, const QList<QPointF> &graph2);

#endif // UTILS_H
