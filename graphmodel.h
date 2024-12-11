#ifndef GRAPHMODEL_H
#define GRAPHMODEL_H

#include <QObject>
#include "edgemodel.h"
#include <QList>
#include "polynomial.h" //not stringpolynomial.h, be careful
#include "neightborlist.h"

#include <QString>

class GraphModel : public QObject
{
    Q_OBJECT
public:
    enum DecompositionType
    {
        Single, Double, Ring, None, Fragment, BisRing
    };
    GraphModel(const QList<EdgeModel>& edges, const QList<EdgeModel>& hiddenEdges, const GraphModel* modelParent, DecompositionType type, QObject *parent = 0);
    ~GraphModel();
signals:
//    void BondSelected(GraphModel* model, EdgeModel edge);
//    void BondUnselected(GraphModel* model, EdgeModel edge);
    void SelectionChanged(GraphModel* model);
    void Disconnected(GraphModel* model);
    void StateChanged(GraphModel* model);
    void PolynomialChanged(GraphModel* model);
    void TagChanged(GraphModel* model);
public slots:
    QList<GraphModel*> getDaughters(EdgeModel edge);
    void selectBond(EdgeModel edge);
    void unselectBond();
    bool isBondSelected();
    EdgeModel getSelectedBond();
    QList<GraphModel*> getFragments();
    QString getZZInput(bool connections, bool hydrogens) const;
    void setDead(bool isDead);
    void prepare();

public:

    GraphModel *getNoRingDaughter(const QList<EdgeModel> &edges);
    GraphModel *getNoBisRingDaughter(const QList<EdgeModel> &edges);
    QList<GraphModel *> getNoEdgeDaughter( QList<EdgeModel>& edges);
    QList<QPoint > getSpinPoint(QList<EdgeModel>& edges);
    void setTag(const QString &tag);
    bool hasCustomTag();
    void setCustomTag(const QString &tag);
    QString getTag();
    QString getCustomTag();
    QString getFullTag();
    bool isDead();
    bool isEmpty();
    bool isFinished();
    QList<EdgeModel> getAllEdges() const;
    const QList<EdgeModel>& getEdges() const;
    const QList<EdgeModel>& getHiddenEdges();
    const QList<EdgeModel>& getDoubleBonds() const;
    const QList<QList<EdgeModel> >& getRings() const;
    const QList<QList<EdgeModel> >& getBisRings() const;
    bool isDisconnected();
    DecompositionType getType();
    const Polynomial<long long>& getPoly() const;
    void setPoly(const Polynomial<long long>& poly);
    // const GraphModel* getModelParent();

    const NeightborList& getNeighborList() const;

    void clearLink();
    bool addLink(const QList<QPair<int, int>> & links);
    QList<QList<EdgeModel> > getAllRings() const;
    QList<EdgeModel> m_hidden_edges; //change 2018/6/11
private slots:   

    GraphModel* getNoBondDaughter(EdgeModel edge);
    GraphModel* getNoAtomsDaughter(EdgeModel edge);

    QList<GraphModel*> getNoRingDaughter(EdgeModel edge);
    QList<GraphModel*> getNoBisRingDaughter(EdgeModel edge);

private:
    void cutDanglingBonds();
    void removeAtoms(const EdgeModel &edge, QList<EdgeModel> &alive_edges, QList<EdgeModel> &dead_edges);
    QVector<QList<EdgeModel> > checkIfDisconnected(QList<EdgeModel> edges);
    void addRing(const QList<EdgeModel> &bonds);
    void addBisRing(const QList<EdgeModel> &bonds);
    void addDoubleBond(const EdgeModel &line);
    QList<GraphModel*> split(const QVector<QList<EdgeModel> >& parts);
    QList<QList<EdgeModel> > getRingEdges(EdgeModel edge);
    QList<QList<EdgeModel> > getBisRingEdges(EdgeModel edge);


private:
    const GraphModel *m_modelParent;
    DecompositionType m_type;
    QList<EdgeModel> m_edges;


    QList<QList<EdgeModel> > m_rings;
    QList<QList<EdgeModel> > m_bisrings;
    QList<EdgeModel> m_doublebonds;

    NeightborList m_neighborlist;

    bool m_isDisconnected;
    bool m_isFinished;

    bool m_isDead;
    bool m_isHidden;
//    int m_depth;

    Polynomial<long long> m_poly;

    bool m_isBondSelected;
    EdgeModel m_selectedBond;
    QVector<QList<EdgeModel> > m_parts;
    QList<GraphModel*> all_gm_chid;
    QList<QPoint> m_spin_point;

    QString m_tag;
    QString m_customTag;
};

#endif // GRAPHMODEL_H
