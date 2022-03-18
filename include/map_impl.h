#pragma once

#include <memory>
#include <QTimer>
#include <vector>
#include <map>
#include <QPainter>
#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>


namespace mapgl {

class MapImpl : public QOpenGLWidget, public QOpenGLFunctions
{
    Q_OBJECT

public:
    MapImpl(QWidget * parent = 0);
    virtual ~MapImpl();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

};

}
