#ifndef PRECISETIMER_H
#define PRECISETIMER_H

#include <QElapsedTimer>

class PreciseTimer : public QElapsedTimer
{
public:
    float delta()
    {
        float dt = nsecsElapsed() * 1e-9;
        restart();
        return dt;
    }
};

#endif // PRECISETIMER_H
