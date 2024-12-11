#include "zoomableview.h"
#include <QtWidgets>
#include <QFlags>

ZoomableView::ZoomableView(QWidget *parent) :
    QGraphicsView(parent)
{
    setupDefaults();
}

ZoomableView::~ZoomableView()
{

}


ZoomableView::ZoomableView(QGraphicsScene* scene, QWidget *parent):
    QGraphicsView(scene, parent)
{
    setupDefaults();
}

void ZoomableView::setZoomable(bool on)
{
    m_zoomable = on;
}

void ZoomableView::wheelEvent(QWheelEvent *event)
{
    if (m_zoomable && m_control)
    {
        QTransform qt = this->transform();
        double currentZoomFactor = sqrt(qt.determinant());
        double zoomFactor = currentZoomFactor + (event->delta() / 120.0)*0.05;
        zoom(zoomFactor);
    }
    else
    {
        QGraphicsView::wheelEvent(event);
    }
}

void ZoomableView::setupDefaults()
{
    m_zoomable = true;
    m_control = false;
    setMouseTracking(true);
    setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing | QPainter::TextAntialiasing);
    this->resetMatrix();
    this->scale(0.6,0.6);
}

void ZoomableView::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Control)
        m_control = true;
    else
        m_control = false;
    QGraphicsView::keyPressEvent(event);
}

void ZoomableView::keyReleaseEvent(QKeyEvent *event)
{
    m_control = false;
    QGraphicsView::keyReleaseEvent(event);
}

void ZoomableView::zoom(double zoomFactor)
{
    QTransform qt = this->transform();
    double currentZoomFactor = sqrt(qt.determinant());

    if (zoomFactor < 0.1)
        zoomFactor = 0.1;
    if (zoomFactor > 4.0)
        zoomFactor = 4.0;

    qt.scale(1.0/currentZoomFactor,1.0/currentZoomFactor);
    qt.scale(zoomFactor,zoomFactor);
    this->setTransform(qt);
}

