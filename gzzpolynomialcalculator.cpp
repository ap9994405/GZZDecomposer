#include "gzzpolynomialcalculator.h"

#include "graphmodel.h"
#include <QtWidgets>
#include <QtXml>
#include <QDebug>
#include <QThread>
#include <iostream>

#include <fstream>

using namespace std;



GZZPolynomialCalculator::GZZPolynomialCalculator(GraphModel* model, QObject *parent) :
    QThread(parent), m_model(model), m_hasError(false)
{
    this->setTerminationEnabled(true);
//    m_process = NULL ;
//    connect(m_process,SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(jobFinished(int,QProcess::ExitStatus)));
//    connect(m_process,SIGNAL(error(QProcess::ProcessError)), this, SLOT(jobFinishedError(QProcess::ProcessError)));
}

void GZZPolynomialCalculator::run()
{
    m_process = new QProcess();

    QString zzcalcname = "GZZCalculator.exe";

    m_poly.clear();

    // .at(0) is path of zzcalcname
    // cmd is the program we want to call
    QFileInfo cmdInfo = QFileInfo(QFileInfo(QCoreApplication::arguments().at(0)).absolutePath(),zzcalcname);

    if (!cmdInfo.exists() || !cmdInfo.isExecutable())
    {
        m_hasError = true;
        m_errorMsg = zzcalcname + " not found in the same path as GZZDecomposer";
        return;
    }
    QString cmd = cmdInfo.absoluteFilePath() ;

    // int nthreads = QThread::idealThreadCount() - 1;
    // if (nthreads < 1 )
    //     nthreads = 1;

    QStringList arguments;

    // arguments << "-x" << QString("%1").arg(nthreads);
    arguments << "-x" << "-B";
    QTemporaryFile file;
    if (file.open())
    {
        arguments << file.fileName();
        {
            QTextStream inOut(&file);
            inOut << m_model->getZZInput(true, false);  // input xyzfile
            std::string ZZInput = m_model->getZZInput(true, false).toStdString();
            std::ofstream InputData;
            int i=0;
            while (true)
            {   
                i += 1;
                std::string FileName = std::string("./Output/Output") + std::to_string(i) + std::string(".txt");
                std::ifstream checkfile(FileName);
                if (checkfile.good())   //check if file can open
                {   
                    checkfile.close();
                    continue;
                }
                else
                {
                    InputData.open(FileName);
                    if (InputData.is_open()) {
                        InputData << ZZInput << std::endl;  
                        InputData.close();
                        // std::cout << "File written successfully." << std::endl;
                    } 
                    else {
                        std::cerr << "Failed to open the file." << std::endl;
                    }
                    break;
                }
            }
        }

        m_process->start(cmd, arguments);
        m_process->waitForFinished(-1); // waiting for finish

        if (m_process->exitCode()!=0)   // if finish exitCode() == 0
        {
            m_hasError = true;
            m_errorMsg = zzcalcname + " crashed.";
            return;
        }

        QByteArray result = m_process->readAll();   // read output save in result
        QString t(result);  // convert QbyteArray into QString

        QDomDocument resultXML; // QDomDocument save XML 
        bool failed = !resultXML.setContent(t); // check t is XML format
        if (failed)
        {
            m_hasError = true;
            m_errorMsg = "The output from " + zzcalcname + " has wrong format1.";
            qDebug() << t << m_errorMsg;
            return;
        }
        else
        {
            int i=0;
            while (true)
            {   
                i += 1;
                std::string FileName = std::string("./Output/Output") + std::to_string(i) + std::string(".txt");
                std::ifstream checkfile(FileName);  // read
                std::ofstream OutputData;  // write
                if (checkfile.good())
                {
                    checkfile.close();
                    continue;
                }
                else
                {
                    i -= 1;
                    FileName = std::string("./Output/Output") + std::to_string(i) + std::string(".txt");
                    OutputData.open(FileName, std::ios::app);
                    if (OutputData.is_open()) 
                    {
                        OutputData << "-------------------------------------------" << std::endl;
                        OutputData << t.toStdString();
                        OutputData.close();
                    } 
                    break;
                }
            }
        }


        QDomElement gzzpoly = resultXML.documentElement();   // get root node(most top node) in resultXML
        if (gzzpoly.isNull() || gzzpoly.tagName() != "gzzpolynomial")
        {
            m_hasError = true;
            m_errorMsg = "The output from " + zzcalcname + " has wrong format2.";
            qDebug() << t << m_errorMsg;
            return;
        }
        // finding all node name
        QDomNodeList terms = gzzpoly.elementsByTagName("term");
        QDomNodeList total_zz = gzzpoly.elementsByTagName("total_zz");
        QDomNodeList total_gzz = gzzpoly.elementsByTagName("total_gzz");

        if (total_zz.count() == 1)
        {
            QDomElement total_elem = total_zz.at(0).toElement();
            QString total_str = total_elem.text();
            m_total_zz = total_str;
        }
        if (total_gzz.count() == 1)
        {
            QDomElement total_elem = total_gzz.at(0).toElement();
            QString total_str = total_elem.text();
            m_total_gzz = total_str;
        }
        for (int i = 0; i < terms.count(); ++i) //loop every term
        {
            QDomNode termNode = terms.item(i);  
            QDomElement termElem = termNode.toElement();    //termElem = terms(i) node
            QDomNodeList orders_x = termElem.elementsByTagName("order_x");  //get order node
            QDomNodeList orders_y = termElem.elementsByTagName("order_y");  //get order node
            QDomNodeList coeffs = termElem.elementsByTagName("coefficient");    //get coefficient node
            if (orders_x.count() != 1 || orders_y.count() != 1 || coeffs.count() != 1)
            {   
                m_hasError = true;
                m_errorMsg = "The output from " + zzcalcname + " has wrong format3.";
                qDebug() << t << m_errorMsg;
                return;
            }
            QDomElement orderElem_x = orders_x.at(0).toElement();   //turn QDomNode to QDomElement
            QDomElement orderElem_y = orders_y.at(0).toElement();   //turn QDomNode to QDomElement
            QDomElement coeffElem = coeffs.at(0).toElement();   //turn QDomNode to QDomElement
            
            int order_x = orderElem_x.text().toInt();
            int order_y = orderElem_y.text().toInt();
            QString coeff = coeffElem.text();

            m_poly.addTerm2(coeff,order_x,order_y);
            //qDebug() << coeff << order_x << order_y;
            // m_poly.addTerm(coeff,order_x);
        }
    }
    delete m_process;
}

Polynomial<QString> GZZPolynomialCalculator::getPoly()
{
    return m_poly;
}

QString GZZPolynomialCalculator::getTotal() const
{
    return m_total_gzz;
}
QString GZZPolynomialCalculator::getTotal2() const
{
    return m_total_zz;
}

bool GZZPolynomialCalculator::hasError()
{
    return m_hasError;
}

const QString & GZZPolynomialCalculator::getErrorMsg()
{
    return m_errorMsg;
}

void GZZPolynomialCalculator::stop()
{
    m_process->kill();
}

void GZZPolynomialCalculator::serialRun()
{
    run();
}

