#ifndef GRAPHMODELGRAPHICSITEMMARKERTOGGLEVISTOR_H
#define GRAPHMODELGRAPHICSITEMMARKERTOGGLEVISTOR_H

#include "ITreeNodeVistor.h"
class GraphModelGraphicsItemMarkerToggleVistor : public ITreeNodeVistor
{
public:
    GraphModelGraphicsItemMarkerToggleVistor();
    virtual void visit(LayoutableTreeNode *node);
    bool isMarkerShowed();
    void setShowMarker(bool value);
private:
    bool show_marker;


};

#endif // GRAPHMODELGRAPHICSITEMMARKERTOGGLEVISTOR_H
