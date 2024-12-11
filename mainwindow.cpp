#include "mainwindow.h"
#include "graphmodel.h"
#include "graphmodelgraphicsitem.h"

#include "zoomableview.h"

#include "VERION_INFO.H"

#include "identificationdecomposer.h"
#include "builderwidget.h"
#include "decomposer.h"
#include "zzpolynomialcalculatorpanel.h"
#include "gzzpolynomialcalculatorpanel.h"

#include "graphmodeldisplaywidget.h"

#include "SetAtomLinkDialog.h"

#include "formats.h"
#include "file_helpers.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);

    m_workingGraphModel = NULL;

    this->setWindowTitle(tr("GZZDecomposer"));

    m_builder = new BuilderWidget();

    m_tabWidget = new QTabWidget(this);
    this->setCentralWidget(m_tabWidget);
    m_tabWidget->addTab(m_builder, tr("Builder"));

    m_decomposer = new Decomposer(0,this);
    m_tabWidget->addTab(m_decomposer, tr("Depth-mode Decomposer"));
    
    m_identDecomposer = new IdentificationDecomposer(this);
    m_tabWidget->addTab(m_identDecomposer, tr("Width-mode Decomposer"));

    m_zzCalculatorPanel = new ZZPolynomialCalculatorPanel(this);
    // m_tabWidget->addTab(m_zzCalculatorPanel, tr("ZZ Polynomial Calculator"));

    m_porsche = new porsche(this);
    m_tabWidget->addTab(m_porsche, tr("GZZ Polynomial Calculator"));


    connect(m_builder,SIGNAL(ZZPolynomialRequest(GraphModel*)),this, SLOT(builderProcessZZPolynomialRequest(GraphModel*)));
    connect(m_decomposer,SIGNAL(ZZPolynomialRequest(GraphModel*)),this,SLOT(processZZPolynomialRequest(GraphModel*)));
    connect(m_identDecomposer,SIGNAL(ZZPolynomialRequest(GraphModel*)),this,SLOT(processZZPolynomialRequest(GraphModel*)));
    connect(m_tabWidget, SIGNAL(currentChanged(int)), this, SLOT(tabPageChanged(int)));

    createActions();
    createMenus();
    createToolbars();

    createDocks();
}

void MainWindow::tabPageChanged(int index)
{
    if (index == 2)
    {
        m_undo->setEnabled(true);
        m_redo->setEnabled(true);
    }
    else
    {
        m_undo->setEnabled(false);
        m_redo->setEnabled(false);
    }
    if (index > 0)
    {
        if (m_workingGraphModel == NULL)
        {
            m_workingGraphModel = m_builder->getGraphModel();
            if ( m_workingGraphModel->isEmpty())
            {
                delete m_workingGraphModel;
                m_workingGraphModel = NULL;
            }
            else
            {
                m_decomposer->setRootGraph(m_builder->getGraphModel());
                m_identDecomposer->setRootGraph( m_builder->getGraphModel());
                m_zzCalculatorPanel->addRow(m_builder->getGraphModel());
                m_porsche->addRow(m_builder->getGraphModel());
            }

        }
        else
        {
            GraphModel* model = m_builder->getGraphModel();
            QSet<EdgeModel> s1, s2;
            QListIterator<EdgeModel> it(m_workingGraphModel->getAllEdges());
            while(it.hasNext())
            {
                s1.insert(it.next());
            }
            QListIterator<EdgeModel> it2(model->getAllEdges());
            while(it2.hasNext())
            {
                s2.insert(it2.next());
            }
            if (s1!=s2)
            {
                delete m_workingGraphModel;
                m_workingGraphModel = NULL;
                m_workingGraphModel = model;
                m_decomposer->clear();
                m_decomposer->setRootGraph(m_builder->getGraphModel());

                m_identDecomposer->clear();
                m_identDecomposer->setRootGraph(m_builder->getGraphModel());
                m_zzCalculatorPanel->addRow(m_builder->getGraphModel());
                m_porsche->addRow(m_builder->getGraphModel());
            }
            else
            {
                delete model;
            }
        }
    }
    if (index == 0)
    {
        m_savefile->setEnabled(true);
        m_zzinfo->setEnabled(false);
    }
    else if (index == 1)
    {
        m_savefile->setEnabled(true);
        m_zzinfo->setEnabled(true);
    }
    else if ( index == 2 )
    {
        m_zzinfo->setEnabled(true);
        m_savefile->setEnabled(true);
    }
    else if (index == 4)
    {
        m_savefile->setEnabled(true);
    }

    else
    {
        m_savefile->setEnabled(false);
        m_zzinfo->setEnabled(false);

    }



    if (index == 1)
    {
        m_toogleSeparateFragments->setEnabled(true);
    }
    else
    {
        m_toogleSeparateFragments->setEnabled(false);
    }

}

void MainWindow::clearAll()
{
    m_builder->clear();
    m_decomposer->clear();
    m_tabWidget->setCurrentIndex(0);
    m_identDecomposer->clear();
    m_workingGraphModel = NULL;
}

void MainWindow::createActions()
{
    m_newfile = new QAction(QIcon(":/images/newfile.png"),tr("&New"),this);
    connect(m_newfile, SIGNAL(triggered()), this, SLOT(clearAll()));
    m_savefile = new QAction(QIcon(":/images/savefile.png"),tr("&Save"),this);
    m_openfile = new QAction(QIcon(":/images/openfile.png"),tr("&Open"),this);
//    m_savefile->setEnabled(false);

//    connect(m_savefile, SIGNAL(triggered()), this, SLOT(exportSVG()));
    connect(m_savefile, SIGNAL(triggered()), this, SLOT(saveClicked()));

    m_zzinfo = new QAction(tr("Show &ZZ Formula"), this);
    connect(m_zzinfo, SIGNAL(triggered()), this, SLOT(showZZInfo()));
    m_zzinfo->setEnabled(false);

//    m_hidezeros = new QAction(tr("Hide &Zeros"), this);
//    m_hidezeros->setCheckable(true);
//    connect(m_hidezeros, SIGNAL(toggled(bool)), m_decomposer, SLOT(setHideZeros(bool)));

    m_undo = new QAction(tr("Undo"), this);
    m_redo = new QAction(tr("Redo"), this);
    connect(m_undo, SIGNAL(triggered()), this, SLOT(undo()));
    connect(m_redo, SIGNAL(triggered()), this, SLOT(redo()));
    m_undo->setEnabled(false);
    m_redo->setEnabled(false);
}

void MainWindow::createToolbars()
{
    m_toolbar = addToolBar(tr("General"));
    m_toolbar->addAction(m_newfile);
    m_toolbar->addAction(m_savefile);
    m_toolbar->addSeparator();
    m_toolbar->addAction(m_undo);
    m_toolbar->addAction(m_redo);
    m_toolbar->addSeparator();
    m_toolbar->addAction(m_zzinfo);

    QAction *test = new QAction(tr("Rotate Grid"),this);
    test->setCheckable(true);
    connect(test, SIGNAL(toggled(bool)),this, SLOT(setGridRotate(bool)));
    m_toolbar->addAction(test);


    m_toolbar->addSeparator();
    m_toogleSeparateFragments = new QAction(tr("Separate fragments"),this);
    m_toogleSeparateFragments->setCheckable(true);
    m_toogleSeparateFragments->setChecked(true);
    m_toogleSeparateFragments->setEnabled(false);
    connect(m_toogleSeparateFragments, SIGNAL(triggered(bool)),this, SLOT(toggleSeparateFragments(bool)));
    m_toolbar->addAction(m_toogleSeparateFragments);

//    test = new QAction(tr("Set atom links"),this);
//    connect(test, SIGNAL(triggered()),this, SLOT(test()));
//    m_toolbar->addAction(test);

//    m_toolbar->addAction(m_hidezeros);

}

void MainWindow::createMenus()
{
    QMenu* menu = menuBar()->addMenu(tr("&File"));
    menu->addAction(tr("&Exit"), this, SLOT(close()));

    menu = menuBar()->addMenu(tr("&Advance"));
    menu->addAction(tr("&Take screenshot"), this, SLOT(screenshot()));

    menu = menuBar()->addMenu(tr("&Help"));
    menu->addAction(tr("&About Qt..."), this, SLOT(showAboutQt()) );
    menu->addAction(tr("&About..."), this, SLOT(showAbout()));
}

void MainWindow::createDocks()
{
}

void MainWindow::saveClicked()
{
    if ( m_tabWidget->currentIndex() == 0)
    {
        GraphModel* mo = m_builder->getGraphModel();
        if (!mo->isEmpty())
            export_structure(mo);
        delete mo;
    }
    else if (m_tabWidget->currentIndex() == 1)
    {
        bool comp;
        QString filename = getSVGExportFilename(this,&comp);
        if (!filename.isNull())
        {
            m_decomposer->exportSVG(filename, comp);
        }
    }
    else if (m_tabWidget->currentIndex() == 2)
    {
        m_identDecomposer->exportSVG();
    }

    // else if (m_tabWidget->currentIndex() == 4)
    // {
    //     bool comp;
    //     QString filename = getSVGExportFilename(this,&comp);
    //     m_zzAromaticityCalculatorPanel->exportSVG(filename, comp);

    // }
    // else if (m_tabWidget->currentIndex() == 5)
    // {
    //     bool comp;
    //     QString filename = getSVGExportFilename(this,&comp);
    //     m_zzSpinpopulaitonCalculatorPanel->exportSVG(filename, comp);

    // }

    // else if (m_tabWidget->currentIndex() == 6)
    // {
    //     bool comp;
    //     QString filename = getSVGExportFilename(this,&comp);
    //     m_zzSpinpopulaitonCalculatorPanel2->exportSVG(filename, comp);

    // }
    // else if (m_tabWidget->currentIndex() == 7)
    // {
    //     bool comp;
    //     QString filename = getSVGExportFilename(this,&comp);
    //     m_zzSpinpopulaitonCalculatorPanel3->exportSVG(filename, comp);

    // }

    // else if (m_tabWidget->currentIndex() == 8)
    // {
    //     bool comp;
    //     QString filename = getSVGExportFilename(this,&comp);
    //     m_johanna->exportSVG(filename, comp);

    // }
}

void MainWindow::showZZInfo()
{
    if (m_tabWidget->currentIndex() == 2)
    {
        QString ZZ = m_identDecomposer->getZZPolynomial();
        QMessageBox msgBox;

        msgBox.setText(ZZ);
        msgBox.setDetailedText(ZZ);
        msgBox.exec();
    }
    else if (m_tabWidget->currentIndex() == 1)
    {
        QString ZZ = m_decomposer->getZZPolynomial();
        QMessageBox msgBox;

        msgBox.setText(ZZ);
        msgBox.setDetailedText(ZZ);
        msgBox.exec();
    }

}

void MainWindow::showAbout()
{
    QMessageBox msgBox;
    QString version("Version: %1.%2.%3 <br>Website:<a href='http://qcl.ac.nctu.edu.tw/zzdecomposer'>http://qcl.ac.nctu.edu.tw/zzdecomposer</a><br>Email: sol.chou@gmail.com<br>Powered by Chien-Pin Chou");
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setText(version.arg(VERSION_MAJOR).arg(VERSION_MINOR).arg(VERSION_REVISION));
    msgBox.setWindowTitle("ZZDecomposer");
    msgBox.exec();
}

void MainWindow::showAboutQt()
{
    QMessageBox::aboutQt(this,tr("GZZDecomposer"));
}

void MainWindow::undo()
{
    if (m_tabWidget->currentIndex()==2)
    {
        m_identDecomposer->undo();
    }
}

void MainWindow::redo()
{
    if (m_tabWidget->currentIndex()==2)
    {
        m_identDecomposer->redo();
    }
}

void MainWindow::processZZPolynomialRequest(GraphModel *model)
{

    m_zzCalculatorPanel->addRowAndRun(model);
    m_porsche->addRowAndRun(model);
    //    m_tabWidget->setCurrentWidget(m_zzCalculatorPanel);
}

void MainWindow::builderProcessZZPolynomialRequest(GraphModel *model)
{
    if (m_workingGraphModel == NULL)
    {
        m_workingGraphModel = m_builder->getGraphModel();
        if ( m_workingGraphModel->isEmpty())
        {
            delete m_workingGraphModel;
            m_workingGraphModel = NULL;
        }
        else
        {
            m_zzCalculatorPanel->addRowAndRun(model);
            m_porsche->addRowAndRun(model);
        }

    }
}

void MainWindow::setGridRotate(bool rotate)
{
    m_builder->setGridRotate(rotate);
    m_decomposer->setGridRotate(rotate);
}

void MainWindow::toggleSeparateFragments(bool isSeparated)
{
    QMessageBox qbox(this);
    qbox.setWindowTitle(tr("ZZDecomposer"));
    qbox.setText(tr("Changing the fragment separation mode will reset the decomposer. Continue?"));
    qbox.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    qbox.setIcon(QMessageBox::Question);
    int ret = qbox.exec();
    if (ret == QMessageBox::Yes)
    {
        m_decomposer->clear();
        m_decomposer->setAllowFragments(isSeparated);
        m_decomposer->setRootGraph(this->m_builder->getGraphModel());

    }
    else
    {
        m_toogleSeparateFragments->toggle();
        return;
    }
}

void MainWindow::test()
{
    GraphModel* model = m_builder->getGraphModel();
    if ( model->isEmpty())
    {
        return;
    }
    SetAtomLinkDialog dia(model);
    dia.resize(1024,767);
    int ret = dia.exec();
    if (ret == QDialog::Accepted)
    {
        m_decomposer->setRootGraph(model);
        m_workingGraphModel = model;
        m_tabWidget->setCurrentIndex(1);
    }
}

void MainWindow::screenshot()
{
    QString filename = QFileDialog::getSaveFileName(
           this,
           tr("Save screenshot to image"),
           QDir::homePath(),
           tr("png files (*.png)") );

    if( !filename.isNull() )
    {
        QPixmap image(this->width()*5.0, this->height()*5.0);
        QPainter painter;
        painter.begin(&image);
        double scale = 5.0;
        painter.scale(scale, scale);
        this->render(&painter);
        image.save(filename, "png",0);
    }

}

