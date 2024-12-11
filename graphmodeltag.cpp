#include "graphmodeltag.h"

#include <QDebug>
#include <QtWidgets>
#include <QFontMetricsF>

#include "uniquetaggenerator.h"
GraphModelTag::GraphModelTag(GraphModel *model, const QFont& font, QGraphicsItem *parentItem, QObject *parent) :
     QObject(parent), QGraphicsRectItem(parentItem)
{

    m_textitem = new QGraphicsTextItem(this);
    m_edit = new QLineEdit();
    m_edit->setEnabled(true);
    m_proxy = new QGraphicsProxyWidget();
    m_proxy->setEnabled(true);
    m_model = model;

    QFont tf(font);
    tf.setBold(true);
    this->setFont(tf);

    this->setText(model->getFullTag());
    this->setPen(QPen(Qt::NoPen));


    connect(m_edit, SIGNAL(editingFinished()), this, SLOT(finishEditing()));

    connect(m_edit,SIGNAL(textChanged(QString)),this, SLOT(textChanging(QString)));
}

GraphModelTag::~GraphModelTag()
{
    delete m_proxy;
}

void GraphModelTag::setFont(const QFont& font)
{
    m_textitem->setFont(font);
}

void GraphModelTag::setText(const QString& text, bool html)
{
    double oldwidth = m_textitem->boundingRect().width();
    m_text = text;
    if (html)
    {
        m_textitem->setHtml(m_text);
    }
    else
    {
        m_textitem->setPlainText(m_text);
    }
    QRectF rect = m_textitem->boundingRect();
    this->setRect(rect);
    double newwidth = m_textitem->boundingRect().width();
    this->moveBy(0.5*(oldwidth-newwidth),0.0);
}



void GraphModelTag::finishEditing()
{
    m_proxy->setVisible(false);
    setTag(m_edit->text());
}

void GraphModelTag::textChanging(const QString &text)
{
    setText(text,false);
    adjustEditBoxPosition(text);
    emit tagChanged();
}

void GraphModelTag::adjustEditBoxPosition(const QString& )
{
    QRectF rect = m_textitem->boundingRect();
    m_proxy->setGeometry(rect);
 }

void GraphModelTag::setTag(const QString &tag)
{
    QString text = tag.trimmed();
    if (text == m_model->getTag())
    {
        m_model->setCustomTag("");
    }
    else
    {
        if (text.startsWith("A"))
        {
            if (text[1].isNumber())
            {
                m_edit->setFocus();
                return;
            }
        }
        m_model->setCustomTag(text);
    }
    setText(m_model->getFullTag());
    m_textitem->setVisible(true);
    emit tagChanged();
}



void GraphModelTag::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *)
{

    if (m_model->hasCustomTag())
    {
        m_edit->setText(m_model->getCustomTag());
    }
    else
    {
        m_edit->setText(m_model->getTag());
    }

    m_edit->setEnabled(true);
    m_edit->setFont(m_textitem->font());
    m_edit->setFrame(true);

    m_proxy->setWidget(m_edit);
    m_proxy->setParentItem(this);   

    m_textitem->setVisible(false);
    m_proxy->setVisible(true);
    m_edit->selectAll();
    m_edit->setFocus();

    setText(m_text,false);
    adjustEditBoxPosition(m_text);
    emit tagChanged();
}
