#ifndef ZZPOLYNOMIALCALCULATOR_H
#define ZZPOLYNOMIALCALCULATOR_H

#include <QThread>
#include "stringpolynomial.h"
#include <QProcess>

class GraphModel;

class ZZPolynomialCalculator : public QThread
{
    Q_OBJECT
public:
    ZZPolynomialCalculator(GraphModel* model, QObject *parent = 0);
    Polynomial<QString> getPoly();
    QString getTotal() const;


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
    QString m_total;
    bool m_hasError;
    QString m_errorMsg;
    QProcess *m_process;
//    QList<QList<std::array<int, 6> > > m_clar_strs;
};

#endif // ZZPOLYNOMIALCALCULATOR_H
