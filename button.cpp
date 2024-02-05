#include "button.h"
#include "application.h"

Button::Button()
{
    connect(this, &QAbstractButton::pressed, this, &Button::onPushButtonPress);
    connect(this, &QAbstractButton::released, this, &Button::onPushButtonRelease);
    connect(&m_repeatTimer, &QTimer::timeout, this, &Button::onTimer);
    setCursor(Qt::PointingHandCursor);
    stmApp()->addWidget(this);
}

Button::Button(Gpio::PinName, bool, bool)
{
    connect(this, &QAbstractButton::pressed, this, &Button::onPushButtonPress);
    connect(this, &QAbstractButton::released, this, &Button::onPushButtonRelease);
    connect(&m_repeatTimer, &QTimer::timeout, this, &Button::onTimer);
    setCursor(Qt::PointingHandCursor);
    stmApp()->addWidget(this);
}

Button::Button(GPIO_TypeDef *, int, bool)
{
    connect(this, &QAbstractButton::pressed, this, &Button::onPushButtonPress);
    connect(this, &QAbstractButton::released, this, &Button::onPushButtonRelease);
    connect(&m_repeatTimer, &QTimer::timeout, this, &Button::onTimer);
    setCursor(Qt::PointingHandCursor);
    stmApp()->addWidget(this);
}

void Button::onPushButtonPress()
{
    m_repeatTimer.start(500); // m_holdingTime
    m_state = true;
    if (onPress)
        onPress();
}

void Button::onPushButtonRelease()
{
    if (!m_holding)
    {
        if (onClick)
            onClick();
    }

    m_repeatTimer.stop();
    m_state = false;
    m_holding = false;

    if (onRelease)
        onRelease();
}

void Button::onTimer()
{
    m_holding = true;
    if (m_repeatTime)
    {
        m_repeatTimer.start(m_repeatTime);
        if (onClick)
            onClick();
    }
}
