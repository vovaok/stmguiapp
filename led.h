#ifndef LED_H
#define LED_H

#include "gpio.h" // fake gpio
#include "timer.h"
#include <QLabel>
#include <QVariant>

class Led : public QLabel
{
    Q_OBJECT
public:
    Led(Gpio::PinName pinName, bool inverted=false);
    Led(GPIO_TypeDef *gpio, int pin, bool inverted=false);
    virtual ~Led();

    void on();
    void off();
    void toggle();

    void setBlinkInterval(int value);
    bool isBlinking() const;
    void setBlinkingEnabled(bool enabled);
    void blink();
    void blinkOnce();

    // emulator things
    void setColor(QColor color);

private:
    bool m_state = false;
    QColor m_color;
    Timer *m_blinkTimer = nullptr;

    void updateState();
    Timer *timer();
};

#endif // LED_H
