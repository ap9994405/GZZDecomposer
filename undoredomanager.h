#ifndef UNDOREDOMANAGER_H
#define UNDOREDOMANAGER_H

#include <QStack>

class ICommand;

class UndoRedoManager
{
public:
    UndoRedoManager();
    void undo();
    void redo();
    void addCommand(ICommand* command);
    void clear();
private:
    QStack<ICommand*> m_undostack;
    QStack<ICommand*> m_redostack;
    void clearRedo();
};

#endif // UNDOREDOMANAGER_H
