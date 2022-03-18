#include <iostream>

#include "Texture.h"

//uniform: Uniform是一种从CPU中的应用向GPU中的着色器发送数据的方式,声明的是全局变量

namespace mapgl {
//glsl区分大小写
//顶点着色器GET_CLSTR()
const char* vertexShaderSource2 =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec3 aColor;\n"
        "layout (location = 2) in vec2 aTexCoord;\n"
        "out vec3 outColor;\n"
        "out vec2 outTexCoord;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "   outColor = aColor;\n"
        "   outTexCoord = aTexCoord;\n"
        "}";

//片段着色器
const char* fragmentShaderSource2 = \
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec3 outColor;\n"
        "in vec2 outTexCoord;\n"
        "uniform sampler2D ourTexCoord;\n"
        "void main()\n"
        "{\n"
        "   FragColor = texture(ourTexCoord, outTexCoord);\n"
        "}";

Texture::Texture(QWidget *parent)
    : MapImpl(parent)
    , m_timer(new QTimer())
{
    m_timer->setInterval(10);
    connect(m_timer, &QTimer::timeout, this, &Texture::slotRotate);
    m_timer->start();
}

Texture::~Texture()
{
    makeCurrent();
    m_vao.destroy();
    m_vbo->destroy();
    m_ebo->destroy();
}

void Texture::initializeGL()
{
    makeCurrent();
    MapImpl::initializeGL();

    // line
    //新建着色器程序处理工具
    m_program = new QOpenGLShaderProgram(this);
    //加载顶点着色器程序
    if(!m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource2))
    {
        qDebug()<<"vertex:"<<m_program->log();
    }
    //加载片段着色器程序
   if (!m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource2))
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
    m_colorLoc = m_program->uniformLocation("aColor");
    m_texture_id = m_program->attributeLocation("aTexCoord");
    m_matrixLoc = m_program->uniformLocation("matrix");
    m_program->bind();

    setupVertices();

    m_texture = new QOpenGLTexture(QImage("./imag/1.jpeg"),QOpenGLTexture::GenerateMipMaps);
    if (m_texture->isCreated())
    {
        m_texture->setWrapMode(QOpenGLTexture::DirectionS,
        QOpenGLTexture::Repeat);
        m_texture->setWrapMode(QOpenGLTexture::DirectionT,
        QOpenGLTexture::Repeat);

        m_texture->setMinificationFilter(QOpenGLTexture::Linear);
        m_texture->setMagnificationFilter(QOpenGLTexture::Linear);
    }
}

void Texture::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    drawAngle();
}

void Texture::resizeGL(int width, int height)
{
    MapImpl::resizeGL(width,height);
}

void Texture::drawAngle()
{
    m_program->bind();
    //glActiveTexture(GL_TEXTURE0);
    m_vao.bind();
    //绘制三角形
    glLineWidth(3);
    glDrawElements(GL_TRIANGLES,6, GL_UNSIGNED_INT,0);
    m_vao.release();
   // m_texture->release();
    m_program->release();
}

//设置填充颜色
void Texture::setColor(const QColor &color)
{
    m_program->setUniformValue(m_colorLoc, color);
}

void Texture::slotRotate()
{
    update();
}

void Texture::setupVertices()
{
    //顶点坐标             颜色          纹理坐标
    GLfloat arrVertex[] = {       
        -0.5, -0.5, 0,        1, 0, 0,        1,1,
        -0.5, 0.5, 0,         0, 1, 0,        1,0,
        0.5, 0.5, 0,          0, 0, 1,        0,0,
        0.5, -0.5, 0,         0, 0, 1,        0,1,
    };

    GLuint indices[] = {
        0, 1, 3,
        1, 2, 3
    };



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
    m_ebo->allocate(indices,sizeof (indices));

    //步长
    m_program->setAttributeBuffer(m_posLoc, GL_FLOAT, 0, 3,
                                  sizeof(GLfloat)*8);
    //启用顶点着色器属性
    glEnableVertexAttribArray(m_posLoc);

    //颜色
    m_program->setAttributeBuffer(m_colorLoc, GL_FLOAT, sizeof(GLfloat)*3, 3,
                                  sizeof(GLfloat)*8);
    glEnableVertexAttribArray(m_colorLoc);

    //纹理  起始位置，步长，大小
//    m_program->setAttributeBuffer(m_texture_id, GL_FLOAT, sizeof(GLfloat)*6, 2,
//                                  sizeof(GLfloat)*8);
//    glEnableVertexAttribArray(m_texture_id);

    m_vbo->release();
    m_vao.release();
}

}
