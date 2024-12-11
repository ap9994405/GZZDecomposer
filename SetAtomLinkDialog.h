#ifndef SETATOMLINKDIALOG_H
#define SETATOMLINKDIALOG_H

#include <QDialog>
#include <QGraphicsScene>
#include "zoomableview.h"
#include <QTableWidget>

class GraphModel ;
class GraphModelGraphicsItem;
class SetAtomLinkDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SetAtomLinkDialog(GraphModel* model, QWidget *parent = 0);

signals:

public slots:
private slots:
    void preview();
private:
    QGraphicsScene* scene;
    ZoomableView *view;
    GraphModel* m_model;
    QPushButton* m_addLink;
    QPushButton* m_removeLink;
    QTableWidget* m_table;
    QPushButton* m_preview;
    GraphModelGraphicsItem *graph_item;

};

#endif // SETATOMLINKDIALOG_H
