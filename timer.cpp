#include "timer.h"

Timer::Timer(QObject *parent) : QTimer(parent)
{
    connect(this, &Timer::timeout, [=]()
    {
        if (onTimeout)
            onTimeout();
    });
}

//Timer::~Timer()
//{

//}
