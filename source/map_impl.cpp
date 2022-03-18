#include "map_impl.h"
#include "GL/glu.h"

namespace mapgl {
//参考资料: https://learnopengl-cn.github.io/intro

MapImpl::MapImpl(QWidget *parent)
    : QOpenGLWidget(parent)
{

}

MapImpl::~MapImpl()
{

}

void MapImpl::initializeGL()
{
    initializeOpenGLFunctions();
    //阴影平滑
    glShadeModel(GL_SMOOTH);
    //清除屏幕所用的颜色
    glClearColor(0.5,0.1,0.4,1.0);
    //设置深度缓存
    glClearDepth(1.0);
    //启用深度测试
    glEnable(GL_DEPTH_TEST);
    //设置深度测试类型
    glDepthFunc(GL_LEQUAL);
    //希望得到最好的透视修正
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
}

void MapImpl::paintGL()
{

}

void MapImpl::resizeGL(int width, int height)
{
    //重置当前视口
    glViewport(0,0,(GLint)width, (GLint)height);
    //选择投影矩阵
    glMatrixMode(GL_PROJECTION);
    //重置矩阵坐标
    glLoadIdentity();
    //建立透视投影矩阵
    gluPerspective(45,(GLfloat)width/(GLfloat)height, 0.1, 100);
    //选择模型观察矩阵
    glMatrixMode(GL_MODELVIEW);
    //重置矩阵坐标
    glLoadIdentity();
}

}
