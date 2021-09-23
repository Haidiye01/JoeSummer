#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include <QTimer>


class OpenGLWindow : public QOpenGLWindow, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    OpenGLWindow();
    ~OpenGLWindow();

protected:
    void initializeGL();          //鍒濆鍖栬缃
    void resizeGL(int w, int h);  //绐楀彛灏哄鍙樺寲鍝嶅簲鍑芥暟
    void paintGL();               //閲嶇粯鍝嶅簲鍑芥暟
private:
    GLfloat angle;                //瀹氫箟鏃嬭浆瑙掑害
    QTimer *timer;                //瀹氫箟鏂扮殑瀹氭椂鍣};
};
#endif // OPENGLWINDOW_H
