#ifndef DECOMPOSERDIALOG_H
#define DECOMPOSERDIALOG_H

#include <QDialog>

class QAbstractButton;
class GraphModel;
class Decomposer;
class UniqueTagGenerator;
class DecomposerDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DecomposerDialog(UniqueTagGenerator* tagGen, QWidget *parent = 0);
    void setRootGraphModel(GraphModel* model);
    QList<GraphModel*> getLeafs();

signals:
    void ZZPolynomialRequest(GraphModel* model);
public slots:

protected:
    void keyPressEvent(QKeyEvent *e);
private slots:
    void childZZPolynomialRequest(GraphModel* model);
private:
    Decomposer* m_decomposer;
//    GraphModel* m_rootGraphModel;
};

#endif // DECOMPOSERDIALOG_H
