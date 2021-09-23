#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H


#include "OpenGLScene.h"

class OpenGLRenderer : public QObject
{
    Q_OBJECT
public:
    explicit OpenGLRenderer(QObject *parent = nullptr);
    OpenGLRenderer(const OpenGLRenderer& renderer);

    bool hasErrorLog();
    QString errorLog();

    bool reloadShaders();
    void reloadFrameBuffers();

    //uint32_t pickingPass(OpenGLScene* openGLScene, QPoint cursorPos);
    //void render(OpenGLScene* openGLScene);
signals:
private:
    QString m_log;
    QOpenGLShaderProgram *m_basicShader, *m_pickingShader, *m_phongShader;
    QOpenGLShaderProgram *m_JoeShader;
    QOpenGLFramebufferObject *m_pickingPassFBO;

    QOpenGLShaderProgram * loadShaderFromFile(
        QString vertexShaderFilePath,
        QString fragmentShaderFilePath,
        QString geometryShaderFilePath = "");
};

#endif // OPENGLRENDERER_H
