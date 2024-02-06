#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <QLabel>
#include <QGraphicsDropShadowEffect>
#include <QDebug>

#if defined(EMULATOR_WIDGET)
#include "emulatorwidget.h"
#endif

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("STM32++ GUI emulator");
    statusBar()->setSizeGripEnabled(false);

    app = new App();

    DisplayWidget *display = app->displayWidget();
    if (display)
    {
        qDebug() << "Display found:" << display << display->width() << "x" << display->height();
        display->setObjectName("Display");
        display->setCursor(Qt::CrossCursor);

        QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect;
        shadow->setBlurRadius(10);
        shadow->setColor(Qt::black);
        shadow->setOffset(0, 0);
        display->setGraphicsEffect(shadow);
    }

    QVBoxLayout *lay = new QVBoxLayout;
    ui->centralwidget->setLayout(lay);
    lay->addWidget(display);

#if defined(EMULATOR_WIDGET)
    EmulatorWidget *emu = new EmulatorWidget(app);
    lay->addWidget(emu);
#endif

}

MainWindow::~MainWindow()
{
    delete ui;
}


