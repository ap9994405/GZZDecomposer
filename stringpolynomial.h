#ifndef STRINGPOLYNOMIAL_H
#define STRINGPOLYNOMIAL_H

#include <QString>
#include <QDebug>
#include "polynomial.h"
#include <tuple>


template<>
class Polynomial<QString>
{
    typedef QPair<QString,unsigned> Term;
    typedef std::tuple <QString, unsigned, unsigned> GTerm;
    
public:
    void clear()
    {
        m_terms.clear();
        m_gterms.clear();
    }

    Polynomial<QString>(){}

    Polynomial<QString>(const Polynomial<QString>& rhs)
    {
        m_terms = rhs.m_terms;
        m_gterms = rhs.m_gterms;
    }
    void addTerm(QString coeff,unsigned order)
    {
        if (coeff == 0) return;
        bool found_term = false;

        QList<Term>::iterator p;
        for(p=m_terms.begin();p!=m_terms.end();++p)
        {
            Term& term = *p;
            if (term.second == order)
            {
                term.first += coeff;
                found_term = true;
                break;
            }
            else if (term.second < order)
            {
                m_terms.insert(p,qMakePair(coeff,order));
                found_term = true;
                break;
            }
        }
        if (!found_term)
        {
            m_terms.push_back(qMakePair(coeff,order));
        }
    }

    void addTerm2(QString coeff,unsigned order_x,unsigned order_y)
    {
        if (coeff == 0) return;
        bool found_term = false;
        QList<GTerm>::iterator p;
        for(p=m_gterms.begin();p!=m_gterms.end();++p)
        {   
            GTerm& gterm = *p;
            if (std::get<1>(gterm) == order_x && std::get<2>(gterm) == order_y )//|| std::get<2>(gterm) == order_y
            {
                std::get<0>(gterm) += coeff;
                found_term = true;
                break;
            }
            else if (std::get<1>(gterm) < order_x || std::get<2>(gterm) < order_y)
            {
                m_gterms.insert(p,std::make_tuple(coeff, order_x, order_y));
                found_term = true;
                break;
            }
        }
        if (!found_term)
        {   
            m_gterms.push_back(std::make_tuple(coeff, order_x, order_y));
        }
    }

    bool isIdentity()   //wrong at gzz
    {
        if (m_terms.size()>1)
            return false;
        QString a = getCoeff(0);
        if (a == "")
            return true;
        else
            return false;
    }

    Polynomial<QString>& operator=(const Polynomial<QString>& rhs)
    {
        m_terms = rhs.m_terms;
        return *this;
    }
    
    int degree()
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

    QString getCoeff(unsigned order) const
    {
        QString def = "0";
        QListIterator<Term> it(m_terms);
        while(it.hasNext())
        {
            const Term& term = it.next();
            if (term.second == order)
            {
                return term.first;
            }
        }
        return def;
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
                if (term.second >1)
                {
                    if (term.first == "1")
                    {
                        list.append(QString("x^%1").arg(term.second));
                    }
                    else
                    {
                        list.append(QString("%1*x^%2").arg(term.first).arg(term.second));
                    }
                }
                else if ( term.second > 0)
                {
                    if (term.first == "1")
                    {
                        list.append(QString("x"));
                    }
                    else
                    {
                        list.append(QString("%1*x").arg(term.first));
                    }
                }
                else
                {
                    list.append(QString("%1").arg(term.first));
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
    QString toHTML() const
    {
        QStringList list;
        if ( m_terms.isEmpty() )
        {
            list.append("0aaa");
        }
        else
        {
            QListIterator<Term> it(m_terms);
            while(it.hasNext())
            {
                const Term& term = it.next();
                if (term.second >1)
                {
                    if (term.first == "1")
                    {
                        list.append(QString("<i>x</i><sup>%1</sup>").arg(term.second));
                    }
                    else
                    {
                        list.append(QString("%1<i>x</i><sup>%2</sup>").arg(term.first).arg(term.second));
                    }
                }
                else if ( term.second > 0)
                {
                    if (term.first == "1")
                    {
                        list.append(QString("<i>x</i>"));
                    }
                    else
                    {
                        list.append(QString("%1<i>x</i>").arg(term.first));
                    }
                }
                else
                {
                    list.append(QString("%1").arg(term.first));
                }
            }
        }
        return list.join(" + ");
    }

    QString toHTML2() const
    {
        QStringList list;
        if ( m_gterms.isEmpty() )
        {   
            list.append("0");
        }
        else
        {
            QListIterator<GTerm> it(m_gterms);
            while(it.hasNext())
            {
                const GTerm& gterm = it.next();
                if ( std::get<1>(gterm) >1 && std::get<2>(gterm) >1)
                {
                    if (std::get<0>(gterm) == "1")
                    {
                        list.append(QString("<i>x</i><sup>%1</sup><i>y</i><sup>%2</sup>").arg(std::get<1>(gterm)).arg(std::get<2>(gterm)));
                    }
                    else
                    {
                        list.append(QString("%1<i>x</i><sup>%2</sup><i>y</i><sup>%3</sup>").arg(std::get<0>(gterm)).arg(std::get<1>(gterm)).arg(std::get<2>(gterm)));
                    }
                }
                else if ( std::get<1>(gterm) == 1 &&  std::get<2>(gterm) > 1)
                {
                    if (std::get<0>(gterm) == "1")
                    {
                        list.append(QString("<i>x</i><i>y</i><sup>%1</sup>").arg(std::get<2>(gterm)));
                    }
                    else
                    {
                        list.append(QString("%1<i>x</i><i>y</i><sup>%2</sup>").arg(std::get<0>(gterm)).arg(std::get<2>(gterm)));
                    }
                }
                else if ( std::get<1>(gterm) > 1 && std::get<2>(gterm) == 1)
                {
                    if (std::get<0>(gterm) == "1")
                    {
                        list.append(QString("<i>x</i><sup>%1</sup><i>y</i>").arg(std::get<1>(gterm)));
                    }
                    else
                    {
                        list.append(QString("%1<i>x</i><sup>%2</sup><i>y</i>").arg(std::get<0>(gterm)).arg(std::get<1>(gterm)));
                    }
                }
                else if ( std::get<1>(gterm) == 1 && std::get<2>(gterm) == 1)
                {
                    if (std::get<0>(gterm) == "1")
                    {
                        list.append(QString("<i>x</i><i>y</i>"));
                    }
                    else
                    {
                        list.append(QString("%1<i>x</i><i>y</i>").arg(std::get<0>(gterm)));
                    }
                }
                else if ( std::get<1>(gterm) == 0 && std::get<2>(gterm) > 1)
                {
                    if (std::get<0>(gterm) == "1")
                    {
                        list.append(QString("<i>y</i><sup>%1</sup>").arg(std::get<2>(gterm)));
                    }
                    else
                    {
                        list.append(QString("%1<i>y</i><sup>%2</sup>").arg(std::get<0>(gterm)).arg(std::get<2>(gterm)));
                    }
                }
                else if ( std::get<1>(gterm) > 1 && std::get<2>(gterm) == 0)
                {
                    if (std::get<0>(gterm) == "1")
                    {
                        list.append(QString("<i>x</i><sup>%1</sup>").arg(std::get<1>(gterm)));
                    }
                    else
                    {
                        list.append(QString("%1<i>x</i><sup>%2</sup>").arg(std::get<0>(gterm)).arg(std::get<1>(gterm)));
                    }
                }
                else if ( std::get<1>(gterm) == 1 && std::get<2>(gterm) == 0)
                {
                    if (std::get<0>(gterm) == "1")
                    {
                        list.append(QString("<i>x</i>"));
                    }
                    else
                    {
                        list.append(QString("%1<i>x</i>").arg(std::get<0>(gterm)));
                    }
                }
                else if ( std::get<1>(gterm) == 0 && std::get<2>(gterm) == 1)
                {
                    if (std::get<0>(gterm) == "1")
                    {
                        list.append(QString("<i>y</i>"));
                    }
                    else
                    {
                        list.append(QString("%1<i>y</i>").arg(std::get<0>(gterm)));
                    }                
                }
                else
                {
                    list.append(QString("%1").arg(std::get<0>(gterm)));
                }
            }
        }
        return list.join(" + ");
    }

    QString toHTML3() const
    {
        QStringList list;
        if ( m_gterms.isEmpty() )
        {   
            list.append("0");
        }
        else
        {
            QListIterator<GTerm> it(m_gterms);
            while(it.hasNext())
            {
                const GTerm& gterm = it.next();
                //get<0>(gterm) = coeff, get<1>(gterm) = order_x get<2>(gterm) = order_y
                if ( std::get<1>(gterm) > 1 && std::get<2>(gterm) == 0)
                {
                    if (std::get<0>(gterm) == "1")
                    {
                        list.append(QString("<i>x</i><sup>%1</sup>").arg(std::get<1>(gterm)));
                    }
                    else
                    {
                        list.append(QString("%1<i>x</i><sup>%2</sup>").arg(std::get<0>(gterm)).arg(std::get<1>(gterm)));
                    }
                }
                else if ( std::get<1>(gterm) == 1 && std::get<2>(gterm) == 0)
                {
                    if (std::get<0>(gterm) == "1")
                    {
                        list.append(QString("<i>x</i>"));
                    }
                    else
                    {
                        list.append(QString("%1<i>x</i>").arg(std::get<0>(gterm)));
                    }
                }
                else if ( std::get<1>(gterm) == 0 && std::get<2>(gterm) == 0)
                {
                    list.append(QString("%1").arg(std::get<0>(gterm)));
                }
            }
        }
        return list.join(" + ");
    }

    QString toHTML2_2() const
    {
        QStringList list;
        if ( m_gterms.isEmpty() )
        {   
            list.append("0");
        }
        else
        {
            QListIterator<GTerm> it(m_gterms);
            while(it.hasNext())
            {
                const GTerm& gterm = it.next();
                if ( std::get<1>(gterm) >1 && std::get<2>(gterm) >1)
                {
                    if (std::get<0>(gterm) == "1")
                    {
                        list.append(QString("<i>x^</i>%1<i>*y^</i>%2").arg(std::get<1>(gterm)).arg(std::get<2>(gterm)));
                    }
                    else
                    {
                        list.append(QString("%1<i>*x^</i>%2<i>*y^</i>%3").arg(std::get<0>(gterm)).arg(std::get<1>(gterm)).arg(std::get<2>(gterm)));
                    }
                }
                else if ( std::get<1>(gterm) == 1 &&  std::get<2>(gterm) > 1)
                {
                    if (std::get<0>(gterm) == "1")
                    {
                        list.append(QString("<i>x</i><i>*y^</i>%1").arg(std::get<2>(gterm)));
                    }
                    else
                    {
                        list.append(QString("%1<i>*x</i><i>*y^</i>%2").arg(std::get<0>(gterm)).arg(std::get<2>(gterm)));
                    }
                }
                else if ( std::get<1>(gterm) > 1 && std::get<2>(gterm) == 1)
                {
                    if (std::get<0>(gterm) == "1")
                    {
                        list.append(QString("<i>x^</i>%1<i>*y</i>").arg(std::get<1>(gterm)));
                    }
                    else
                    {
                        list.append(QString("%1<i>*x^</i>%2<i>*y</i>").arg(std::get<0>(gterm)).arg(std::get<1>(gterm)));
                    }
                }
                else if ( std::get<1>(gterm) == 1 && std::get<2>(gterm) == 1)
                {
                    if (std::get<0>(gterm) == "1")
                    {
                        list.append(QString("<i>x</i><i>*y</i>"));
                    }
                    else
                    {
                        list.append(QString("%1<i>*x</i><i>*y</i>").arg(std::get<0>(gterm)));
                    }
                }
                else if ( std::get<1>(gterm) == 0 && std::get<2>(gterm) > 1)
                {
                    if (std::get<0>(gterm) == "1")
                    {
                        list.append(QString("<i>y^</i>%1").arg(std::get<2>(gterm)));
                    }
                    else
                    {
                        list.append(QString("%1<i>*y^</i>%2").arg(std::get<0>(gterm)).arg(std::get<2>(gterm)));
                    }
                }
                else if ( std::get<1>(gterm) > 1 && std::get<2>(gterm) == 0)
                {
                    if (std::get<0>(gterm) == "1")
                    {
                        list.append(QString("<i>x^</i>%1").arg(std::get<1>(gterm)));
                    }
                    else
                    {
                        list.append(QString("%1<i>*x^</i>%2").arg(std::get<0>(gterm)).arg(std::get<1>(gterm)));
                    }
                }
                else if ( std::get<1>(gterm) == 1 && std::get<2>(gterm) == 0)
                {
                    if (std::get<0>(gterm) == "1")
                    {
                        list.append(QString("<i>x</i>"));
                    }
                    else
                    {
                        list.append(QString("%1<i>*x</i>").arg(std::get<0>(gterm)));
                    }
                }
                else if ( std::get<1>(gterm) == 0 && std::get<2>(gterm) == 1)
                {
                    if (std::get<0>(gterm) == "1")
                    {
                        list.append(QString("<i>y</i>"));
                    }
                    else
                    {
                        list.append(QString("%1<i>*y</i>").arg(std::get<0>(gterm)));
                    }                
                }
                else
                {
                    list.append(QString("%1").arg(std::get<0>(gterm)));
                }
            }
        }
        return list.join(" + ");
    }

    QString toHTML3_2() const
    {
        QStringList list;
        if ( m_gterms.isEmpty() )
        {   
            list.append("0");
        }
        else
        {
            QListIterator<GTerm> it(m_gterms);
            while(it.hasNext())
            {
                const GTerm& gterm = it.next();
                //get<0>(gterm) = coeff, get<1>(gterm) = order_x get<2>(gterm) = order_y
                if ( std::get<1>(gterm) > 1 && std::get<2>(gterm) == 0)
                {
                    if (std::get<0>(gterm) == "1")
                    {
                        list.append(QString("<i>x^</i>%1").arg(std::get<1>(gterm)));
                    }
                    else
                    {
                        list.append(QString("%1<i>*x^</i>%2").arg(std::get<0>(gterm)).arg(std::get<1>(gterm)));
                    }
                }
                else if ( std::get<1>(gterm) == 1 && std::get<2>(gterm) == 0)
                {
                    if (std::get<0>(gterm) == "1")
                    {
                        list.append(QString("<i>x</i>"));
                    }
                    else
                    {
                        list.append(QString("%1<i>*x</i>").arg(std::get<0>(gterm)));
                    }
                }
                else if ( std::get<1>(gterm) == 0 && std::get<2>(gterm) == 0)
                {
                    list.append(QString("%1").arg(std::get<0>(gterm)));
                }
            }
        }
        return list.join(" + ");
    }

private:
    QList<Term> m_terms;
    QList<GTerm> m_gterms;
};
#endif // STRINGPOLYNOMIAL_H
