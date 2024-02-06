#ifndef ROTARYENCODER_H
#define ROTARYENCODER_H

#include <QDial>
#include "gpio.h"
#include "core/coretypes.h"

class RotaryEncoder : public QDial
{
    Q_OBJECT
public:
    RotaryEncoder(Gpio::PinName pinA, Gpio::PinName pinB);

    Closure<void(int)> onStep;
    NotifyEvent onStepUp;
    NotifyEvent onStepDown;

protected:
    virtual void sliderChange(QAbstractSlider::SliderChange change) override;

private:
    int m_value;
};

#endif // ROTARYENCODER_H
