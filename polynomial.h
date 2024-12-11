#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <QList>
#include <QPair>
#include <QDebug>
#include <QStringList>

//multiplyTerm use for polynomial with x
//multiplyTerm2 use for polynomial with x and y
template<typename X>    // X is any data type
class Polynomial
{
    typedef QPair<X,QPair<unsigned,unsigned>> Term;
public:
    void clear()
    {
        m_terms.clear();
    }

    Polynomial<X>(){}

    Polynomial<X>(const Polynomial<X>& rhs)
    {
        //nothing happened when decompose
        m_terms = rhs.m_terms;
    }

    Polynomial<X> operator+(const Polynomial<X>& rhs)
    {
        Polynomial<X> new_poly(*this);
        new_poly+=rhs;
        return new_poly;
    }

    Polynomial<X>& operator+=(const Polynomial<X>& rhs)
    {
        QListIterator<Term> it(rhs.m_terms);
        while(it.hasNext())
        {
            const Term& term = it.next();
            addTerm(term.first, term.second.first,term.second.second);
        }
        return *this;
    }

    void multiplyTerm(X coeff,unsigned order_x,unsigned order_y)
    {
        // if (coeff == 0) m_terms.clear();
        QMutableListIterator<Term> it(m_terms);
        while(it.hasNext())
        {
            Term& term = it.next();
            term.second.second += order_y;
            term.second.first += order_x;
            term.first *= coeff;
        }
    }

    void addTerm(X coeff,unsigned order_x,unsigned order_y)
    {
        bool found_term = false;
        typename QList<Term>::iterator p;
        for(p=m_terms.begin();p!=m_terms.end();++p)
        {
            Term& term = *p;
            if (term.second.first == order_x && term.second.second == order_y)
            {
                term.first += coeff;
                found_term = true;
                break;
            }
            else if (term.second.first < order_x && term.second.second < order_y)
            {
                m_terms.insert(p,qMakePair(coeff,qMakePair(order_x,order_y)));
                found_term = true;
                break;
            }
        }
        if (!found_term)
        {
            m_terms.push_back(qMakePair(coeff,qMakePair(order_x,order_y)));
        }
    }

    bool isIdentity() const
    {
        if (m_terms.size()>1)
            return false;
        X a = getCoeff(0,0);
        if (a == X(1))
            return true;
        else
            return false;
    }

    Polynomial<X>& operator=(const Polynomial<X>& rhs)
    {
        m_terms = rhs.m_terms;
        return *this;
    }

    int degree() const
    {
        int d = 0;
        QListIterator<Term> it(m_terms);
        while(it.hasNext())
        {
            int o = it.next().second;
            if (o > d)
            {
                d = o;
            }
        }
        return d;
    }

    X getCoeff(unsigned order_x, unsigned order_y) const
    {
        X def(0);
        QListIterator<Term> it(m_terms);
        while(it.hasNext())
        {
            const Term& term = it.next();
            if (term.second.first == order_x || term.second.second == order_y)
            {
                return term.first;
            }
        }
        return def;
    }

    QString toHTML2() const
    {
        QStringList list;
        // term.first and term.second always divide by 2 because of unknown bug
        // both also have benn multiply by 2 in graphmodel.cpp
        if ( m_terms.isEmpty() )
        {
            list.append("0");
        }
        else
        {
            QListIterator<Term> it(m_terms);
            while(it.hasNext())
            {
                const Term& term = it.next();
                if (term.second.first == 0 && term.second.second == 0)
                {
                    list.append(QString("%1").arg(term.first));
                }
                else if (term.second.first == 1 && term.second.second == 0)
                {
                    if (term.first == 1 )
                    {
                        list.append(QString("<i>x</i>"));
                    }
                    else
                    {
                        list.append(QString("%1<i>x</i>").arg(term.first));
                    }
                }
                else if (term.second.first == 0 && term.second.second == 1)
                {
                    if (term.first == 1 )
                    {
                        list.append(QString("<i>y</i>"));
                    }
                    else
                    {
                        list.append(QString("%1<i>y</i>").arg(term.first));
                    }
                }
                else if (term.second.first == 1 && term.second.second == 1)
                {
                    if (term.first == 1 )
                    {
                        list.append(QString("<i>x</i><i>y</i>"));
                    }
                    else
                    {
                        list.append(QString("%1<i>x</i><i>y</i>").arg(term.first));
                    }
                }
                else if (term.second.first > 1 && term.second.second == 0)
                {
                    if (term.first == 1 )
                    {
                        list.append(QString("<i>x</i><sup>%1</sup>").arg(term.second.first));
                    }
                    else
                    {
                        list.append(QString("%1<i>x</i><sup>%2</sup>").arg(term.first).arg(term.second.first));
                    }
                }
                else if (term.second.first == 0 && term.second.second > 1)
                {
                    if (term.first == 1 )
                    {
                        list.append(QString("<i>y</i><sup>%1</sup>").arg(term.second.second));
                    }
                    else
                    {
                        list.append(QString("%1<i>y</i><sup>%2</sup>").arg(term.first).arg(term.second.second));
                    }
                }
                else if (term.second.first > 1 && term.second.second == 1)
                {
                    if (term.first == 1 )
                    {
                        list.append(QString("<i>x</i><sup>%1</sup><i>y</i>").arg(term.second.first));
                    }
                    else
                    {
                        list.append(QString("%1<i>x</i><sup>%2</sup><i>y</i>").arg(term.first).arg(term.second.first));
                    }
                }
                else if (term.second.first == 1 && term.second.second > 1)
                {
                    if (term.first == 1 )
                    {
                        list.append(QString("<i>x</i><i>y</i><sup>%1</sup>").arg(term.second.second));
                    }
                    else
                    {
                        list.append(QString("%1<i>x</i><i>y</i><sup>%2</sup>").arg(term.first).arg(term.second.second));
                    }
                }
                else if (term.second.first > 1 && term.second.second > 1)
                {
                    if (term.first == 1 )
                    {
                        list.append(QString("<i>x</i><sup>%1</sup><i>y</i><sup>%2</sup>").arg(term.second.first).arg(term.second.second));
                    }
                    else
                    {
                        list.append(QString("%1<i>x</i><sup>%2</sup><i>y</i><sup>%3</sup>").arg(term.first).arg(term.second.first).arg(term.second.second));
                    }
                }
                else
                {
                    qDebug() << "something wrong at toHTML2 in polynomial.h";
                }
            }
        }
        return list.join(" + ");
    }

    QString toHTML() const
    {
        QStringList list;
        // term.first and term.second always divide by 2 because of unknown bug
        // both also have benn multiply by 2 in graphmodel.cpp
        if ( m_terms.isEmpty() )
        {
            list.append("0");
        }
        else
        {
            QListIterator<Term> it(m_terms);
            while(it.hasNext())
            {
                const Term& term = it.next();
                if (term.second.first >= 1 && term.second.second == 0)
                    {
                        if (term.first == 1 )
                        {
                            list.append(QString("%1<i>x</i>").arg(term.first));
                        }
                        else
                        {
                            list.append(QString("%1<i>x</i><sup>%2</sup>").arg(term.first).arg(term.second.first));
                        }
                    }
                else if (term.second.first == 0 && term.second.second >= 1)
                    {
                        if (term.first == 1 )
                        {
                            list.append(QString("%1<i>y</i>").arg(term.first));
                        }
                        else
                        {
                            list.append(QString("%1<i>y</i><sup>%2</sup>").arg(term.first).arg(term.second.second));
                        }
                    }
                else if (term.second.first == 1 && term.second.second == 1)
                    {
                        list.append(QString("%1<i>x</i><i>y</i>").arg(term.first));
                    }
                else if (term.second.first > 1 && term.second.second == 1)
                    {
                        list.append(QString("%1<i>x</i><sup>%2</sup><i>y</i>").arg(term.first).arg(term.second.first));
                    }
                else if (term.second.first == 1 && term.second.second > 1)
                    {
                        list.append(QString("%1<i>x</i><i>y</i><sup>%2</sup>").arg(term.first).arg(term.second.second));
                    }
                else if (term.second.first > 1 && term.second.second > 1)
                    {
                        list.append(QString("%1<i>x</i><sup>%2</sup><i>y</i><sup>%3</sup>").arg(term.first).arg(term.second.first).arg(term.second.second));
                    }
                else
                {
                    list.append(QString("%1").arg(term.first));
                }
            }
        }
        return list.join(" + ");
    }

    QString toString()
    {
        QStringList list;

        if ( m_terms.isEmpty() )
        {
            list.append("0");
        }
        else
        {
            QListIterator<Term> it(m_terms);
            while(it.hasNext())
            {
                const Term& term = it.next();
                if (term.second.second >1)
                {
                    if (term.second.first == 1)
                    {
                        list.append(QString("x^%1").arg(term.second.second));
                    }
                    else
                    {
                        list.append(QString("%1*x^%2").arg(term.second.first).arg(term.second.second));
                    }
                }
                else if ( term.second.second > 0)
                {
                    if (term.first == 1)
                    {
                        list.append(QString("x"));
                    }
                    else
                    {
                        list.append(QString("%1*x").arg(term.second.first));
                    }
                }
                else
                {
                    list.append(QString("%1").arg(term.second.first));
                }
            }
        }
        return list.join(" + ");
    }

    bool isEmpty()
    {
        return m_terms.isEmpty();
    }
    int numOfTerms()
    {
        return m_terms.size();
    }

protected:
private:
    QList<Term> m_terms;
};




#endif // POLYNOMIAL_H
