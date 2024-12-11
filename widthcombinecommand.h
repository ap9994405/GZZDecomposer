#ifndef WIDTHCOMBINECOMMAND_H
#define WIDTHCOMBINECOMMAND_H

#include "icommand.h"

#include <QModelIndexList>



class UniqueTagGenerator;
class IdentificationModelManager;
class QStandardItemModel;
class QStandardItem;
class GraphModel;
class WidthCombineCommand : public ICommand
{
public:
    WidthCombineCommand(IdentificationModelManager* manager, QModelIndexList list);
    void Execute();
    void UnExecute();
private:
    IdentificationModelManager* m_manager;
    QModelIndexList m_list;
    QStandardItemModel* m_model;

    QMap<int, QStandardItem*> m_oldpos;
    QStandardItem* m_newItem;
    UniqueTagGenerator* m_tagGenerator;
};

#endif // WIDTHCOMBINECOMMAND_H
