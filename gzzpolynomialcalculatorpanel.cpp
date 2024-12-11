#include "gzzpolynomialcalculatorpanel.h"

#include "graphdelegate.h"
#include "graphmodel.h"
#include <QtWidgets>

#include "gzzcalculatorjob.h"
#include "zzpolynomialresultdelegate.h"
#include "graphmodelgraphicsitem5.h"

porsche::porsche(QWidget *parent) :
    QWidget(parent)
{
    QGridLayout *layout = new QGridLayout(this);

    m_tableView = new QTableWidget(this);
    m_tableView->setSelectionMode(QAbstractItemView::NoSelection);
    m_tableView->setColumnCount(3);
    // tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);    //qtableWidgetItem can not edit 

    m_tableView->verticalHeader()->hide();
    m_tableView->horizontalHeader()->hide();

    m_tableView->setShowGrid(false);
    GraphDelegate<GraphModelGraphicsItem5> *gd = new GraphDelegate<GraphModelGraphicsItem5>(m_tableView, false, this);
    gd->setDrawRect(false);
    m_tableView->setItemDelegateForColumn(1,gd);
    m_tableView->setItemDelegateForColumn(2,new ZZPolynomialResultDelegate());

    m_tableView->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Fixed);
    m_tableView->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Fixed);
    m_tableView->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Stretch);
    // m_tableView->horizontalHeader()->setResizeMode(1,QHeaderView::ResizeToContents);

    m_tableView->setColumnWidth(0,100);
    m_tableView->setColumnWidth(1,200);


    m_tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);


//    m_tableView->horizontalHeader()->setResizeMode(QHeaderView::Fixed);
//    m_tableView->verticalHeader()->setResizeMode(QHeaderView::Fixed);

    layout->addWidget(m_tableView,0,0,1,1);
    this->setLayout(layout);
}

void porsche::addRow(GraphModel *model)
{
    GraphModel* newmodel = new GraphModel(model->getEdges(),QList<EdgeModel>(),NULL,GraphModel::None,NULL);
    GZZCalculatorJob *job =  new GZZCalculatorJob(newmodel, model);
    m_jobs.append(job);
    m_tableView->insertRow(0);
    m_tableView->setCellWidget(0,0,job->getCancelWidget());
    m_tableView->setItem(0,2,job->getResultItem());
    // m_tableView->setItem(0,2,new QTableWidgetItem("Porsche_test"));
    QTableWidgetItem *item = new QTableWidgetItem();
    item->setData(99,qVariantFromValue((void*)newmodel));
    m_tableView->setItem(0,1,item);

    connect(job, SIGNAL(removed(GZZCalculatorJob*)), this, SLOT(jobRemoved(GZZCalculatorJob*)));
    connect(job, SIGNAL(updated(GZZCalculatorJob*)), this, SLOT(jobUpdated(GZZCalculatorJob*)));
}


void porsche::jobRemoved(GZZCalculatorJob *job)
{
    int row = job->getResultItem()->row();
    delete job;
    m_tableView->removeRow(row);
    m_jobs.removeOne(job);
}

void porsche::jobUpdated(GZZCalculatorJob *job)
{
    int row = job->getResultItem()->row();
    m_tableView->selectRow(row);
//    m_tableView->setSelectionBehavior(QA);
//    m_tableView->scrollToItem(job->getResultItem());
}

void porsche::addRowAndRun(GraphModel *model)
{
    addRow(model);
    m_jobs.last()->start();
}

