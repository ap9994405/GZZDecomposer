#include "zzcalculatorjob.h"

#include <QtWidgets>
#include "zzpolynomialcalculator.h"
// #include "gzzpolynomialcalculator.h"
#include "graphmodel.h"

ZZCalculatorJob::ZZCalculatorJob(GraphModel* model, GraphModel *ori_model, QObject *parent) :
    QObject(parent), m_canceled(false)
{

    m_cancelWidget = new QWidget();
    QGridLayout *l=new QGridLayout(m_cancelWidget);

    m_startButton = new QPushButton("Start");
    m_startButton->setMaximumHeight(30);

    m_showClarButton = new QPushButton("Show Clar");
    // m_showClarButton->setMaximumHeight(30);

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

    m_calc = new ZZPolynomialCalculator(model);

    m_result = new QTableWidgetItem();

    m_result->setText("Ready");
    m_result->setData(99,"Ready");

    connect(m_cancelButton, SIGNAL(clicked()), this, SLOT(cancelClicked()));
    connect(m_startButton, SIGNAL(clicked()), this, SLOT(startClicked()));
    connect(m_calc,SIGNAL(finished()), this, SLOT(calcFinished()));
}

void ZZCalculatorJob::cancelClicked()
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

void ZZCalculatorJob::calcFinished()
{
    m_cancelButton->setText("Remove");
    if (!m_calc->hasError())
    {
        m_result->setText(m_calc->getPoly().toString());
        // m_result->setData(100,m_calc->getPoly().toString() + "\n" + m_calc->getTotal());
        // m_result->setData(99,m_calc->getPoly().toHTML() + "<br>Total: " + m_calc->getTotal());
        m_result->setData(99,"ZZ polynomial <br>" + m_calc->getPoly().toHTML() + "<br>Total: " + m_calc->getTotal());
        // + "<br>" + " GZZ polynomial <br>" + m_calc->getPoly().toHTML() + "<br>Total: " + m_calc->getTotal());
        //m_result->setData(98,m_calc->getTotal());
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

QWidget * ZZCalculatorJob::getCancelWidget()
{
    return m_cancelWidget;
}

QTableWidgetItem * ZZCalculatorJob::getResultItem()
{
    return m_result;
}

void ZZCalculatorJob::start()
{
    m_startButton->setVisible(false);

    m_cancelButton->setText("Cancel");
    m_cancelButton->setVisible(true);

    m_result->setText("Calculating...");
    m_result->setData(99,"Calculating...");
    m_calc->start();
}

void ZZCalculatorJob::startClicked()
{
    if (!m_calc->isRunning() && !m_calc->isFinished())
    {
        start();    //running ZZCalculatorJob::run(), btw defult run() is empty
    }
}
