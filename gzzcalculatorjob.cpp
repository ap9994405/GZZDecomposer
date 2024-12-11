#include "gzzcalculatorjob.h"

#include <QtWidgets>
#include "gzzpolynomialcalculator.h"
#include "graphmodel.h"
#include <typeinfo>
GZZCalculatorJob::GZZCalculatorJob(GraphModel* model, GraphModel *ori_model, QObject *parent) :
    QObject(parent), m_canceled(false)
{

    m_cancelWidget = new QTableWidget();
    // m_cancelWidget = new QWidget();
    QGridLayout *l=new QGridLayout(m_cancelWidget);

    m_startButton = new QPushButton("Start");
    m_startButton->setMaximumHeight(30);

    m_showClarButton = new QPushButton("Show Clar");

    m_cancelButton = new QPushButton("Remove");
    m_cancelButton->setMaximumHeight(30);
//    m_cancelButton->setVisible(false);

    m_showClarButton->setVisible(false);

    QVBoxLayout *vbl = new QVBoxLayout();
    vbl->addWidget(m_startButton);
    vbl->addWidget(m_showClarButton);
    vbl->addWidget(m_cancelButton);


    l->addLayout(vbl,0,0,0,0,Qt::AlignHCenter);


    m_model = model;
    m_ori_model = ori_model;

    m_calc = new GZZPolynomialCalculator(model);

    m_result = new QTableWidgetItem();

    m_result->setText("Ready");
    m_result->setData(99,"Ready");

    connect(m_cancelButton, SIGNAL(clicked()), this, SLOT(cancelClicked()));
    connect(m_startButton, SIGNAL(clicked()), this, SLOT(startClicked()));
    connect(m_calc,SIGNAL(finished()), this, SLOT(calcFinished()));
}

void GZZCalculatorJob::cancelClicked()
{
    if (m_calc->isRunning())
    {
        m_canceled = true;
        m_calc->stop();
        m_calc->wait();
    }
    else
    {
        emit removed(this);
    }
}

void GZZCalculatorJob::calcFinished()
{
    m_cancelButton->setText("Remove");
    if (!m_calc->hasError())
    {   
        // m_result->setFlags(Qt::ItemIsEnabled);
        // tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked);

        // m_result->setText(m_calc->getPoly().toString());
        // qDebug() << m_calc->getPoly();
        m_result->setText("ZZ polynomial <br>" + m_calc->getPoly().toHTML3() + "<br>Total: " + m_calc->getTotal2()+ "<br><br>" + "GZZ polynomial <br>" + m_calc->getPoly().toHTML2() + "<br>Total: " + m_calc->getTotal());
        // 99 is HTML format, 98 is HTML represents Maple format
        m_result->setData(99,"ZZ polynomial <br>" + m_calc->getPoly().toHTML3() + "<br>Total: " + m_calc->getTotal2()+ "<br><br>" + "GZZ polynomial <br>" + m_calc->getPoly().toHTML2() + "<br>Total: " + m_calc->getTotal());
        m_result->setData(98,"ZZ polynomial <br>" + m_calc->getPoly().toHTML3_2() + "<br>Total: " + m_calc->getTotal2()+ "<br><br>" + "GZZ polynomial <br>" + m_calc->getPoly().toHTML2_2() + "<br>Total: " + m_calc->getTotal());
        if (m_calc->getPoly().toString() == "0" )
        {
            m_ori_model->setDead(true);
        }
        m_showClarButton->setVisible(true);
    }
    else if (m_canceled)
    {
        m_result->setText("Canceled");
        m_result->setData(99,"Canceled");
    }
    else
    {
        m_result->setText(m_calc->getErrorMsg());
        m_result->setData(99,m_calc->getErrorMsg());
    }
    emit updated(this);
}

QWidget * GZZCalculatorJob::getCancelWidget()
{
    return m_cancelWidget;
}

QTableWidgetItem * GZZCalculatorJob::getResultItem()
{
    return m_result;
}

void GZZCalculatorJob::start()
{
    m_startButton->setVisible(false);

    m_cancelButton->setText("Cancel");
    m_cancelButton->setVisible(true);

    m_result->setText("Calculating...");
    m_result->setData(99,"Calculating...");
    m_calc->start();
}

void GZZCalculatorJob::startClicked()
{
    if (!m_calc->isRunning() && !m_calc->isFinished())
    {
        start();
    }
}