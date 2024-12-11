#ifndef GZZPOLYNOMIALCALCULATOR_H
#define GZZPOLYNOMIALCALCULATOR_H

#include <QThread>
#include "stringpolynomial.h"
#include <QProcess>

class GraphModel;

class GZZPolynomialCalculator : public QThread
{
    Q_OBJECT
public:
    GZZPolynomialCalculator(GraphModel* model, QObject *parent = 0);
    Polynomial<QString> getPoly();
    QString getTotal() const;
    QString getTotal2() const;


    bool hasError();
    const QString& getErrorMsg();
    void stop();
    void serialRun();
protected:
    void run();
signals:
    void resultReady(const QString &s);
public slots:
private slots:
//    void jobFinishedError(QProcess::ProcessError error );
//    void jobFinished( int exitCode, QProcess::ExitStatus exitStatus);
private:
    GraphModel* m_model;
    Polynomial<QString> m_poly;
    QString m_total_gzz;
    QString m_total_zz;
    bool m_hasError;
    QString m_errorMsg;
    QProcess *m_process;
//    QList<QList<std::array<int, 6> > > m_clar_strs;
};

#endif // GZZPOLYNOMIALCALCULATOR_H
