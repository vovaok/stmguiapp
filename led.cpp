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
