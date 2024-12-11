#include "uniquetaggenerator.h"
#include <QtWidgets>


UniqueTagGenerator::UniqueTagGenerator(): m_counter(1)
{
}

UniqueTagGenerator::UniqueTagGenerator(const UniqueTagGenerator &rhs)
{
    this->m_counter = rhs.m_counter;
    this->m_keymap = rhs.m_keymap;
    this->m_valuemap = rhs.m_valuemap;
}

UniqueTagGenerator &UniqueTagGenerator::operator =(const UniqueTagGenerator &rhs)
{
    this->m_counter = rhs.m_counter;
    this->m_keymap = rhs.m_keymap;
    this->m_valuemap = rhs.m_valuemap;
    return *this;
}


//QList<GraphModel *> UniqueTagGenerator::getModelList()
//{
//    return m_keymap.keys();
//}

void UniqueTagGenerator::clear()
{
    m_counter = 1;
    m_keymap.clear();
    m_valuemap.clear();
}

QString UniqueTagGenerator::nextTag()   //creat new tag
{
    bool used = true;
    QString _nextTag;
    m_counter = 1;
    while(used)
    {
        _nextTag = QString("A%1").arg(m_counter);
        m_counter += 1;
        if (!m_valuemap.contains(_nextTag))
            used = false;
    }
    return _nextTag;
}

void UniqueTagGenerator::removeModel(GraphModel *model)
{
    if (m_keymap.contains(model))
    {
        QString value = m_keymap[model];
        m_valuemap.remove(value);
        m_keymap.remove(model);
    }
}

QString UniqueTagGenerator::getTagFromModel(GraphModel *model)
{
    if (m_keymap.contains(model))   //QHash<key,value> .contain(key) check whether key exist
    {
        return m_keymap[model]; //return Tag (value)
    }
    else
    {
        QString _nextTag = nextTag();
        m_keymap.insert(model, _nextTag);   //QHash<GraphModel*, QString> m_keymap;
        m_valuemap.insert(_nextTag, model); //QHash<QString, GraphModel*> m_valuemap;
        return _nextTag;
    }
}


GraphModel *UniqueTagGenerator::getModelFromTag(const QString &tag)
{
    if (m_valuemap.contains(tag))
    {
        return m_valuemap[tag];
    }
    else
    {
        return NULL;
    }
}
//QDataStream &operator<<(QDataStream &out, const UniqueTagGenerator &generator)
//{
//    out << generator.m_counter << generator.m_keymap << generator.m_valuemap;
//}
//QDataStream &operator>>(QDataStream &in, UniqueTagGenerator &generator)
//{
//    in >> generator.m_counter >> generator.m_keymap >> generator.m_valuemap;
//}
