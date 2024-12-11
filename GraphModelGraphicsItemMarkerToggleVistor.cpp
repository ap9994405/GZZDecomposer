#include "GraphModelGraphicsItemMarkerToggleVistor.h"

#include "graphmodeltreenode.h"
#include "graphmodelgraphicsitem.h"

GraphModelGraphicsItemMarkerToggleVistor::GraphModelGraphicsItemMarkerToggleVistor()
{
    this->show_marker = false;
}

void GraphModelGraphicsItemMarkerToggleVistor::visit(LayoutableTreeNode *node)
{
    GraphModelTreeNode* gnode = dynamic_cast<GraphModelTreeNode*>(node);
    if (gnode)
    {
        GraphModelGraphicsItem* item = gnode->getGraphicsItem();
        item->setShowMarker(this->show_marker);
    }
}

bool GraphModelGraphicsItemMarkerToggleVistor::isMarkerShowed()
{
    return this->show_marker;
}

void GraphModelGraphicsItemMarkerToggleVistor::setShowMarker(bool value)
{
    this->show_marker = value;
}

