#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QTcpSocket>
#include "core/coretypes.h"

typedef qintptr SocketDescriptor_t;

class TcpSocket : public QTcpSocket
{
public:
    NotifyEvent onConnect;
    NotifyEvent onDisconnect;
    NotifyEvent onReadyRead;
};

#endif // TCPSOCKET_H
