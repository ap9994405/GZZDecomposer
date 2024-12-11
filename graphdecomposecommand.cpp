#include "graphdecomposecommand.h"
#include "decomposer.h"
#include "graphmodel.h"
#include "layoutabletree.h"

#include <QList>

GraphDecomposeCommand::GraphDecomposeCommand(Decomposer *decomposer, GraphModel *model):m_decomposer(decomposer),m_model(model)
{
    // after :, m_decomposer = decomposer, and m_model = model
    // assign value when creat the function, better then assign the value in function
    // porshce
}

void GraphDecomposeCommand::Execute()
{
    QList<GraphModel*> daughters = m_model->getDaughters(m_model->getSelectedBond());
    QListIterator<GraphModel*> it(daughters);
    while(it.hasNext())
    {
        GraphModel *item = it.next();
        item->prepare();
        if (!item->isDisconnected())
        {
            m_decomposer->addChild(m_model, item);
        }
        if (item->isDisconnected())
        {
            if (m_decomposer->allowFragments())
            {

                m_decomposer->addChild(m_model, item);
                QList<GraphModel*> fragments = item->getFragments();
                QListIterator<GraphModel*> fit(fragments);
                while(fit.hasNext())
                {
                    m_decomposer->addChild(item, fit.next());
                }
            }
            else
            {
                QList<GraphModel*> fragments = item->getFragments();
                bool anyChildrenDead = false;
                QListIterator<GraphModel*> fit(fragments);
                while(fit.hasNext())
                {
                    GraphModel* mo = fit.next();
                    if ( mo->isDead())
                    {
                        anyChildrenDead = true;
                    }
                    delete mo;
                }
                if (anyChildrenDead)
                {
                    item->setDead(true);
                }
                m_decomposer->addChild(m_model, item);
            }
        }
    }
}

void GraphDecomposeCommand::UnExecute()
{

}
