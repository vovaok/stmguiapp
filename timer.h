#ifndef TIMER_H
#define TIMER_H

#include <QTimer>
#include "core/coretypes.h"
#include <functional>

class Timer : public QTimer
{
    Q_OBJECT
public:
    Timer(QObject *parent = nullptr);
//    virtual ~Timer();

    std::function<void(void)> onTimeout;
    //    void (*callback)(void) = nullptr;

//    std::function<void(void)> timeoutEvent() {return onTimeout;}
//    void setTimeoutEvent(std::function<void(void)> event) {onTimeout = event;}

private:

};

#endif // TIMER_H
