#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_openGLWindow=new OpenGLWindow(new OpenGLScene,new OpenGLRenderer);
    //m_openGLWindow->setRenderer(new OpenGLRenderer);
    configLayout();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::configLayout() {
    m_splitter = new QSplitter(this);
    //m_splitter->addWidget(m_sceneTreeWidget);
    m_splitter->addWidget(QWidget::createWindowContainer(m_openGLWindow));
    //m_splitter->addWidget(m_propertyWidget);
   // m_splitter->setSizes(QList<int>{160, width() - 160 - 300, 300});

    QHBoxLayout * mainLayout = new QHBoxLayout;
    mainLayout->addWidget(m_splitter);
    centralWidget()->setLayout(mainLayout);
}
