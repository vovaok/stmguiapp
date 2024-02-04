#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>

class TcpServer : public QTcpServer
{
public:
    void listen(uint16_t port) {QTcpServer::listen(QHostAddress::Any, port);}

};

#endif // TCPSERVER_H
