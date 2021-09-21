TEMPLATE = subdirs

SUBDIRS += \
    JSMain \
    OpenGLWidget

DEFINES += QT_NO_WARNING_OUTPUT#屏蔽警告 核心版本
CONFIG += ordered
QMAKE_CXXFLAGS += /MP
