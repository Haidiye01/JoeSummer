#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <OpenGLWindow.h>
#include <OpenGLScene.h>
#include <Common.h>
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
    QSplitter * m_splitter;
    QLabel* m_fpsLabel;

    OpenGLWindow* m_openGLWindow;
};
#endif // MAINWINDOW_H
