#ifndef GZZCALCULATORJOB_H
#define GZZCALCULATORJOB_H

#include <QObject>



class GraphModel;
class QTableWidget;
class QTableWidgetItem;
class QPushButton;
class GZZPolynomialCalculator;

class GZZCalculatorJob : public QObject
{
    Q_OBJECT
public:
    GZZCalculatorJob(GraphModel* model, GraphModel* ori_model, QObject *parent = 0);
    QWidget* getCancelWidget();
    QTableWidgetItem* getResultItem();
signals:
    void removed(GZZCalculatorJob* job);
    void updated(GZZCalculatorJob* job);
public slots:
    void start();
private slots:
    void cancelClicked();
    void startClicked();
    void calcFinished();

private:
    GraphModel* m_model;
    GraphModel* m_ori_model;
    QTableWidget* m_cancelWidget;
    QPushButton* m_startButton;
    QPushButton* m_showClarButton;
    QPushButton* m_cancelButton;
    QTableWidgetItem* m_result;
    GZZPolynomialCalculator* m_calc;
    bool m_canceled;
};

#endif // GZZCALCULATORJOB_H
