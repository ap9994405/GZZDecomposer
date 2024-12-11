#ifndef BUILDERVIEW_H
#define BUILDERVIEW_H

#include <QGraphicsView>

class ZoomableView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit ZoomableView(QWidget *parent = 0);
    virtual ~ZoomableView();
    ZoomableView(QGraphicsScene* scene, QWidget *parent = 0);
    void setZoomable(bool on);
protected:
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
signals:

public slots:
    void zoom(double value);
private:
    void setupDefaults();
    bool m_control;
    bool m_zoomable;
};

#endif // BUILDERVIEW_H
