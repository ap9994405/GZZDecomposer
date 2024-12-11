#ifndef WIDTHIDENTIFYCOMMAND_H
#define WIDTHIDENTIFYCOMMAND_H

#include "icommand.h"
#include <QModelIndexList>
#include <QMap>
class QStandardItemModel;
class QStandardItem;
class WidthIdentifyCommand : public ICommand
{
public:
    WidthIdentifyCommand(QStandardItemModel* source, QStandardItemModel* target, const QModelIndexList& indexes);
    void Execute();
    void UnExecute();
private:
    QStandardItemModel* m_source;
    QStandardItemModel* m_target;
    QMap<int, QStandardItem*> m_oldpos;
};

#endif // WIDTHIDENTIFYCOMMAND_H
