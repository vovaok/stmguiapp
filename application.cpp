#include "application.h"
#include <QDebug>

Application *Application::m_instance = nullptr;

Application *stmApp()
{
    return Application::instance();
}

Application *Application::instance()
{
//    if (!m_instance)
//        m_instance = new Application;
    return m_instance;
}

void Application::registerTaskEvent(NotifyEvent e)
{
    qDebug() << "task" << e.p_this;
}

void Application::registerTickEvent(Closure<void (int)> e)
{
    qDebug() << "tick" << e.p_this;
}

void Application::addWidget(QWidget *w)
{
    m_widgets << w;
    DisplayWidget *display = qobject_cast<DisplayWidget *>(w);
    if (display)
        m_display = display;
}

Application::Application()
{
    m_instance = this;
}

