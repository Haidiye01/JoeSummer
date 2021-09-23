#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include "Common.h"


class OpenGLWindow : public QOpenGLWindow,  protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    OpenGLWindow();
    ~OpenGLWindow();

    QString rendererName();
    QString openGLVersion();
    QString shadingLanguageVersion();
protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
private:
private:
    GLuint shaderProgram;
    QOpenGLFunctions_3_3_Core *core;
};
#endif // OPENGLWINDOW_H
