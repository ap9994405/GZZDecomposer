#ifndef UNIQUETAGGENERATOR_H
#define UNIQUETAGGENERATOR_H
#include <QString>
#include <QHash>
#include <QList>
#include <QDataStream>
class GraphModel;

class UniqueTagGenerator
{
//    friend class QDataStream;
public:
    UniqueTagGenerator();
    UniqueTagGenerator(const UniqueTagGenerator& rhs);
    UniqueTagGenerator& operator=(const UniqueTagGenerator& rhs);
private:
    QHash<GraphModel*, QString> m_keymap;
    QHash<QString, GraphModel*> m_valuemap;
    int m_counter;
    QString nextTag();
public slots:
//    QList<GraphModel*> getModelList();
    void clear();
    void removeModel(GraphModel *model);
    QString getTagFromModel(GraphModel* model);
    GraphModel* getModelFromTag(const QString& tag);
};
#endif // UNIQUETAGGENERATOR_H
