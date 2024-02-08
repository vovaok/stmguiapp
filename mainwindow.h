#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include "app.h"
#if defined(EMULATOR_WIDGET)
#include "emulatorwidget.h"
#endif

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void start();
    void reset();

private:
    Ui::MainWindow *ui;
    App *app;
    DisplayWidget *display;
    QVBoxLayout *mainLayout;
#if defined(EMULATOR_WIDGET)
    EmulatorWidget *emu;
#endif
};

#endif // MAINWINDOW_H
