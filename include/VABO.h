#pragma once

#include <QTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include "map_impl.h"


namespace mapgl {

class VABO : public MapImpl
{
    Q_OBJECT

public:
    VABO(QWidget * parent = 0);
    virtual ~VABO() = default;

    void setColor(const QColor& color);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

private:
    void drawAngle();
    void init_opengl();
    void drawAngle_opengl();
    void drawRect();
    void makeObject();
private:
    void slotRotate();

private:
    double m_rTri = 0;
    double m_rQuad = 0;
    QTimer * m_timer;
    GLint m_posLoc = 0; // 位置id
    GLint m_colorLoc = 0; // 颜色id
    GLint m_matrixLoc = 0; // 变换矩阵id
    QOpenGLShaderProgram * m_program = nullptr;
private:
    int m_shader_program;
};

}
