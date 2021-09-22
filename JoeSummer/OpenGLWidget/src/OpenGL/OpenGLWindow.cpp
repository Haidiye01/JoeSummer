#include "OpenGLWindow.h"

OpenGLWindow::OpenGLWindow()
{
    timer = new QTimer();
    angle = 0.0;
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));   //连接定时器的信号与槽
    timer->start(100);
}

OpenGLWindow::~OpenGLWindow()
{

}

void OpenGLWindow::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0,0.0,0.0,0.0);
    glClearDepth(1.0);
}

void OpenGLWindow::resizeGL(int w, int h)
{
    Q_UNUSED(w);
    Q_UNUSED(h);
}

void OpenGLWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glRotated(angle,0.0,1.0,0.0);
    glBegin(GL_TRIANGLES);
        glColor3f(1.0,0.0,0.0);
        glVertex3f(0.0,0.8,0.0);
        glColor3f(0.0,0.0,1.0);
        glVertex3f(0.5,0.0,0.0);
        glColor3f(0.0,1.0,0.0);
        glVertex3f(-0.5,0.0,0.0);
    glEnd();
    angle+=10.0;
}
