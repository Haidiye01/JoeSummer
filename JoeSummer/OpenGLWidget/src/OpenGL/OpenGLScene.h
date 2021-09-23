#ifndef OPENGLSCENE_H
#define OPENGLSCENE_H

#include <QObject>
#include <OpenGLUniformBufferObject.h>
class OpenGLScene : public QObject
{
    Q_OBJECT
public:
    explicit OpenGLScene(QObject *parent = nullptr);

signals:

};

#endif // OPENGLSCENE_H
