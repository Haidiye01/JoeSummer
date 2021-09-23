#include "OpenGLWindow.h"

int log_level =  LOG_LEVEL_INFO;//修改  从main函数移动中这里
#define TestJoe 1
GLuint VBO, VAO;
const char *vertexShaderSource =
        "#version 330 core\n"
        "layout(location = 0) in vec3 aPos;\n"
        "void main(){\n"
        "  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\n\0";
const char *fragmentShaderSource =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main(){\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";

OpenGLWindow::OpenGLWindow()
{
    m_lastCursorPos = QCursor::pos();
      m_enableMousePicking = true;
      m_renderer = 0;
      //m_openGLScene = 0;
      //m_fpsCounter = new FPSCounter(this);
     // m_customRenderingLoop = 0;
      configSignals();
}
//OpenGLWindow::OpenGLWindow(OpenGLScene * openGLScene, OpenGLRenderer * renderer) {
//    m_lastCursorPos = QCursor::pos();
//    m_enableMousePicking = true;
//    m_renderer = renderer;
//    m_openGLScene = openGLScene;
//    m_fpsCounter = new FPSCounter(this);
//    m_customRenderingLoop = 0;
//    configSignals();
//}
OpenGLWindow::~OpenGLWindow()
{

}
#pragma region "获取信息" {
QString OpenGLWindow::rendererName() {
    return isInitialized() ? QString((char*) glGetString(GL_RENDERER)) : "";
}

QString OpenGLWindow::openGLVersion() {
    return isInitialized() ? QString((char*) glGetString(GL_VERSION)) : "";
}

QString OpenGLWindow::shadingLanguageVersion() {
    return isInitialized() ? QString((char*) glGetString(GL_SHADING_LANGUAGE_VERSION)) : "";
}
#pragma endregion}
void OpenGLWindow::initializeGL()
{
#if TestJoe==1
    //着色器部分
    core = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();//获取上下文
    int vertexShader = core->glCreateShader(GL_VERTEX_SHADER);
    core->glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    core->glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    core->glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        core->glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        qDebug() << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
    }
    // fragment shader
    int fragmentShader = core->glCreateShader(GL_FRAGMENT_SHADER);

    core->glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    core->glCompileShader(fragmentShader);
    // check for shader compile errors
    core->glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        core->glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        qDebug() << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
    }
    shaderProgram = core->glCreateProgram();
    core->glAttachShader(shaderProgram, vertexShader);
    core->glAttachShader(shaderProgram, fragmentShader);
    core->glLinkProgram(shaderProgram);
    // check for linking errors
    core->glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        core->glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        qDebug() << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
    }
    core->glDeleteShader(vertexShader);
    core->glDeleteShader(fragmentShader);

    //VAO，VBO数据部分
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, // left
        0.5f, -0.5f, 0.0f, // right
        0.0f,  0.5f, 0.0f  // top
    };


    core->glGenVertexArrays(1, &VAO);//两个参数，第一个为需要创建的缓存数量。第二个为用于存储单一ID或多个ID的GLuint变量或数组的地址
    core->glGenBuffers(1, &VBO);
    core->glBindVertexArray(VAO);
    core->glBindBuffer(GL_ARRAY_BUFFER, VBO);

    core->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    core->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    core->glEnableVertexAttribArray(0);

    core->glBindBuffer(GL_ARRAY_BUFFER, 0);
    core->glBindVertexArray(0);
#else

#endif
}

void OpenGLWindow::resizeGL(int w, int h)
{
    //core->glViewport(0, 0, w, h);
}

void OpenGLWindow::paintGL()
{
    //glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#if TestJoe==1
    core->glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
    core->glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

    core->glUseProgram(shaderProgram);
    core->glBindVertexArray(VAO);
    core->glDrawArrays(GL_TRIANGLES, 0, 3);
    core->glUseProgram(0);
#else
#endif
}
#pragma region "高级" {
//void OpenGLWindow::setScene(OpenGLScene* openGLScene) {
//    if (m_openGLScene)
//        disconnect(m_openGLScene, 0, this, 0);
//    m_openGLScene = openGLScene;
//    if (m_openGLScene)
//        connect(m_openGLScene, SIGNAL(destroyed(QObject*)), this, SLOT(sceneDestroyed(QObject*)));
//}

//void OpenGLWindow::setRenderer(OpenGLRenderer * renderer) {
//    m_renderer = renderer;
//    if (isInitialized() && m_renderer) {
//        m_renderer->reloadShaders();
//        if (m_renderer->hasErrorLog()) {
//            QString log = m_renderer->errorLog();
//            QMessageBox::critical(0, "Failed to load shaders", log);
//            if (log_level >= LOG_LEVEL_ERROR)
//                dout << log;
//        }
//    }
//}

void OpenGLWindow::setEnableMousePicking(bool enabled) {
    m_enableMousePicking = enabled;
}

//void OpenGLWindow::setCustomRenderingLoop(void (*customRenderingLoop)(Scene*)) {
//    m_customRenderingLoop = customRenderingLoop;
//}

//void OpenGLWindow::initializeGL() {
//    initializeOpenGLFunctions();
//    glEnable(GL_DEPTH_TEST);

//    if (m_renderer) {
//        m_renderer->reloadShaders();
//        if (m_renderer->hasErrorLog()) {
//            QString log = m_renderer->errorLog();
//            QMessageBox::critical(0, "Failed to load shaders", log);
//            if (log_level >= LOG_LEVEL_ERROR)
//                dout << log;
//        }
//    } else {
//        QMessageBox::critical(0, "Failed to initialize OpenGL", "No renderer specified.");
//        if (log_level >= LOG_LEVEL_ERROR)
//            dout << "No renderer specified";
//    }
//}

//void OpenGLWindow::paintGL() {
//    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//    processUserInput();

//    if (m_renderer && m_openGLScene && m_openGLScene->host()->camera()) {
//        if (m_customRenderingLoop)
//            m_customRenderingLoop(m_openGLScene->host());

//        m_openGLScene->host()->camera()->setAspectRatio(float(width()) / height());
//        m_openGLScene->commitCameraInfo();
//        m_openGLScene->commitLightInfo();
//        //非鼠标左键单击
//        if (!m_keyPressed[Qt::LeftButton] && m_enableMousePicking) {
//            uint32_t pickingID = m_renderer->pickingPass(m_openGLScene, mapFromGlobal(QCursor::pos()) * devicePixelRatioF());
//            OpenGLMesh* pickedOpenGLMesh = m_openGLScene->pick(pickingID);
//            if (pickedOpenGLMesh)
//                pickedOpenGLMesh->host()->setHighlighted(true);
//            else if (Mesh::getHighlighted())
//                Mesh::getHighlighted()->setHighlighted(false);
//        }

//        m_renderer->render(m_openGLScene);
//    }
//}

bool OpenGLWindow::event(QEvent * event) {
    if (QOpenGLWindow::event(event)) return true;
//    if (!m_openGLScene) return false;

//    if (event->type() == QEvent::DragEnter) {
//        QDragEnterEvent* dragEnterEvent = static_cast<QDragEnterEvent*>(event);
//        if (dragEnterEvent->mimeData()->hasUrls())
//            dragEnterEvent->acceptProposedAction();
//        event->accept();
//        return true;
//    } else if (event->type() == QEvent::DragMove) {
//        QDragMoveEvent* dragMoveEvent = static_cast<QDragMoveEvent*>(event);
//        if (dragMoveEvent->mimeData()->hasUrls())
//            dragMoveEvent->acceptProposedAction();
//        event->accept();
//        return true;
//    } else if (event->type() == QEvent::Drop) {
//        QDropEvent* dropEvent = static_cast<QDropEvent*>(event);
//        foreach(const QUrl &url, dropEvent->mimeData()->urls()) {
//            ModelLoader loader;
//            Model* model = loader.loadModelFromFile(url.toLocalFile());

//            if (loader.hasErrorLog()) {
//                QString log = loader.errorLog();
//                QMessageBox::critical(0, "Error", log);
//                if (log_level >= LOG_LEVEL_ERROR)
//                    dout << log;
//            }

//            if (model) m_openGLScene->host()->addModel(model);
//        }
//        event->accept();
//        return true;
//    }
    return false;
}

void OpenGLWindow::keyPressEvent(QKeyEvent * event) {
    m_keyPressed[event->key()] = true;
    event->accept();
}

void OpenGLWindow::keyReleaseEvent(QKeyEvent * event) {
    m_keyPressed[event->key()] = false;
    event->accept();
}

void OpenGLWindow::mousePressEvent(QMouseEvent * event) {
//    if (!m_openGLScene || (event->button() != Qt::LeftButton&& event->button() != Qt::RightButton))
//    {//joe add event->button() != Qt::RightButton
//        return;
//    }
    m_lastCursorPos = mapFromGlobal(QCursor::pos());
    m_lastMousePressTime = QTime::currentTime();
    m_keyPressed[event->button()] = true;
    event->accept();

//    if (Mesh::getHighlighted() && Mesh::getHighlighted()->isGizmo())
//        m_openGLScene->host()->transformGizmo()->setTransformAxis(Mesh::getHighlighted());
}

void OpenGLWindow::mouseReleaseEvent(QMouseEvent * event) {
//    if (!m_openGLScene || (event->button() != Qt::LeftButton&& event->button() != Qt::RightButton))
//    {//joe add event->button() != Qt::RightButton
//        return;
//    }
//    m_keyPressed[event->button()] = false;
//    m_openGLScene->host()->transformGizmo()->setTransformAxis(TransformGizmo::None);
//    event->accept();

//    if (m_lastMousePressTime.msecsTo(QTime::currentTime()) < 200) { // click
//        if (Mesh::getHighlighted()) {
//            if (!Mesh::getHighlighted()->isGizmo()) {
//                Mesh::getHighlighted()->setSelected(true);
//                m_openGLScene->host()->transformGizmo()->bindTo(Mesh::getSelected());
//            }
//        } else if (Mesh::getSelected()) {
//            Mesh::getSelected()->setSelected(false);
//            m_openGLScene->host()->transformGizmo()->unbind();
//        }
//    }
}
//滚轮事件
void OpenGLWindow::wheelEvent(QWheelEvent * event) {
//    if (!m_openGLScene) return;

//    if (!event->pixelDelta().isNull())
//        m_openGLScene->host()->camera()->moveForward(event->pixelDelta().y());
//    else if (!event->angleDelta().isNull())
//        m_openGLScene->host()->camera()->moveForward(event->angleDelta().y());

//    event->accept();
}

void OpenGLWindow::focusOutEvent(QFocusEvent *) {
    for (int i = 0; i < m_keyPressed.keys().size(); i++)
        m_keyPressed[m_keyPressed.keys()[i]] = false;
}

void OpenGLWindow::processUserInput() {
//    if (!m_openGLScene || !m_openGLScene->host()->camera())
//    {
//        return;
//    }
//    float shift = 1.0f;
//    if (m_keyPressed[Qt::Key_Shift]) shift *= 5.0f;
//    if (m_keyPressed[Qt::Key_W]) m_openGLScene->host()->camera()->moveForward(shift);
//    if (m_keyPressed[Qt::Key_S]) m_openGLScene->host()->camera()->moveForward(-shift);
//    if (m_keyPressed[Qt::Key_A]) m_openGLScene->host()->camera()->moveRight(-shift);
//    if (m_keyPressed[Qt::Key_D]) m_openGLScene->host()->camera()->moveRight(shift);
//    if (m_keyPressed[Qt::Key_Q]) m_openGLScene->host()->camera()->moveUp(-shift);
//    if (m_keyPressed[Qt::Key_E]) m_openGLScene->host()->camera()->moveUp(shift);
//    //鼠标左键
//    if (m_keyPressed[Qt::LeftButton]) {
//        QPoint cntCursorPos = mapFromGlobal(QCursor::pos());
//        TransformGizmo* gizmo = m_openGLScene->host()->transformGizmo();
//        if (gizmo->visible() && gizmo->transformAxis() != TransformGizmo::None) {
//            gizmo->drag(m_lastCursorPos, cntCursorPos,
//                        width(), height(),
//                        m_openGLScene->host()->camera()->projectionMatrix(),
//                        m_openGLScene->host()->camera()->viewMatrix());
//        } else {
//            m_openGLScene->host()->camera()->turnLeft((m_lastCursorPos.x() - cntCursorPos.x()) / 10.0f);
//            m_openGLScene->host()->camera()->lookUp((m_lastCursorPos.y() - cntCursorPos.y()) / 10.0f);
//        }
//        m_lastCursorPos = cntCursorPos;
//    }
//    //鼠标右键 joe add
//    if (m_keyPressed[Qt::RightButton]) {
//        float shiftLR=0;
//        float shiftUD=0;
//        float constCeo=5.0f;
//        QPoint cntCursorPos = mapFromGlobal(QCursor::pos());
//        shiftLR=(m_lastCursorPos.x() - cntCursorPos.x())/constCeo;
//        shiftUD=(m_lastCursorPos.y() - cntCursorPos.y())/constCeo;
//        m_openGLScene->host()->camera()->moveRight(shiftLR);
//        m_openGLScene->host()->camera()->moveUp(-shiftUD);
//        m_lastCursorPos = cntCursorPos;
//    }
}

void OpenGLWindow::configSignals() {
//    connect(m_fpsCounter, SIGNAL(fpsChanged(int)), this, SIGNAL(fpsChanged(int)));
//    connect(this, SIGNAL(frameSwapped()), m_fpsCounter, SLOT(inc()));
//    connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
//    if (m_openGLScene)
//        connect(m_openGLScene, SIGNAL(destroyed(QObject*)), this, SLOT(sceneDestroyed(QObject*)));
}

//void OpenGLWindow::sceneDestroyed(QObject *) {
//    m_openGLScene = 0;
//}
#pragma endregion}
