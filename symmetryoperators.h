#ifndef SYMMETRYOPERATORS_H
#define SYMMETRYOPERATORS_H

#include <QPointF>
#include <QString>
#include <cmath>

const double PI = std::acos(-1.0);

class BaseSymmetryOperator
{
public:
    virtual QPointF operator()(const QPointF& point) const = 0 ;
    virtual int order() const = 0;
    virtual QString name() const = 0 ;
    virtual ~BaseSymmetryOperator(){}
};

class IdentityOperator : public BaseSymmetryOperator
{
public:
    QPointF operator ()(const QPointF &point) const
    {
        return point;
    }
    int order() const
    {
        return 1;
    }
    QString name() const
    {
        return "E";
    }
};

class RotationOperator : public BaseSymmetryOperator
{
public:
    RotationOperator(const QPointF& cp, double fold)
    {
        center = cp;
        x11 = std::cos(2.0*PI/static_cast<double>(fold));
        x12 = -std::sin(2.0*PI/static_cast<double>(fold));
        m_fold = fold;
    }

    virtual QPointF operator ()(const QPointF &point) const
    {
        QPointF ala = point - center;
        QPointF ala_f = QPointF(x11*ala.x()+x12*ala.y(), -x12*ala.x()+x11*ala.y())+center;
        return ala_f;
    }
private:
    QPointF center;
    double x11, x12;
    int m_fold;

public:
    virtual int order() const
    {
        return m_fold;
    }

    virtual QString name() const
    {
        return QString("C%1").arg(m_fold);
    }
};

class ReflectionOperator: public BaseSymmetryOperator
{
public:
    ReflectionOperator(const QPointF& centerp)
    {
        center = centerp;
        x11 = 1.0;
        x12 = x21 = 0.0;
        x22 = -x11;
    }
    virtual QPointF operator ()(const QPointF &point) const
    {
        QPointF ala = point - center;
        QPointF ala_f = QPointF(x11*ala.x()+x12*ala.y(), x21*ala.x()+x22*ala.y())+center;
        return ala_f;
    }
    virtual int order() const
    {
        return 2;
    }
    virtual QString name() const
    {
        return QString("R0");
    }
private:
    QPointF center;
protected:
    double x11, x12, x21, x22;
};

class ReflectionOperatorP30: public ReflectionOperator
{
public:
    ReflectionOperatorP30(const QPointF& centerp): ReflectionOperator(centerp)
    {
        x11 = 0.5;
        x12 = 0.5*std::sqrt(3.0);
        x21 = x12;
        x22 = -x11;
    }
    virtual QString name() const
    {
        return QString("RP30");
    }
};

class ReflectionOperatorP60: public ReflectionOperator
{
public:
    ReflectionOperatorP60(const QPointF& centerp): ReflectionOperator(centerp)
    {
        x11 = -0.5;
        x12 = 0.5*std::sqrt(3.0);
        x21 = x12;
        x22 = -x11;
    }
    virtual QString name() const
    {
        return QString("RP60");
    }
};

class ReflectionOperator90: public ReflectionOperator
{
public:
    ReflectionOperator90(const QPointF& centerp): ReflectionOperator(centerp)
    {
        x11 = -1.0;
        x12 = 0.0;
        x21 = x12;
        x22 = -x11;
    }
    virtual QString name() const
    {
        return QString("RP90");
    }
};
class ReflectionOperatorM30: public ReflectionOperator
{
public:
    ReflectionOperatorM30(const QPointF& centerp): ReflectionOperator(centerp)
    {
        x11 = 0.5;
        x12 = -0.5*std::sqrt(3.0);
        x21 = x12;
        x22 = -x11;
    }
    virtual QString name() const
    {
        return QString("RM30");
    }
};
class ReflectionOperatorM60: public ReflectionOperator
{
public:
    ReflectionOperatorM60(const QPointF& centerp): ReflectionOperator(centerp)
    {
        x11 = -0.5;
        x12 = -0.5*std::sqrt(3.0);
        x21 = x12;
        x22 = -x11;
    }
    virtual QString name() const
    {
        return QString("RM60");
    }
};

#endif // SYMMETRYOPERATORS_H
