#pragma once

#include <QTimer>
#include "map_impl.h"


namespace mapgl {

class BaseDraw : public MapImpl
{
    Q_OBJECT

public:
    BaseDraw(QWidget * parent = 0);
    virtual ~BaseDraw();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

private:
    void drawAngle();
    void drawRect();
private:
    void slotRotate();

private:
    double m_rTri = 0;
    double m_rQuad = 0;
    QTimer * m_timer;
};

}
