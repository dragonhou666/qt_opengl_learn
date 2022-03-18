#include "base_draw.h"

namespace mapgl {


BaseDraw::BaseDraw(QWidget *parent)
    : MapImpl(parent)
    , m_timer(new QTimer(this))
{
    m_timer->setInterval(10);
    connect(m_timer, &QTimer::timeout, this, &BaseDraw::slotRotate);
    m_timer->start();
}

BaseDraw::~BaseDraw()
{

}

void BaseDraw::initializeGL()
{
    MapImpl::initializeGL();
}

void BaseDraw::paintGL()
{
    //清除屏幕和深度缓存
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawAngle();
    drawRect();
}

void BaseDraw::resizeGL(int width, int height)
{
    MapImpl::resizeGL(width,height);
}

void BaseDraw::drawAngle()
{
    //重置观察矩阵/投影坐标
    //x轴：从左到右，y轴：从下到上，z轴：从里到外
    glLoadIdentity();

    //移动坐标
    glTranslatef(-1.5, 0.0, -6.0);
    //绕y轴旋转
    glRotatef(m_rTri, 0, 1, 0);

    //绘制三角形
    glBegin(GL_TRIANGLES);
    glColor3f(1,0,0);
    glVertex3f(0,1,0);
    glColor3f(0,1,0);
    glVertex3f(-1,-1,0);
    glColor3f(0,0,1);
    glVertex3f(1,-1,0);
    glEnd();
    glLoadIdentity();
}

void BaseDraw::drawRect()
{
    //重置观察矩阵/投影坐标
    //x轴：从左到右，y轴：从下到上，z轴：从里到外
    glLoadIdentity();

    //移动坐标
    glTranslatef(1.5, 0.0, -6.0);
    //绕x轴旋转
    glRotatef(m_rQuad, 1, 0, 0);

    //绘制三角形
    glBegin(GL_QUADS);
    glColor3f(0.5,0.5,1);
    glVertex3f(-1,1,0);
    glVertex3f(-1,-1,0);
    glVertex3f(1,-1,0);
    glVertex3f(1,1,0);
    glEnd();
    glLoadIdentity();
}

void BaseDraw::slotRotate()
{
    m_rTri += 2;
    m_rQuad += 1;
    update();
}

}
