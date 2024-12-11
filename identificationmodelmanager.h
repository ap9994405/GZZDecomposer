#ifndef IDENTIFICATIONMODELMANAGER_H
#define IDENTIFICATIONMODELMANAGER_H

#include <QObject>
#include <QModelIndex>
#include "polynomial.h"
#include "graphmodel.h"

class QStandardItem;
class QStandardItemModel;
class UniqueTagGenerator;
class IdentificationModelManager : public QObject
{

    Q_OBJECT
    friend class WidthCombineCommand;
    friend class WidthDecomposeCommand;
public:
    explicit IdentificationModelManager(QObject *parent = 0);
    
signals:
    
public slots:
    GraphModel* getModel(const QModelIndex& index);
    GraphModel* getModel(QStandardItem* item);
    QStandardItem* appendGraphModelToUnidentified(GraphModel* model);
    void appendGraphModelToIdentified(GraphModel* model);
    QStandardItemModel* getUnidentifiedModel();
    QStandardItemModel* getIdentifiedModel();
    void removeGraphModelFromUnidentified(GraphModel* model);
    void clear();
    QString getZZPolynomial();
    UniqueTagGenerator* getUniqueTagGenerator();
//    void combine(QModelIndexList list);
    QStandardItem* appendGraphModel(QStandardItemModel* target, GraphModel* model);
    QStandardItem* insertGraphModel(QStandardItemModel* target, int row, GraphModel* model);
    QStandardItem* insertGraphModel(QStandardItemModel* target, int row, QStandardItem* model);
    QList<QStandardItem*> getFreeTermCoeffItems();


    void removeItemFromIndex(QModelIndex index);
    QString getFreeTermPolynomialInHTML();

private:
//    void combineKernel(QStandardItemModel* target,const QModelIndexList& list);

    QString getCoeffs(GraphModel* model);

    QStandardItemModel* m_unidentifiedModel;
    QStandardItemModel* m_identifiedModel;

    QList<QStandardItem*> m_freeTermCoeffItems;

//    Polynomial<long long> m_freeTermCoeff;
    UniqueTagGenerator* m_tagGenerator;

    QList<GraphModel*> getAllModels();

    Polynomial<long long> getFreeTermPolynomial();

};

#endif // IDENTIFICATIONMODELMANAGER_H
