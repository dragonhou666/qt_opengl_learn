#include <iostream>

#include "EBO.h"

//VAO(vertex Array Object)：顶点数组对象
//VBO(vertex Array Object)：顶点缓冲对象

namespace mapgl {
//glsl区分大小写
//顶点着色器GET_CLSTR()
const char* vertexShaderSource1 = \
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}";

//片段着色器
const char* fragmentShaderSource1 = \
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f,0.5f,0.2f, 1.0f);\n"
        "}";

EBO::EBO(QWidget *parent)
    : MapImpl(parent)
    , m_timer(new QTimer())
{
    m_timer->setInterval(10);
    connect(m_timer, &QTimer::timeout, this, &EBO::slotRotate);
    m_timer->start();
}

EBO::~EBO()
{
    makeCurrent();
    m_vao.destroy();
    m_vbo->destroy();
    m_ebo->destroy();
}

void EBO::initializeGL()
{
    makeCurrent();
    MapImpl::initializeGL();

    // line
    //新建着色器程序处理工具
    m_program = new QOpenGLShaderProgram(this);
    //加载顶点着色器程序
    if(!m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource1))
    {
        qDebug()<<"vertex:"<<m_program->log();
    }
    //加载片段着色器程序
   if (!m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource1))
   {
       qDebug()<<"fragment:"<<m_program->log();
   }
    //链接着色器程序
    if (!m_program->link())
    {
        qDebug()<<"link"<<m_program->log();
    }
    //着色器程序位置属性
    m_posLoc = m_program->attributeLocation("aPos");
    m_colorLoc = m_program->uniformLocation("FragColor");
    m_matrixLoc = m_program->uniformLocation("matrix");
    m_program->bind();
    setupVertices();

}

void EBO::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    drawAngle();
}

void EBO::resizeGL(int width, int height)
{
    MapImpl::resizeGL(width,height);
}

void EBO::drawAngle()
{
    m_program->bind();
    m_vao.bind();
    //绘制三角形
    glLineWidth(3);
    //glDrawArrays(GL_TRIANGLES,0,3);
    glDrawElements(GL_TRIANGLES,18, GL_UNSIGNED_INT,0);
    m_vao.release();
    m_program->release();
}

void EBO::makeObject()
{
    int attr = -1;
    attr = m_program->attributeLocation("posAttr");
    m_program->setAttributeBuffer(attr,GL_FLOAT, 0, 3,
                                  sizeof(float)*6);
    m_program->enableAttributeArray(attr);

    attr = m_program->attributeLocation("colAttr");
    m_program->setAttributeBuffer(attr,GL_FLOAT, 3*sizeof (float), 3,
                                  sizeof(float)*6);

    m_vbo->release();
}

//设置填充颜色
void EBO::setColor(const QColor &color)
{
    m_program->setUniformValue(m_colorLoc, color);
}

void EBO::slotRotate()
{
    update();
}

void EBO::setupVertices()
{
    GLfloat arrVertex[] = {
        -0.8,-0.5,0,
        -0.8,0.5,0,
        0,1,0,
        0.8,0.5,0,
        0.8,-0.5,0,
        0,-1,0,
    };

    GLuint indices[] = {
        0,1,2,
        1,2,3,
        2,3,4,
        3,4,5,
        4,5,0,
        5,0,1,
    };
//    GLfloat arrVertex[] = {
//        0.5,0.5,0,
//        0.5,-0.5,0,
//        -0.5,-0.5,0,
//        -0.6,0,0,
//        -0.5,0.5,0
//    };

//    GLuint indices[] = {
//        0,1,2,
//        1,2,3,
//        2,3,4,
//    };

    m_vao.create();
    m_vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_vbo->create();
    m_ebo = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    m_ebo->create();

    m_vao.bind();
    m_vbo->bind();
    m_vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vbo->allocate(arrVertex,sizeof (arrVertex));


    m_ebo->bind();
    m_ebo->setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_ebo->allocate(indices, sizeof (indices));

    //步长
    m_program->setAttributeBuffer(m_posLoc, GL_FLOAT, 0, 3, 0);
    //启用顶点着色器属性
    glEnableVertexAttribArray(m_posLoc);
    m_vbo->release();
    m_vao.release();
}

}
