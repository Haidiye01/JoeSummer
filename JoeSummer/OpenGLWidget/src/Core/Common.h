#ifndef COMMON_H
#define COMMON_H
#include <QDebug>
#include <QWidget>
#include <QTranslator>
#include <QMessageBox>
#include <QApplication>
#include <QCoreApplication>
#include <QMap>
#include <memory>
#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_3_3_Core>
#include <QSurfaceFormat>
#include <QTimer>
#include <QTime>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QOpenGLShaderProgram>
#include <QOpenGLFramebufferObject>
#include <QFile>
#include <QFileInfo>
#include <QObject>
#include <iostream>
//#include <QPluginLoader>
//#include <QRect>
//#include <QGraphicsDropShadowEffect>
#include <QMainWindow>//主工程用
#include <QHBoxLayout>//主工程用
#include <QSplitter>//主工程用
#define FILENAME (QFileInfo(__FILE__).fileName().toStdString().c_str())
#define FUNCNAME __FUNCTION__
#define LINENO __LINE__

#define dout ((qDebug().nospace() << FUNCNAME << "(" << FILENAME << ":" << LINENO << "):").space())
#define tab(n) (QByteArray((n) * 4, ' ').data())

#define NO_LOG 0
#define LOG_LEVEL_ERROR 1
#define LOG_LEVEL_WARNING 2
#define LOG_LEVEL_INFO 3

extern int log_level;
#endif // COMMON_H
