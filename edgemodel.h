#ifndef EDGEMODEL_H
#define EDGEMODEL_H
#include <QDebug>
#include <QPoint>
#include <QString>
#include <QHash>
#include <QCryptographicHash>

class EdgeModel
{
public:
    EdgeModel(const QPoint& start_pt, const QPoint& end_pt);
    EdgeModel();
protected:
    QPoint m_pt_start;
    QPoint m_pt_end;
public:
    QPoint startPoint() const;
    QPoint endPoint() const;
    void setStartPoint(const QPoint &p);
    void setEndPoint(const QPoint &p);
    bool connected(const EdgeModel& other);
    QString toString();
};

inline uint qHash(const EdgeModel &key)
{
    QString str = QString("[%1,%2]").arg(key.startPoint().x()+key.endPoint().x()).arg(key.startPoint().y()+key.endPoint().y());
    QString hkey = QString(QCryptographicHash::hash(str.toStdString().c_str(),QCryptographicHash::Md5).toHex());
    return qHash(hkey);
}

inline bool operator==(const EdgeModel &e1, const EdgeModel &e2)
{
    if (e1.startPoint() == e2.startPoint() && e1.endPoint() == e2.endPoint())
        return true;
    if (e1.startPoint() == e2.endPoint() && e1.endPoint() == e2.startPoint())
        return true;
    else
        return false;
}
#endif // EDGEMODEL_H
