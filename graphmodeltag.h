#ifndef GRAPHMODELTAG_H
#define GRAPHMODELTAG_H

#include <QGraphicsRectItem>
#include <QGraphicsProxyWidget>
#include <QLineEdit>
#include <QRegExpValidator>
#include "graphmodel.h"


class GraphModelTag : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    GraphModelTag(GraphModel* model, const QFont &font = QFont(), QGraphicsItem *parentItem = 0,  QObject *parent = 0);
    ~GraphModelTag();
signals:
    void tagChanged();
public slots:
    void setFont(const QFont &font);
    void setText(const QString &text, bool html = true);
private slots:
    void finishEditing();
    void textChanging(const QString &text);
    void adjustEditBoxPosition(const QString &text);
    void setTag(const QString& tag);
private:
    QString m_text;
    QGraphicsTextItem* m_textitem;
    QLineEdit *m_edit;
    QGraphicsProxyWidget *m_proxy;
    GraphModel* m_model;


protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};

#endif // GRAPHMODELTAG_H
