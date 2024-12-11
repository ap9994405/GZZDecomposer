#ifndef TESTNODE_H
#define TESTNODE_H

#include "layoutabletreenode.h"
class TestNode : public LayoutableTreeNode
{
public:
    TestNode(double width, double height);
    virtual bool isHidden(){
        return false;
    }
    virtual double getWidth()
    {
        return m_width;
    }
    virtual double getHeight()
    {
        return m_height;
    }
    virtual void setPosition(const QPointF &point)
    {
        m_pos = point;
    }
    QPointF pos()
    {
        return m_pos;
    }

private:
    double m_width;
    double m_height;
    QPointF m_pos;
};

#endif // TESTNODE_H
