#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <QLabel>
#include <QToolBar>
#include <QGraphicsDropShadowEffect>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(500, 500);
    setWindowTitle("STM32++ GUI emulator");
    statusBar()->setSizeGripEnabled(false);

//    QPushButton *resetBtn = new QPushButton();
    QToolBar *toolbar = addToolBar("main");
    toolbar->addAction("Reset", this, &MainWindow::reset);

    mainLayout = new QVBoxLayout;
    ui->centralwidget->setLayout(mainLayout);

    start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::start()
{
    app = new App();
    app->setParent(this);
    display = app->displayWidget();
    if (display)
    {
        qDebug() << "Display found:" << display << display->width() << "x" << display->height();
        display->setObjectName("Display");

        QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect;
        shadow->setBlurRadius(10);
        shadow->setColor(Qt::black);
        shadow->setOffset(0, 0);
        display->setGraphicsEffect(shadow);
    }

    mainLayout->addWidget(display);

#if defined(EMULATOR_WIDGET)
    emu = new EmulatorWidget(app);
    mainLayout->addWidget(emu);
#endif

    connect(app, &Application::systemResetRequest, this, &MainWindow::reset);
}

void MainWindow::reset()
{
#if defined(EMULATOR_WIDGET)
    mainLayout->removeWidget(emu);
#else
    mainLayout->removeWidget(display);
#endif
    app->deleteLater();
    display->deleteLater();
#if defined(EMULATOR_WIDGET)
    emu->deleteLater();
#endif

    start();
}


