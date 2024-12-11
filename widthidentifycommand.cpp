#include "widthidentifycommand.h"
#include <QStandardItemModel>
#include <QModelIndex>
#include <QMapIterator>

#include <QDebug>

WidthIdentifyCommand::WidthIdentifyCommand(QStandardItemModel* source, QStandardItemModel* target, const QModelIndexList& indexes):
    m_source(source), m_target(target)
{
    QModelIndexList list = indexes;
    qSort(list);
    QListIterator<QModelIndex> it(list);
    while(it.hasNext())
    {
        QModelIndex index = it.next();
        m_oldpos.insert(index.row(),m_source->item(index.row()));
    }
}

void WidthIdentifyCommand::Execute()
{
    QMapIterator<int, QStandardItem*> it(m_oldpos);
    while(it.hasNext())
    {
        it.next();
        QModelIndex index = m_source->indexFromItem(it.value());
        m_source->takeItem(index.row());
        m_target->appendRow(it.value());
        m_source->removeRow(index.row());
    }
}

void WidthIdentifyCommand::UnExecute()
{
    QMapIterator<int, QStandardItem*> it(m_oldpos);
    while(it.hasNext())
    {
        it.next();
        QModelIndex index = m_target->indexFromItem(it.value());
        m_target->takeItem(index.row());
        m_source->insertRow(it.key(),it.value());
        m_target->removeRow(index.row());
    }
}
