#include "zzpolynomialresultdelegate.h"

#include <QtWidgets>

// #include <QApplication>
// #include <QClipboard>
// #include <QTableWidgetItem>
ZZPolynomialResultDelegate::ZZPolynomialResultDelegate()
{
    text = new QStaticText();

    text->setTextFormat(Qt::RichText);
    QTextOption opt;

    opt.setWrapMode(QTextOption::WordWrap);
//    opt.setAlignment(Qt::AlignVCenter);
    text->setTextOption(opt);
}

QSize ZZPolynomialResultDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &) const
{
    return option.rect.size();
}

QWidget *ZZPolynomialResultDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const
{
    QTextEdit* editor = new QTextEdit(parent);
    return editor;
}

void ZZPolynomialResultDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QTextEdit* myeditor = qobject_cast<QTextEdit*>(editor);
    myeditor->setText(index.model()->data(index,98).toString());
    myeditor->setReadOnly(false);
    myeditor->selectAll();
    myeditor->setFocus();
}

void ZZPolynomialResultDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const
{
    editor->setGeometry(option.rect);
}

ZZPolynomialResultDelegate::~ZZPolynomialResultDelegate()
{
    delete text;
}

void ZZPolynomialResultDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QFont font;
    font.setFamily("Times New Roman");
    font.setPixelSize(20);

    QString str = index.model()->data(index,99).toString();

    text->setText(str);
    text->prepare(QTransform(), font);

//    qDebug() << option.rect;

    painter->save();
    text->setTextWidth(option.rect.width());



    painter->setFont(font);

    text->prepare();

    painter->drawStaticText(option.rect.left()+5,option.rect.top()+5,*text);
    painter->restore();

}
