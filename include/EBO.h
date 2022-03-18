#pragma once

#include <QTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include "map_impl.h"


namespace mapgl {

class EBO : public MapImpl
{
    Q_OBJECT

public:
    EBO(QWidget * parent = 0);
    virtual ~EBO();

    void setColor(const QColor& color);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

private:
    void drawAngle();
    void drawRect();
    void makeObject();
private:
    void slotRotate();
    void setupVertices();
private:
    double m_rTri = 0;
    double m_rQuad = 0;
    QTimer * m_timer;
    GLint m_posLoc = 0; // 位置id
    GLint m_colorLoc = 0; // 颜色id
    GLint m_matrixLoc = 0; // 变换矩阵id
    QOpenGLShaderProgram * m_program = nullptr;
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer *m_vbo;
    QOpenGLBuffer *m_ebo;

private:
    int m_shader_program;
};

}
