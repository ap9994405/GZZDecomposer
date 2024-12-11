#include "file_helpers.h"

#include <QFileDialog>

QString getSVGExportFilename(QWidget* parent, bool *compressed)
{
    QString selected_filter;
    QString filename = QFileDialog::getSaveFileName(
           parent,
           QObject::tr("Export SVG file"),
           QDir::homePath(),
           QObject::tr("Compressed SVG format (*.svgz);;SVG format (*.svg)"),
           &selected_filter);


    QString ext = ".svg";

    if (filename.isNull())
        return filename;

    if ( selected_filter == "Compressed SVG format (*.svgz)" )
    {
       *compressed = true;
        ext = ".svgz";
    }
    else
    {
        *compressed = false;
    }

    if (!filename.endsWith(ext))
    {
        filename.append(ext);
    }

    return filename;
}


