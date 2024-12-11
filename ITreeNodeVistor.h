#ifndef ITREENODEVISTOR_H
#define ITREENODEVISTOR_H


class LayoutableTreeNode;
class ITreeNodeVistor
{
public:
    virtual void visit(LayoutableTreeNode* node) = 0;
    virtual ~ITreeNodeVistor(){}
};


#endif // ITREENODEVISTOR_H
