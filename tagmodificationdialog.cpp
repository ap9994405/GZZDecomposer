#include "tagmodificationdialog.h"
#include "ui_tagmodificationdialog.h"

#include "graphmodel.h"

TagModificationDialog::TagModificationDialog(GraphModel* model, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TagModificationDialog)
{
    ui->setupUi(this);

    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(updatePreview(QString)));
    connect(ui->buttonBox,SIGNAL(accepted()), this, SLOT(beforeAccept()));

    m_model = model;
    ui->lineEdit->setText(model->getFullTag());
    ui->lineEdit->selectAll();
    ui->lineEdit->setFocus();
}

TagModificationDialog::~TagModificationDialog()
{
    delete ui;
}

void TagModificationDialog::beforeAccept()
{
    if (!ui->lineEdit->isModified())
    {
        reject();
    }
    QString text = ui->lineEdit->text().trimmed();

    if (text == m_model->getTag())
    {
        m_model->setCustomTag("");
        accept();
    }
    else
    {
        if (text.startsWith("A"))
        {
            ui->lineEdit->setFocus();
            return;
        }
        m_model->setCustomTag(text);
    }
    accept();
}

void TagModificationDialog::updatePreview(const QString &str)
{
    QFont font;
    font.setPixelSize(26);
    font.setFamily("Times New Roman");
    ui->label_preview->setTextFormat(Qt::RichText);
    ui->label_preview->setText(str);
    ui->label_preview->setFont(font);
}
