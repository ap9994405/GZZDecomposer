#ifndef ICOMMAND_H
#define ICOMMAND_H

class ICommand
{
public:
    ICommand(){}
    virtual void Execute() = 0;
    virtual void UnExecute() = 0;
    virtual ~ICommand(){}
};

#endif // ICOMMAND_H
