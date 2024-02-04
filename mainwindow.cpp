#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <QLabel>
#include <QGraphicsDropShadowEffect>
#include <QDebug>

QString css = R"(
QPushButton
{
    width: 30px;
    height: 30px;
    max-width: 30px;
    max-height: 30px;
    background-color: white;
    border: 3px solid gray;
    border-radius: 15px;
    font-size: 25px;
}

QPushButton::pressed
{
    background-color: #CCC;
}
)";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(320, 500);
    setWindowTitle("STM32++ GUI emulator");
    statusBar()->setSizeGripEnabled(false);

    app = new App();

    setStyleSheet(css);

//    display = new DisplayWidget(320, 480);

    DisplayWidget *display = app->displayWidget();
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

//    QWidget *buttons = new QWidget;
//    buttons->setFixedWidth(app->display()->width());
//    QGridLayout *btnlay = new QGridLayout;
//    btnlay->setContentsMargins(0, 0, 0, 0);
//    buttons->setLayout(btnlay);
//    for (int i=0; i<5; i++)
//        btnlay->addWidget(app->btnMenu[i], 0, i);
//    btnlay->addWidget(new QLabel, 1, 0);
//    btnlay->addWidget(app->btnUp, 2, 2);
//    btnlay->addWidget(app->btnLeft, 3, 1);
//    btnlay->addWidget(app->btnFire, 3, 2);
//    btnlay->addWidget(app->btnRight, 3, 3);
//    btnlay->addWidget(app->btnDown, 4, 2);

//    app->btnUp->setText("↑");
//    app->btnLeft->setText("←");
//    app->btnRight->setText("→");
//    app->btnDown->setText("↓");

    QVBoxLayout *lay = new QVBoxLayout;
    ui->centralwidget->setLayout(lay);
    lay->addWidget(display);
//    lay->addWidget(buttons);
}

MainWindow::~MainWindow()
{
    delete ui;
}


