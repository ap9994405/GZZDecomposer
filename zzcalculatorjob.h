#ifndef ZZCALCULATORJOB_H
#define ZZCALCULATORJOB_H

#include <QObject>



class GraphModel;
class QWidget;
class QTableWidgetItem;
class QPushButton;
class ZZPolynomialCalculator;

class ZZCalculatorJob : public QObject
{
    Q_OBJECT
public:
    ZZCalculatorJob(GraphModel* model, GraphModel* ori_model, QObject *parent = 0);
    QWidget* getCancelWidget();
    QTableWidgetItem* getResultItem();
signals:
    void removed(ZZCalculatorJob* job);
    void updated(ZZCalculatorJob* job);
public slots:
    void start();
private slots:
    void cancelClicked();
    void startClicked();
    void calcFinished();
private:
    GraphModel* m_model;
    GraphModel* m_ori_model;
    QWidget* m_cancelWidget;
    QPushButton* m_startButton;
    QPushButton* m_showClarButton;
    QPushButton* m_cancelButton;
    QTableWidgetItem* m_result;
    ZZPolynomialCalculator* m_calc;
    bool m_canceled;
};

#endif // ZZCALCULATORJOB_H
