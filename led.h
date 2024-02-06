#ifndef LED_H
#define LED_H

#include "gpio.h" // fake gpio
#include <QLabel>
#include <QVariant>

class Led : public QLabel
{
    Q_OBJECT
public:
    Led(Gpio::PinName pinName, bool inverted=false);
    Led(GPIO_TypeDef *gpio, int pin, bool inverted=false);

    void on();
    void off();
    void toggle();

    // emulator things
    void setColor(QColor color);

private:
    bool m_state = false;
    QColor m_color;

    void updateState();
};

#endif // LED_H
