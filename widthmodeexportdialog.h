#ifndef WIDTHMODEEXPORTDIALOG_H
#define WIDTHMODEEXPORTDIALOG_H

#include <QDialog>
#include <QStandardItemModel>
#include <QtWidgets>
#include "graphmodelgraphicsitem.h"

namespace Ui {
class WidthModeExportDialog;
}

class WidthModeExportDialog : public QDialog
{
    Q_OBJECT
    
public:
    WidthModeExportDialog(QStandardItemModel* model,
                          const QString& freeterm_poly, QWidget *parent = 0);
    ~WidthModeExportDialog();
    
    void updateFrame();
    void updateGridLines();
    void clearGridLines();
    void clearFrame();
private slots:
    void on_button_cancel_clicked();
    void updatePreview();
    bool save();
    void prepareGraphics();
    void on_button_OK_clicked();

    void on_horizontalSlider_2_valueChanged(int value);

    void on_horizontalSlider_3_valueChanged(int value);

    void on_horizontalSlider_4_valueChanged(int value);

    void on_checkBox_gridlines_toggled(bool checked);

    void on_checkBox_toggled(bool checked);


    void on_slider_ncols_valueChanged(int value);

private:
    Ui::WidthModeExportDialog *ui;
    int m_numCols;
    QStandardItemModel* m_model;
    QGraphicsScene scene;
    bool prepared;
    QVector<GraphModelGraphicsItem*> m_graphItems;
    QVector<QGraphicsLineItem*> m_gridLines;
    QGraphicsRectItem* m_frame;
    QVector<QGraphicsTextItem*> m_textItems;
    int m_hSpacing;
    int m_vSpacing;
    int m_margin;
    bool m_drawGridLines;
    bool m_drawFrame;
    double m_maxWidth;
    double m_maxHeight;
    QString m_freeterm_poly;

    double m_doc_left;
    double m_doc_top;
    double m_doc_width;
    double m_doc_height;

};

#endif // WIDTHMODEEXPORTDIALOG_H
