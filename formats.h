#ifndef FORMATS_H
#define FORMATS_H


#include <QString>

class GraphModel;
//void save_cml(const QString& filename, const GraphModel* model);
//void save_xyz(const QString& filename, const GraphModel* model);
void export_structure(const GraphModel *model);



#endif // FORMATS_H
