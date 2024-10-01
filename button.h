#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>
//#include "sbutton.h"
#include <QTimer>
#include "core/coretypes.h"
#include "gpio.h" // fake gpio

class Button : public QPushButton
{
    Q_OBJECT

public:
    Button();
    Button(Gpio::PinName, bool pullUp=true, bool inverted=true);
    Button(GPIO_TypeDef *, int , bool inverted=true);

    void setAutoRepeat(int timeMs = 200) {m_repeatTime = timeMs;}
    bool isHolding() const {return m_holding;}

    bool state() const {return m_state;}
    int holdTime() const {return m_holdTime;}

    NotifyEvent onPress;
    NotifyEvent onRelease;
    NotifyEvent onClick;

private:
    QTimer m_repeatTimer;
    int m_repeatTime = 200;
    bool m_state = false;
    bool m_holding = false;
    int m_holdTime = 0;

    void onPushButtonPress();
    void onPushButtonRelease();
    void onTimer();
};

#endif // BUTTON_H
