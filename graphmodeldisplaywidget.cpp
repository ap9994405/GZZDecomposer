#include "graphmodeldisplaywidget.h"
#include "graphmodelgraphicsitem2.h"
#include "zoomableview.h"

GraphModelDisplayWidget::GraphModelDisplayWidget(GraphModel* model, QWidget *parent) :
    QWidget(parent), m_model(model)
{
    m_scene = new QGraphicsScene(this);
    m_view = new ZoomableView(m_scene, this);
    m_item = new GraphModelGraphicsItem2(m_model);
    m_scene->addItem(m_item);
    QHBoxLayout *lay = new QHBoxLayout();
    lay->addWidget(m_view);

    this->setLayout(lay);
}
