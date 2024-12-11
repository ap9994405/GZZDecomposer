#ifndef TAGMODIFICATIONDIALOG_H
#define TAGMODIFICATIONDIALOG_H

#include <QDialog>

class GraphModel;
namespace Ui {
class TagModificationDialog;
}

class TagModificationDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit TagModificationDialog(GraphModel* model, QWidget *parent = 0);
    ~TagModificationDialog();
    
private:
    Ui::TagModificationDialog *ui;
    GraphModel* m_model;

private slots:
    void beforeAccept();
    void updatePreview(const QString &str);
};

#endif // TAGMODIFICATIONDIALOG_H
