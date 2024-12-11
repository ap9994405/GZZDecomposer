#include "widthcombinecommand.h"
#include <QStandardItemModel>

#include "identificationmodelmanager.h"
#include "graphmodel.h"

#include "uniquetaggenerator.h"

WidthCombineCommand::WidthCombineCommand(IdentificationModelManager* manager, QModelIndexList list): m_manager(manager), m_list(list)
{
    m_tagGenerator = NULL;
    if (!list.isEmpty())
    {
        const QStandardItemModel* model = dynamic_cast<const QStandardItemModel*>(list.first().model());

        if (model == m_manager->getUnidentifiedModel())
        {
            m_model = m_manager->getUnidentifiedModel();
        }
        else if (model == m_manager->getIdentifiedModel())
        {
            m_model = m_manager->getIdentifiedModel();
        }
        qSort(m_list);
    }
}

void WidthCombineCommand::Execute()
{   
    if (!m_list.isEmpty())
    {
        m_oldpos.clear();

        QListIterator<QModelIndex> it(m_list);

        while(it.hasNext())
        {
            QModelIndex index = it.next();
            m_oldpos.insert(index.row(), m_model->takeItem(index.row()));
        }
        it.toBack();
        while(it.hasPrevious())
        {

            QModelIndex index = it.previous();
            m_model->removeRow(index.row());
        }

        Polynomial<long long> poly;
        QMapIterator<int, QStandardItem*> it2(m_oldpos);
        while(it2.hasNext())
        {
            it2.next();
            poly +=  m_manager->getModel(it2.value())->getPoly();
        }

        GraphModel* head = m_manager->getModel(m_oldpos.begin().value());

        GraphModel* newItem = new GraphModel(head->getEdges(),head->getHiddenEdges(),0,head->getType(),head->parent());
        newItem->setPoly(poly);
        qDebug() << "someting happened";
        m_tagGenerator = new UniqueTagGenerator(*(m_manager->m_tagGenerator));
        m_newItem = m_manager->appendGraphModel(m_model, newItem);
    }
}

void WidthCombineCommand::UnExecute()
{
    if ( m_newItem != NULL)
    {
        QModelIndex index = m_model->indexFromItem(m_newItem);
        if (index.isValid())
        {
            m_model->removeRow(index.row());
        }
        else
        {
            m_manager->getFreeTermCoeffItems().removeOne(m_newItem);
        }
        m_newItem = NULL;
    }
    else
    {
        qWarning() << "There might be a bug in CombineCommand class";
    }

    *(m_manager->m_tagGenerator) = *(m_tagGenerator);
    QMapIterator<int, QStandardItem*> it2(m_oldpos);
    while(it2.hasNext())
    {
        it2.next();
        m_manager->insertGraphModel(m_model, it2.key(), it2.value());
    }
    delete m_tagGenerator;
    m_tagGenerator = NULL;
}
