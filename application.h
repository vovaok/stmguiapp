#ifndef APPLICATION_H
#define APPLICATION_H

#include "core/coretypes.h"
#include "gpio.h" // fake gpio
#include <QWidget>
#include "displaywidget.h"

class Application : public QObject
{
    Q_OBJECT

public:
    static Application *instance();

    void registerTaskEvent(NotifyEvent e);
    void registerTickEvent(Closure<void(int)> e);

    void addWidget(QWidget *w); // should be called from widgets when creating them
    DisplayWidget *displayWidget() {return m_display;}

signals:
    void systemResetRequest();

protected:
    Application();

    void systemReset() {emit systemResetRequest();}

private:
    static Application *m_instance;

    QVector<QWidget *> m_widgets;
    DisplayWidget *m_display;
};

Application *stmApp();

#endif // APPLICATION_H
