#include "rotaryencoder.h"
#include <QDebug>

RotaryEncoder::RotaryEncoder(Gpio::PinName pinA, Gpio::PinName pinB)
{
    setRange(0, 15);
    m_value = value();
    setWrapping(true);
}

void RotaryEncoder::sliderChange(SliderChange change)
{
    if (change == SliderValueChange)
    {
        int delta = value() - m_value;
        m_value = value();
        int N = maximum() + 1;
        if (delta > N / 2)
            delta -= N;
        else if (delta < -N / 2)
            delta += N;

        int step = qBound(-1, delta, 1);
        if (step)
        {
            if (step > 0)
            {
                if (onStepUp)
                    onStepUp();
            }
            else
            {
                if (onStepDown)
                    onStepDown();
            }

            if (onStep)
                onStep(step);
        }
    }
    QDial::sliderChange(change);
}

