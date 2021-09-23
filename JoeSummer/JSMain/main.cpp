#include "mainwindow.h"
#include <QApplication>
void initApplication() {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

#ifdef WIN32
    QApplication::setFont(QFont("Microsoft YaHei UI", 9));
#endif
    QSurfaceFormat openGLFormat;
    openGLFormat.setVersion(3, 3);
    openGLFormat.setProfile(QSurfaceFormat::CoreProfile);
    openGLFormat.setDepthBufferSize(24);
    openGLFormat.setStencilBufferSize(8);
    QSurfaceFormat::setDefaultFormat(openGLFormat);
    //QSurfaceFormat代表QSurface的一种格式，包括颜色缓冲（、红、绿、蓝、alpha缓冲）、深度缓冲、多重采样数量等;
}
int main(int argc, char *argv[])
{
    initApplication();//全局变量初始化
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
