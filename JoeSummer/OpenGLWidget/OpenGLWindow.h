#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include "Common.h"

class OpenGLWindow :  public QOpenGLWindow, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT

public:
    OpenGLWindow();

signals:

};

#endif // OPENGLWINDOW_H
