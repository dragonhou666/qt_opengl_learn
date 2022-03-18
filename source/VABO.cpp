#include <iostream>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions_4_5_Core>
#include <QtMath>
#include "VABO.h"

//VAO(vertex Array Object)：顶点数组对象
//VBO(vertex Array Object)：顶点缓冲对象

namespace mapgl {
//glsl区分大小写
//顶点着色器
const char* vertexShaderSource = \
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}";

//片段着色器
const char* fragmentShaderSource = \
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f,0.5f,0.2f, 1.0f);\n"
        "}";

#define EBO 1;

VABO::VABO(QWidget *parent)
    : MapImpl(parent)
    , m_timer(new QTimer())
{
    m_timer->setInterval(10);
    connect(m_timer, &QTimer::timeout, this, &VABO::slotRotate);
    m_timer->start();
}

void VABO::initializeGL()
{
    MapImpl::initializeGL();

    //顶点着色器的另一种形式
//    QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex,this);
//    vshader->compileSourceCode(vertexShaderSource);
//    m_program->addShader(vshader);

    // line
    //新建着色器程序处理工具
    m_program = new QOpenGLShaderProgram(this);
    //加载顶点着色器程序
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    //加载片段着色器程序
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    //链接着色器程序
    m_program->link();
    //着色器程序位置属性
    m_posLoc = m_program->attributeLocation("aPos");
    m_colorLoc = m_program->uniformLocation("FragColor");
    m_matrixLoc = m_program->uniformLocation("matrix");
    m_program->bind();
}

void VABO::paintGL()
{
    drawAngle();
}

void VABO::resizeGL(int width, int height)
{
    MapImpl::resizeGL(width,height);
}

void VABO::drawAngle()
{
    //为着色器设置顶点属性
    //输入顶点数据
    float pointCache[] = {
        -0.5,0,0,
        0.5,0,0,
        0,0.8666,0,
    };
    glVertexAttribPointer(m_posLoc, 3, GL_FLOAT, GL_FALSE, 0, pointCache);
    //启用顶点着色器属性
    glEnableVertexAttribArray(m_posLoc);
    //绘制三角形
    glLineWidth(3);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    //关闭顶点着色器属性
    glDisableVertexAttribArray(m_posLoc);
}

void VABO::init_opengl()
{
    //初始化部分
    //创建vao,vbo；vbo用来缓存顶点数据，尽可能多的将顶点数据发送到gpu,gpu缓存数据的对象
    GLuint VAO, VBO;
    //glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    //将顶点数据链接到缓冲对象上
    //glBindVertexArray(VAO);
    //将缓存对象链接到相应的缓存上
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //输入顶点数据
    float pointCache[] = {
        -0.5,0,0,
        0.5,0,0,
        0,0.8666,0,
    };

    //将顶点数据copy到缓存对象
    //glBUfferData(GL_ARRAY_BUFFER,sizeof(pointCache), pointCache, GL_STATIC_DRAW);

    //告诉opengl如何解析顶点数据
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 3*sizeof(float), (void*)0);
    //启用顶点属性
    glEnableVertexAttribArray(0);

    //解绑缓存着色器
    glBindBuffer(GL_ARRAY_BUFFER,0);
    //解绑顶点着色器
    //glBindVertexArray(0);

    //创建顶点着色器并编译
    int sucess;
    char infoLog[512];
    int vertextShader = glCreateShader(GL_VERTEX_SHADER);
    //着色器源码附着到着色器对象上
    glShaderSource(vertextShader, 1, &vertexShaderSource, nullptr);
    //编译
    glCompileShader(vertextShader);
    //检测是否编译成功
    glGetShaderiv(vertextShader, GL_COMPILE_STATUS, &sucess);
    if (!sucess)
    {
        glGetShaderInfoLog(vertextShader, 512, nullptr, infoLog);
        std::cout<<"vertex shader:"<<infoLog;
    }

    //创建片段着色器并编译
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &sucess);
    if (!sucess)
    {
        glGetShaderInfoLog(vertextShader, 512, nullptr, infoLog);
        std::cout<<"fragment shader:"<<infoLog;
    }

    //创建着色器程序
    m_shader_program = glCreateProgram();
    glAttachShader(m_shader_program,vertextShader);
    glAttachShader(m_shader_program, fragmentShader);
    //链接
    glLinkProgram(m_shader_program);
    //判断是否链接成功
    glGetProgramiv(m_shader_program, GL_LINK_STATUS, &sucess);

    if (!sucess)
    {
        glGetShaderInfoLog(vertextShader, 512, nullptr, infoLog);
        std::cout<<"program shader:"<<infoLog;
    }

    //删除已经使用的着色器
    glDeleteShader(vertextShader);
    glDeleteShader(fragmentShader);
}

void VABO::drawAngle_opengl()
{
    //使用着色器程序
    glUseProgram(m_shader_program);
    //激活vao表示的顶点缓存
    //glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void VABO::drawRect()
{

}

//设置填充颜色
void VABO::setColor(const QColor &color)
{
    m_program->setUniformValue(m_colorLoc, color);
}

void VABO::slotRotate()
{
    update();
}




}
