#ifndef GRAPHDECOMPOSECOMMAND_H
#define GRAPHDECOMPOSECOMMAND_H

#include "icommand.h"

class Decomposer;
class GraphModel;

class GraphDecomposeCommand : public ICommand
{
public:
    GraphDecomposeCommand(Decomposer* decomposer, GraphModel* model);
    virtual void Execute();
    virtual void UnExecute();
private:
    Decomposer *m_decomposer;
    GraphModel *m_model;

};

#endif // GRAPHDECOMPOSECOMMAND_H
