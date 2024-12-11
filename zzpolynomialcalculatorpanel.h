#ifndef ZZPOLYNOMIALCALCULATORPANEL_H
#define ZZPOLYNOMIALCALCULATORPANEL_H

#include <QWidget>

class GraphModel;
//class QTableView;
class QTableWidget;
class QStandardItemModel;
class ZZCalculatorJob;
class ZZPolynomialCalculatorPanel : public QWidget
{
    Q_OBJECT
public:
    explicit ZZPolynomialCalculatorPanel(QWidget *parent = 0);


signals:

public slots:
    void addRow(GraphModel* model);
    void addRowAndRun(GraphModel* model);
private slots:
    void jobRemoved(ZZCalculatorJob* job) ;
    void jobUpdated(ZZCalculatorJob* job) ;
private:
    QTableWidget* m_tableView;
    QList<ZZCalculatorJob*> m_jobs;
};

#endif // ZZPOLYNOMIALCALCULATORPANEL_H
