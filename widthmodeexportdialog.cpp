#include "widthmodeexportdialog.h"
#include "ui_widthmodeexportdialog.h"

#include <QIntValidator>
#include <QStandardItemModel>

#include <QtSvg>

#include "graphmodel.h"
#include "graphmodelgraphicsitem.h"

#include <QDebug>
#include "graphmodeltag.h"
#include "gzip_helper.h"
#include "file_helpers.h"

WidthModeExportDialog::WidthModeExportDialog(QStandardItemModel* model,
                                             const QString& freeterm_poly, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WidthModeExportDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Preview");

    this->m_model = model;
    m_freeterm_poly = freeterm_poly;


    ui->graphicsView->setScene(&scene);
    ui->graphicsView->setZoomable(true);
    ui->graphicsView->setMouseTracking(true);

    m_numCols = std::max(std::min(model->rowCount(),3),1);



    m_vSpacing = 50;
    m_hSpacing = 50;
    m_margin = 10;
    prepared = false;
    m_drawGridLines = true;
    m_drawFrame = true;
    m_maxWidth = 0;
    m_maxHeight = 0;
    m_frame = NULL;
    prepareGraphics();

    ui->slider_ncols->setValue(m_numCols);
    m_doc_left = 0.0;
    m_doc_top = 0.0;
    m_doc_width = 0.0;
    m_doc_height = 0.0;

    updatePreview();
}

WidthModeExportDialog::~WidthModeExportDialog()
{
    scene.clear();
    delete ui;
}

void WidthModeExportDialog::on_button_cancel_clicked()
{
    scene.clear();
    this->reject();
}



void WidthModeExportDialog::updateFrame()
{
    QRectF rr(m_doc_left,m_doc_top, m_doc_width, m_doc_height);

    m_frame = new QGraphicsRectItem(rr,NULL);
    m_frame->setPen(QPen(QBrush(QColor("#606060")),3));
    scene.addItem(m_frame);
}

void WidthModeExportDialog::clearGridLines()
{
    for(int i=0; i<m_gridLines.size();++i)
    {
        delete m_gridLines[i];
    }
    m_gridLines.clear();
}

void WidthModeExportDialog::clearFrame()
{
    if ( m_frame != NULL)
    {
        delete m_frame;
        m_frame = NULL;
    }
}

void WidthModeExportDialog::updateGridLines()
{
    int modRow = m_graphItems.size() % m_numCols;
    int num_rows = m_graphItems.size()/m_numCols + (modRow >0 ? 1:0);

    double totWidth = (m_numCols-1)*m_hSpacing+m_maxWidth*m_numCols;
    double totHeight = (num_rows-1)*m_vSpacing+m_maxHeight*num_rows;
    double paddingH = static_cast<double>(m_hSpacing)/2.0;
    double paddingV = static_cast<double>(m_vSpacing)/2.0;

    QPen pen(QBrush(QColor("#606060")),3);

    //hor
    for(int i=1; i<num_rows;++i)
    {
        double curY;
        curY = i*m_maxHeight+(i-1)*m_vSpacing+static_cast<double>(m_vSpacing)/2.0;
        m_gridLines.push_back(scene.addLine(0.0-paddingH,curY,totWidth+paddingH, curY, pen));
    }

    //verticle
    for(int i=1; i<m_numCols;++i)
    {
        double height = totHeight;
        if (modRow > 0 && i > modRow)
        {
            height = (num_rows-2)*m_vSpacing+m_maxHeight*(num_rows-1);
        }
        double curX;
        curX = i*m_maxWidth+(i-1)*m_hSpacing+static_cast<double>(m_hSpacing)/2.0;
        m_gridLines.push_back(scene.addLine(curX,0.0-paddingV,curX,height+paddingV, pen));
    }

    //top
    m_gridLines.push_back(scene.addLine(0.0-paddingH,0.0-paddingV,totWidth+paddingH,0.0-paddingV,pen));
    //left
    m_gridLines.push_back(scene.addLine(0.0-paddingH,0.0-paddingV,0.0-paddingH,totHeight+paddingV,pen));




    if (modRow == 0)
    {
        //bottom
        m_gridLines.push_back(scene.addLine(0.0-paddingH,totHeight+paddingV,totWidth+paddingH,totHeight+paddingV,pen));
        //right
        m_gridLines.push_back(scene.addLine(totWidth+paddingH,0.0-paddingV,totWidth+paddingH,totHeight+paddingV,pen));
    }
    else
    {
        //bottom
        double width = (modRow-1)*m_hSpacing+m_maxWidth*modRow;
        double  height = (num_rows-2)*m_vSpacing+m_maxHeight*(num_rows-1);
        m_gridLines.push_back(scene.addLine(0.0-paddingH,totHeight+paddingV,width+paddingH,totHeight+paddingV,pen));
        //right
        m_gridLines.push_back(scene.addLine(totWidth+paddingH,0.0-paddingV,totWidth+paddingH,height+paddingV,pen));
    }


}

void WidthModeExportDialog::updatePreview()
{
    QList<QGraphicsItem*> items = scene.items();
    for(int i=items.size()-1; i>=0;i--)
    {
        GraphModelGraphicsItem * myitem = dynamic_cast<GraphModelGraphicsItem*>(items[i]);
        if (myitem != NULL && m_graphItems.contains(myitem))
        {
            scene.removeItem(items[i]);
        }
    }

    int curRow = 0;
    int curCol = 0;

    for(int i=0; i<m_graphItems.size(); ++i)
    {
        curCol = i - curRow*m_numCols;
        scene.addItem(m_graphItems[i]);

        m_graphItems[i]->setPos(curCol*m_maxWidth+m_hSpacing*(curCol),curRow*m_maxHeight+m_vSpacing*(curRow));

        if ((i+1)%m_numCols==0)
        {
            curRow += 1;          
        }
    }


    clearGridLines();
    if (m_drawGridLines)
    {
        updateGridLines();
    }

    for(int i=0; i<m_textItems.size(); ++i)
    {
        delete m_textItems[i];
    }
    m_textItems.clear();

    int modRow = m_graphItems.size() % m_numCols;
    int num_rows = m_graphItems.size()/m_numCols + (modRow >0 ? 1:0);

    double totWidth = (m_numCols-1)*m_hSpacing+m_maxWidth*m_numCols;
    double totHeight = (num_rows-1)*m_vSpacing+m_maxHeight*num_rows;
    double paddingH = static_cast<double>(m_hSpacing)/2.0;
    double paddingV = static_cast<double>(m_vSpacing)/2.0;

    QFont font("Times New Roman",26);
    QFontMetricsF matrics(font);

    double textLeft = 0.0-static_cast<double>(m_hSpacing)/2.0;

    QGraphicsTextItem* title = scene.addText("Identified Graphs:",font);
    title->setPos(textLeft,-m_vSpacing/2.0-matrics.height()-10);
    m_textItems.push_back(title);

    double freeterm_y = totHeight+static_cast<double>(m_vSpacing)/2.0 ;
    QGraphicsTextItem* freeterms = scene.addText("Free Term Coefficients:",font);
    freeterms->setPos(textLeft,freeterm_y);
    m_textItems.push_back(freeterms);

    QGraphicsTextItem* poly = new QGraphicsTextItem(NULL);
    poly->setFont(font);
    poly->setHtml(m_freeterm_poly);
    poly->setPos(textLeft,freeterm_y+matrics.height());
    m_textItems.push_back(poly);
    scene.addItem(poly);

    m_doc_top = title->pos().y()-m_margin;
    m_doc_left = textLeft - m_margin;
    m_doc_width = totWidth+2*paddingH+2*m_margin;
    m_doc_height = totHeight+2*paddingV+2*m_margin+freeterms->boundingRect().height()+
            poly->boundingRect().height()+title->boundingRect().height();


    clearFrame();
    if (m_drawFrame)
    {
        updateFrame();
    }

    scene.setSceneRect(scene.itemsBoundingRect().adjusted(-50,-50,100,100));
}

bool WidthModeExportDialog::save()
{
    bool comp = false;
    QString filename = getSVGExportFilename(this, &comp);

    if (filename.isNull())
    {
        return false;
    }

    QSvgGenerator svgGen;

    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    svgGen.setOutputDevice(&buffer);

    QRectF rr = scene.itemsBoundingRect();

    svgGen.setTitle("ZZ Decomposition Export");
    svgGen.setSize(QSize(rr.width(),rr.height()));
    svgGen.setViewBox(rr);
    QPainter painter;
    painter.begin(&svgGen);

    scene.render(&painter,rr,rr);
    painter.end();


    QFile file( filename );
    file.open( QIODevice::WriteOnly );
    if (comp)
    {
        QByteArray compressed = compress(byteArray);
        file.write( compressed );
    }
    else
    {
        file.write(byteArray);
    }
    file.close();


    return true;

}

void WidthModeExportDialog::prepareGraphics()
{
    if (prepared == false)
    {
        int size = m_model->rowCount();
        for(int i=0; i<size; ++i)
        {
            QStandardItem* item = m_model->item(i);
            GraphModel* graphModel = static_cast<GraphModel*>(item->data(99).value<void*>());
            GraphModelGraphicsItem* graphItem = new GraphModelGraphicsItem(graphModel);
            graphItem->setEnabled(false);
            graphItem->setShowTagWhenDisconnected(true);
            this->m_graphItems.push_back(graphItem);

            if (graphItem->boundingRect().width() > m_maxWidth)
            {
                m_maxWidth = graphItem->boundingRect().width();
            }
            if (graphItem->boundingRect().height() > m_maxHeight)
            {
                m_maxHeight = graphItem->boundingRect().height();
            }
        }
        prepared = true;
    }
}


void WidthModeExportDialog::on_button_OK_clicked()
{
    bool saved = save();
    if (saved)
    {
        accept();
    }
}

void WidthModeExportDialog::on_horizontalSlider_2_valueChanged(int value)
{
    this->m_vSpacing = value;
    updatePreview();
}

void WidthModeExportDialog::on_horizontalSlider_3_valueChanged(int value)
{
    this->m_hSpacing = value;
    updatePreview();
}

void WidthModeExportDialog::on_horizontalSlider_4_valueChanged(int value)
{
    this->m_margin = value;
    updatePreview();
}

void WidthModeExportDialog::on_checkBox_gridlines_toggled(bool checked)
{
    this->m_drawGridLines = checked;
    updatePreview();
}

void WidthModeExportDialog::on_checkBox_toggled(bool checked)
{
    this->m_drawFrame = checked;
    updatePreview();
}


void WidthModeExportDialog::on_slider_ncols_valueChanged(int value)
{
    ui->label_ncols->setText(QString("%1").arg(value));
    this->m_numCols = value;
    updatePreview();
}
