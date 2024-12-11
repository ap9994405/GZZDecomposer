#ifndef GRAPHICSITEMDEBUGDIALOG_H
#define GRAPHICSITEMDEBUGDIALOG_H

#include <QDialog>
#include <QtWidgets>

namespace Ui {
class GraphicsItemDebugDialog;
}

class GraphModelGraphicsItem;
class GraphicsItemDebugDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit GraphicsItemDebugDialog(QWidget *parent = 0);
    ~GraphicsItemDebugDialog();
    void setItem(GraphModelGraphicsItem* item);
private slots:
    void loadProperties();
    void update_rect_x(QString value);
    void update_rect_y(QString value);
    void update_rect_w(QString value);
    void update_rect_h(QString value);
private:
    Ui::GraphicsItemDebugDialog *ui;
    GraphModelGraphicsItem* m_item;
    QTimer m_timer;
};

#endif // GRAPHICSITEMDEBUGDIALOG_H
