#ifndef WIDTHDECOMPOSECOMMAND_H
#define WIDTHDECOMPOSECOMMAND_H

#include "icommand.h"

#include <QList>
#include <QModelIndex>

class IdentificationModelManager;
class IdentificationDecomposer;
class GraphModel;
class UniqueTagGenerator;
class QStandardItem;
class WidthDecomposeCommand : public ICommand
{
public:
    WidthDecomposeCommand(IdentificationDecomposer* decomposer, IdentificationModelManager* manager, const UniqueTagGenerator *tagGenerator, QModelIndex index, const QList<GraphModel*>& list);
    void Execute();
    void UnExecute();
    ~WidthDecomposeCommand();

private:
    IdentificationDecomposer* m_decomposer;
    IdentificationModelManager* m_manager;
    QStandardItem* m_parent;
    QList<QStandardItem*> m_children;
    UniqueTagGenerator* m_tagGenerator;
    QModelIndex m_index;
    QList<GraphModel*> m_list;
};

#endif // WIDTHDECOMPOSECOMMAND_H
