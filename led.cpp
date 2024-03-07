#include "led.h"
#include <QStyle>
Led::Led(Gpio::PinName pinName, bool inverted)
{
    setObjectName("Led");
    updateState();
}

Led::Led(GPIO_TypeDef *gpio, int pin, bool inverted)
{
    setObjectName("Led");
    updateState();
}

Led::~Led()
{
    if (m_blinkTimer)
        delete m_blinkTimer;
}

void Led::on()
{
    m_state = true;
    updateState();
}

void Led::off()
{
    m_state = false;
    updateState();
}

void Led::toggle()
{
    m_state = !m_state;
    updateState();
}

void Led::setBlinkInterval(int value)
{
    timer()->setInterval(value);
}

bool Led::isBlinking() const
{
    if (m_blinkTimer)
        return m_blinkTimer->isActive();
    return false;
}

void Led::setBlinkingEnabled(bool enabled)
{
    if (enabled)
        timer()->start();
    else if (m_blinkTimer)
        m_blinkTimer->stop();
}

void Led::blink()
{
    on();
    timer()->setSingleShot(false);
    setBlinkingEnabled(true);
}

void Led::blinkOnce()
{
    on();
    timer()->setSingleShot(true);
    setBlinkingEnabled(true);
}

void Led::setColor(QColor color)
{
    m_color = color;
    updateState();
}

void Led::updateState()
{
    QString state = m_state? "on": "off";
    QObject::setProperty("state", state);
    QColor color = m_state? m_color: m_color.darker(300);
    setStyleSheet("#Led {background-color: " + color.name() + ";}");
    style()->polish(this);
}

Timer *Led::timer()
{
    if (!m_blinkTimer)
    {
        m_blinkTimer = new Timer;
        m_blinkTimer->setInterval(50);
        m_blinkTimer->onTimeout = EVENT(&Led::toggle);
    }
    return m_blinkTimer;
}
