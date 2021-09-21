#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "../OpenGLWidget/OpenGLWindow.h"
#include <QOpenGLWindow>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void configLayout();
private:
    Ui::MainWindow *ui;
    OpenGLWindow* m_openGLWindow;
    QSplitter * m_splitter;
    QLabel* m_fpsLabel;

};
#endif // MAINWINDOW_H
