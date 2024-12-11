#include "widthdecomposecommand.h"

#include "uniquetaggenerator.h"
#include "identificationmodelmanager.h"

#include <QStandardItemModel>
#include "identificationdecomposer.h"

WidthDecomposeCommand::WidthDecomposeCommand(IdentificationDecomposer* decomposer, IdentificationModelManager* manager, const UniqueTagGenerator *tagGenerator, QModelIndex index, const QList<GraphModel *> &list):
    m_decomposer(decomposer), m_manager(manager), m_index(index), m_list(list)
{
    m_tagGenerator = new UniqueTagGenerator(*tagGenerator);
}

void WidthDecomposeCommand::Execute()
{
    if (!m_list.isEmpty())
    {
        m_children.clear();

        QListIterator<GraphModel*> it(m_list);
        while(it.hasNext())
        {
            GraphModel* item = it.next();
            if (!item->isDead())
            {
                m_children.append(m_manager->appendGraphModelToUnidentified(item));
            }
        }
        m_parent = m_manager->m_unidentifiedModel->takeItem(m_index.row());
        m_manager->m_unidentifiedModel->removeRow(m_index.row());
        m_decomposer->m_freeterm_text->setHtml(m_manager->getFreeTermPolynomial().toHTML2());       //bug here

    }
}

void WidthDecomposeCommand::UnExecute()
{
    *(m_manager->m_tagGenerator) = *(m_tagGenerator);

    if (!m_list.isEmpty())
    {

        QListIterator<QStandardItem*> it(m_children);
        while(it.hasNext())
        {
            QStandardItem* item = it.next();
            QStandardItemModel* itemModel = m_manager->m_unidentifiedModel;

            QModelIndex index = itemModel->indexFromItem(item);
            if (index.row() != -1)
            {
                m_manager->m_unidentifiedModel->removeRow(index.row());
            }
            else
            {
                m_manager->m_freeTermCoeffItems.removeOne(item);
            }
        }

        m_manager->m_unidentifiedModel->insertRow(m_index.row(),m_parent);
        m_decomposer->m_freeterm_text->setHtml(m_manager->getFreeTermPolynomial().toHTML2());

    }
}

WidthDecomposeCommand::~WidthDecomposeCommand()
{
    delete m_tagGenerator;
}
