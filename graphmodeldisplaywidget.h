#ifndef GRAPHMODELDISPLAYWIDGET_H
#define GRAPHMODELDISPLAYWIDGET_H

#include <QWidget>
#include <QtWidgets>


class GraphModel;
class ZoomableView;
class GraphModelGraphicsItem2;
class GraphModelDisplayWidget : public QWidget
{
    Q_OBJECT
public:
    GraphModelDisplayWidget(GraphModel* model, QWidget *parent = 0);

signals:

public slots:
private:
    QGraphicsScene *m_scene;
    ZoomableView* m_view;
    GraphModel* m_model;
    GraphModelGraphicsItem2* m_item;
};

#endif // GRAPHMODELDISPLAYWIDGET_H
