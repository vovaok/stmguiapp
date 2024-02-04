#ifndef TIMER_H
#define TIMER_H

#include <QTimer>
#include "core/coretypes.h"

class Timer : public QTimer
{
    Q_OBJECT
public:
    Timer(QObject *parent = nullptr);
//    virtual ~Timer();

    NotifyEvent onTimeout;
    //    void (*callback)(void) = nullptr;

    NotifyEvent timeoutEvent() {return onTimeout;}
    void setTimeoutEvent(NotifyEvent event) {onTimeout = event;}

private:

};

#endif // TIMER_H
