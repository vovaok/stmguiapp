#ifndef LED_H
#define LED_H

#include "gpio.h" // fake gpio

class Led
{
public:
    Led(Gpio::PinName pinName, bool inverted=false);
    Led(GPIO_TypeDef *gpio, int pin, bool inverted=false);

    void toggle();
};

#endif // LED_H
