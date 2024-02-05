#include "tcpsocket.h"

TcpSocket::TcpSocket() :
    QTcpSocket()
{
    connect(this, &QTcpSocket::connected, [=](){if (onConnect) onConnect();});
    connect(this, &QTcpSocket::disconnected, [=](){if (onDisconnect) onDisconnect();});
    connect(this, &QTcpSocket::readyRead, [=](){if (onReadyRead) onReadyRead();});
}
