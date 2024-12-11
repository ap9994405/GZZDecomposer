#include "undoredomanager.h"
#include "icommand.h"
UndoRedoManager::UndoRedoManager()
{
}

void UndoRedoManager::addCommand(ICommand *command)
{
    m_undostack.push(command);
    clearRedo();
}

void UndoRedoManager::clearRedo()
{
    while(!m_redostack.isEmpty())
    {
        ICommand *command  = m_redostack.pop();
        delete command;
    }
}

void UndoRedoManager::undo()
{
    if (!m_undostack.isEmpty())
    {
        ICommand* command = m_undostack.pop();
        command->UnExecute();
        m_redostack.push(command);
    }
}

void UndoRedoManager::redo()
{
    if (!m_redostack.isEmpty())
    {
        ICommand* command = m_redostack.pop();
        command->Execute();
        m_undostack.push(command);
    }
}

void UndoRedoManager::clear()
{
    clearRedo();
    while(!m_undostack.isEmpty())
    {
        ICommand *command  = m_undostack.pop();
        delete command;
    }
}
