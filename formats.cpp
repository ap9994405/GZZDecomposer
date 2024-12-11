#include "formats.h"

#include <QFile>
#include <QTextStream>
#include "graphmodel.h"
#include "utils.h"

#include <QtWidgets>

inline uint qHash(const QPoint &key)
{
    QString str = QString("(%1,%2)").arg(key.x()).arg(key.y());
    QString hkey = QString(QCryptographicHash::hash(str.toStdString().c_str(),QCryptographicHash::Md5).toHex());
    return qHash(hkey);
}

void save_cml(const QString& filename, const GraphModel* model)
{
    QFile file(filename);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << "<?xml version=\"1.0\"?>" << endl;
    out << "<molecule xmlns=\"http://www.xml-cml.org/schema\">" << endl;
    out << "<atomArray>" << endl;

    QHash<QPoint, int> atomName;
    QHash<EdgeModel, int> bondOrder;

    int counter = 1;

    {
        QListIterator<EdgeModel>  it(model->getAllEdges());
        while(it.hasNext())
        {
            EdgeModel edge = it.next();
            if (!atomName.contains(edge.startPoint()))
                atomName.insert(edge.startPoint(), counter++);
            if (!atomName.contains(edge.endPoint()))
                atomName.insert(edge.endPoint(), counter++);
            bondOrder.insert(edge, 1);
        }
    }


    {
        QHashIterator<QPoint, int> it(atomName);
        QList<QPointF> points;
        QList<int> tags;
        QPointF cm(0.0,0.0);
        while(it.hasNext())
        {
            it.next();
            QPoint point = it.key();
            QPointF v1 = vertexXY2XY(point, 1.4);
            points.append(v1);
            cm += v1;
            int tag = it.value();
            tags.append(tag);

        }
        cm /= static_cast<double>(points.size());
        for(int i=0; i< points.size(); ++i)
        {
            QPointF v1 = points[i]-cm;
            int tag = tags[i];
            out << QString("<atom elementType=\"C\" id=\"a%1\" x2=\"%2\" y2=\"%3\"/>").arg(tag).arg(v1.x(),0,'f',6).arg(-v1.y(),0,'f',6) << endl;
        }


    }

    {
        QListIterator<EdgeModel> it(model->getDoubleBonds());
        while(it.hasNext())
        {
            bondOrder.insert(it.next(), 2);
        }
    }
    {
        QListIterator<QList<EdgeModel> > it(model->getRings());
        while(it.hasNext())
        {
            const QList<EdgeModel>& list = it.next();
            for(int i=0; i< list.size(); ++i)
            {
                bondOrder.insert(list[i], 4);
            }
        }
    }

    out << "</atomArray>" << endl;
    out << "<bondArray>" << endl;

    counter = 1;
    {
        QHashIterator<EdgeModel, int> it(bondOrder);
        while(it.hasNext())
        {
            it.next();
            EdgeModel edge = it.key();
            int order = it.value();
            if (order == 4 )
            {
                out << QString("<bond atomRefs2=\"a%1 a%2\" id=\"b%3\" order=\"%4\"/>").arg(atomName[edge.startPoint()]).arg(atomName[edge.endPoint()]).arg(counter++).arg("A") << endl;
            }
            else
            {
                out << QString("<bond atomRefs2=\"a%1 a%2\" id=\"b%3\" order=\"%4\"/>").arg(atomName[edge.startPoint()]).arg(atomName[edge.endPoint()]).arg(counter++).arg(order) << endl;
            }

        }
    }


    out << "</bondArray>" << endl;
    out << "</molecule>" << endl;



    file.close();

}


void save_xyz(const QString& filename, const GraphModel* model, bool connections)
{
    QFile file(filename);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);

//    QSet<QPoint> pointExisted;
//    QList<QPointF> points;
//    QPointF cm(0.0,0.0);

//    {
//        QListIterator<EdgeModel>  it(model->getEdges());
//        while(it.hasNext())
//        {
//            EdgeModel edge = it.next();
//            if (!pointExisted.contains(edge.startPoint()))
//            {
//                QPointF tmp = vertexXY2XY(edge.startPoint(), 1.4);
//                cm += tmp;
//                points.append(tmp);
//                pointExisted.insert(edge.startPoint());
//            }
//            if (!pointExisted.contains(edge.endPoint()))
//            {
//                QPointF tmp = vertexXY2XY(edge.endPoint(), 1.4);
//                cm += tmp;
//                points.append(tmp);
//                pointExisted.insert(edge.endPoint());
//            }
//        }
//    }

//    cm /= points.size();

//    out << points.size() << endl << "ZZDecomposer XYZ export" << endl;

//    QListIterator<QPointF> it(points);
//    while(it.hasNext())
//    {
//        QPointF point  = it.next();
//        out << QString("C  %1  %2  0.0000").arg(point.x()).arg(point.y()) << endl;
//    }

    out << model->getZZInput(connections, true);
//    qDebug() << model->getZZInput();

    file.close();
}
void export_structure(const GraphModel* model)
{
    QString filter;
    QString filename = QFileDialog::getSaveFileName(
           0,
           QString("Export structure as..."),
           QDir::homePath(),
           QString("XYZ format files(*.xyz);;XYZ with connections(*.xyz);;Chemical Markup Language (*.cml)"), &filter );

    if( !filename.isNull() )
    {
        if (filter == QString("Chemical Markup Language (*.cml)"))
        {
            save_cml(filename, model );
        }
        else if (filter == QString("XYZ format files(*.xyz)"))
        {
            save_xyz(filename, model, false );
        }
        else if (filter == QString("XYZ with connections(*.xyz)"))
        {
            save_xyz(filename, model, true );
        }
    }
}
