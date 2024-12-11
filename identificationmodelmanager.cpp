#include "identificationmodelmanager.h"
#include <QtWidgets>

#include "graphmodel.h"
#include "uniquetaggenerator.h"
#include <QDebug>

IdentificationModelManager::IdentificationModelManager(QObject *parent) :
    QObject(parent)
{
    m_unidentifiedModel = new QStandardItemModel(this);
    m_identifiedModel = new QStandardItemModel(this);
    m_tagGenerator = new UniqueTagGenerator();
}

GraphModel* IdentificationModelManager::getModel(const QModelIndex &index)
{
    return (GraphModel*)(index.model()->data(index,99).value<void*>());
}

GraphModel* IdentificationModelManager::getModel(QStandardItem* item)
{
    return (GraphModel*)(item->data(99).value<void*>());
}

QStandardItem* IdentificationModelManager::appendGraphModelToUnidentified(GraphModel *model)
{
    return appendGraphModel(m_unidentifiedModel, model);
}

void IdentificationModelManager::appendGraphModelToIdentified(GraphModel *model)
{
    appendGraphModel(m_identifiedModel, model);
}

QStandardItemModel *IdentificationModelManager::getUnidentifiedModel()
{
    return m_unidentifiedModel;
}

QStandardItemModel *IdentificationModelManager::getIdentifiedModel()
{
    return m_identifiedModel;
}

void IdentificationModelManager::removeGraphModelFromUnidentified(GraphModel *model)
{
//    qDebug() << "IdentificationModelManager::removeGraphModelFromUnidentified";
    for(int i=0; i<m_unidentifiedModel->rowCount(); ++i)
    {
        QStandardItem* item = m_unidentifiedModel->item(i);
        if (model ==  (GraphModel*)item->data(99).value<void*>())
        {
            m_unidentifiedModel->removeRow(i);
        }
    }
}

void IdentificationModelManager::clear()
{
//    qDebug() << "IdentificationModelManager::clear";
    m_unidentifiedModel->clear();
    m_identifiedModel->clear();
//    m_freeTermCoeff.clear();
    m_freeTermCoeffItems.clear();
    m_tagGenerator->clear();

}



QString IdentificationModelManager::getZZPolynomial()
{   
    QStringList list;
    QList<GraphModel*> all_models = getAllModels();
    QListIterator<GraphModel*> it(all_models);
    while(it.hasNext())
    {
        GraphModel* model = it.next();
        list.append(getCoeffs(model));
    }
    if (!m_freeTermCoeffItems.isEmpty())
    {
        list.append(getFreeTermPolynomial().toString());
    }

    if (list.empty())
    {
        list.append("0");
    }
    return list.join(" + ");
}

UniqueTagGenerator *IdentificationModelManager::getUniqueTagGenerator()
{
    return m_tagGenerator;
}

QString IdentificationModelManager::getCoeffs(GraphModel *model)
{
    Polynomial<long long> poly;

    poly += model->getPoly();


    if (poly.numOfTerms()==1)
    {
        if ( poly.isIdentity() )
            return model->getFullTag();
        return poly.toString()+"*"+model->getFullTag();
    }
    // qDebug() << "IdentificationModelManager";
    return "(" + poly.toString() +")*"+model->getFullTag();
}


QList<GraphModel *> IdentificationModelManager::getAllModels()
{
    QList<GraphModel*> res;
    for(int i=0; i<m_unidentifiedModel->rowCount(); ++i)
    {
        QStandardItem* item = m_unidentifiedModel->item(i);
        GraphModel* model = static_cast<GraphModel*>(item->data(99).value<void*>());
        if (model != NULL)
        {
            res.append(model);
        }
    }
    for(int i=0; i<m_identifiedModel->rowCount(); ++i)
    {
        QStandardItem* item = m_identifiedModel->item(i);
        GraphModel* model = static_cast<GraphModel*>(item->data(99).value<void*>());
        if (model != NULL)
        {
            res.append(model);
        }
    }
    return res;
}

QStandardItem* IdentificationModelManager::insertGraphModel(QStandardItemModel *target, int row, QStandardItem *model)
{
    target->insertRow(row, model);

    return model;
}

QStandardItem* IdentificationModelManager::appendGraphModel(QStandardItemModel *target, GraphModel *model)
{
    model->setTag(m_tagGenerator->getTagFromModel(model));

    QStandardItem* item = new QStandardItem();
    item->setData(qVariantFromValue((void*)model),99);

    if (model->isFinished())
    {
        m_freeTermCoeffItems.append(item);
//        m_freeTermCoeff += model->getPoly();
    }
    else
    {
        target->appendRow(item);
    }
    return item;
}

Polynomial<long long> IdentificationModelManager::getFreeTermPolynomial()
{
    QListIterator<QStandardItem*> it(m_freeTermCoeffItems);
    Polynomial<long long> res;
    while(it.hasNext())
    {
        QStandardItem* item = it.next();
        GraphModel* model = (GraphModel*)(item->data(99).value<void*>());
        res += model->getPoly();
    }
    return res;
}

QStandardItem * IdentificationModelManager::insertGraphModel(QStandardItemModel *target, int row, GraphModel *model)
{
    model->setTag(m_tagGenerator->getTagFromModel(model));

    QStandardItem* item = new QStandardItem();
    item->setData(qVariantFromValue((void*)model),99);
    if (model->isFinished())
    {
        m_freeTermCoeffItems.append(item);
    }
    else
    {
        target->insertRow(row,item);
    }
    return item;
}

QList<QStandardItem *> IdentificationModelManager::getFreeTermCoeffItems()
{
    return m_freeTermCoeffItems;
}

void IdentificationModelManager::removeItemFromIndex(QModelIndex )
{
//    if (index.isValid())
//    {
//        m_model->removeRow(index.row());
//    }
//    else
//    {
//        m_manager->getFreeTermCoeffItems().removeOne(m_newItem);
    //    }
}

QString IdentificationModelManager::getFreeTermPolynomialInHTML()
{
    return getFreeTermPolynomial().toHTML();
}
