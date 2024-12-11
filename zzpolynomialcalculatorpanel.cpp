#include "zzpolynomialcalculatorpanel.h"

#include "graphdelegate.h"
#include "graphmodel.h"
#include <QtWidgets>

#include "zzcalculatorjob.h"
#include "zzpolynomialresultdelegate.h"
#include "graphmodelgraphicsitem2.h"

ZZPolynomialCalculatorPanel::ZZPolynomialCalculatorPanel(QWidget *parent) :
    QWidget(parent)
{
    QGridLayout *layout = new QGridLayout(this);


    m_tableView = new QTableWidget(this);

    m_tableView->setSelectionMode(QAbstractItemView::NoSelection);
    m_tableView->setColumnCount(3);

    m_tableView->verticalHeader()->hide();
    m_tableView->horizontalHeader()->hide();

    m_tableView->setShowGrid(false);
    GraphDelegate<GraphModelGraphicsItem2> *gd = new GraphDelegate<GraphModelGraphicsItem2>(m_tableView, false, this);
    gd->setDrawRect(false);
    m_tableView->setItemDelegateForColumn(1,gd);
    m_tableView->setItemDelegateForColumn(2,new ZZPolynomialResultDelegate());

    // m_tableView->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Fixed);
    m_tableView->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Fixed);
    m_tableView->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Stretch);
//    m_tableView->horizontalHeader()->setResizeMode(1,QHeaderView::ResizeToContents);

    m_tableView->setColumnWidth(0,100);
    m_tableView->setColumnWidth(1,200);


    m_tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);


//    m_tableView->horizontalHeader()->setResizeMode(QHeaderView::Fixed);
//    m_tableView->verticalHeader()->setResizeMode(QHeaderView::Fixed);

    layout->addWidget(m_tableView,0,0,1,1);
    this->setLayout(layout);
}

void ZZPolynomialCalculatorPanel::addRow(GraphModel *model)
{
    GraphModel* newmodel = new GraphModel(model->getEdges(),QList<EdgeModel>(),NULL,GraphModel::None,NULL);
    ZZCalculatorJob *job =  new ZZCalculatorJob(newmodel, model);
    m_jobs.append(job);
    m_tableView->insertRow(0);
    m_tableView->setCellWidget(0,0,job->getCancelWidget());
    m_tableView->setItem(0,2,job->getResultItem());
    QTableWidgetItem *item = new QTableWidgetItem();
    item->setData(99,qVariantFromValue((void*)newmodel));
    m_tableView->setItem(0,1,item);

    connect(job, SIGNAL(removed(ZZCalculatorJob*)), this, SLOT(jobRemoved(ZZCalculatorJob*)));
    connect(job, SIGNAL(updated(ZZCalculatorJob*)), this, SLOT(jobUpdated(ZZCalculatorJob*)));
}


void ZZPolynomialCalculatorPanel::jobRemoved(ZZCalculatorJob *job)
{
    int row = job->getResultItem()->row();
    delete job;
    m_tableView->removeRow(row);
    m_jobs.removeOne(job);
}

void ZZPolynomialCalculatorPanel::jobUpdated(ZZCalculatorJob *job)
{
    int row = job->getResultItem()->row();
    m_tableView->selectRow(row);
//    m_tableView->setSelectionBehavior(QA);
//    m_tableView->scrollToItem(job->getResultItem());
}

void ZZPolynomialCalculatorPanel::addRowAndRun(GraphModel *model)
{
    addRow(model);
    m_jobs.last()->start();
}

