
#include <QApplication>
#include <QSurfaceFormat>
#include <QOpenGLContext>

#include "window.h"
#include <cstdint>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    QSurfaceFormat::setDefaultFormat(format);


    Window window;
    window.show();

    return app.exec();
}
