QT +=xml  network opengl widgets

TEMPLATE = lib
DEFINES += OPENGLWIDGET_LIBRARY
DESTDIR = ../bin
CONFIG += c++11 precompile_header
PRECOMPILED_HEADER
win32 {
    LIBS += -lopengl32
    #LIBS += -L../bin -lassimp-vc140-mt#这句话可以
    LIBS += -L../bin -llibassimp#-lassimp-vc140-mt#dll引用 #-L../bin -llibassimp#-lassimp-vc140-mt
}
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    OpenGLWindow.cpp \
    OpenglWidget.cpp

HEADERS += \
    OpenGLWidget_global.h \
    OpenGLWindow.h \
    OpenglWidget.h
RESOURCES += resources.qrc
# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

PRECOMPILED_HEADER += \
    Common.h
