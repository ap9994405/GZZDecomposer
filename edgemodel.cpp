#include "edgemodel.h"



void EdgeModel::setStartPoint(const QPoint &p)
{
    m_pt_start = p;
}

void EdgeModel::setEndPoint(const QPoint &p)
{
    m_pt_end = p;
}

bool EdgeModel::connected(const EdgeModel &other)
{
    if (this->startPoint() == other.startPoint() || this->startPoint() == other.endPoint() ||
            this->endPoint() == other.startPoint() || this->endPoint() == other.endPoint() )
    {
        return true;
    }
    return false;
}




EdgeModel::EdgeModel(const QPoint& start_pt, const QPoint& end_pt):m_pt_start(start_pt),m_pt_end(end_pt)
{
}

EdgeModel::EdgeModel()  //without any parameter
{
    m_pt_start = QPoint(0,0);
    m_pt_end = QPoint(0,0);
}

QPoint EdgeModel::startPoint() const
{
    return m_pt_start;
}

QPoint EdgeModel::endPoint() const
{
    return m_pt_end;
}

QString EdgeModel::toString()
{
    QString str = QString("[%1,%2]").arg(startPoint().x()+endPoint().x()).arg(startPoint().y()+endPoint().y());
    return str;
}


