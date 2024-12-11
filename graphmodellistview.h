#ifndef GRAPHMODELLISTVIEW_H
#define GRAPHMODELLISTVIEW_H

#include <QListView>

class GraphModelListView : public QListView
{
    Q_OBJECT
public:
    explicit GraphModelListView(QWidget *parent = 0);
protected:
    virtual void mouseReleaseEvent(QMouseEvent *e);
signals:

public slots:


};

#endif // GRAPHMODELLISTVIEW_H
