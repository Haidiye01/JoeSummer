QT       += core gui network opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
DESTDIR = ../bin
INCLUDEPATH += \
    ../OpenGLWidget/src/Core \
    ../OpenGLWidget/src/OpenGL \
    ../OpenGLWidget/src/UI \
    ../OpenGLWidget/3rdparty
win32 {
    LIBS += -lopengl32
    LIBS += ../bin/OpenGLWidget.dll#dll引用 -L../bin -lOpenGLWidget#新增
    #LIBS += -L../bin -lassimp-vc140-mt#这句话可以
    LIBS += -L../bin -llibassimp#-lassimp-vc140-mt
    RC_ICONS = ../OpenGLWidget/resources/icons/AppIcon.ico
}
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
