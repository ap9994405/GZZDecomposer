#ifndef PORSCHE_H
#define PORSCHE_H

#include <QWidget>

class GraphModel;
//class QTableView;
class QTableWidget;
class QStandardItemModel;
class GZZCalculatorJob;
class porsche : public QWidget
{
    Q_OBJECT
public:
    explicit porsche(QWidget *parent = 0);


signals:

public slots:
    void addRow(GraphModel* model);
    void addRowAndRun(GraphModel* model);
private slots:
    void jobRemoved(GZZCalculatorJob* job) ;
    void jobUpdated(GZZCalculatorJob* job) ;
private:
    QTableWidget* m_tableView;
    QList<GZZCalculatorJob*> m_jobs;
};

#endif // PORSCHE_H
