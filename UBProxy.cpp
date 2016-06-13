#include "UBProxy.h"
#include "UBServer.h"

#include "config.h"

#include <QUdpSocket>

UBProxy::UBProxy(QObject *parent) : QObject(parent)
{
    m_server = new UBServer(this);
    m_server->startServer(NET_PORT);

    connect(m_server, SIGNAL(dataReady(QByteArray)), this, SLOT(netDataReadyEvent(QByteArray)));

    m_socket = new QUdpSocket(this);
    m_socket->bind(PXY_PORT, QUdpSocket::ShareAddress);

    connect(m_socket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
}

void UBProxy::netDataReadyEvent(QByteArray stream) {
//    m_socket->writeDatagram(stream.data(), stream.size(), QHostAddress::Broadcast, PXY_PORT);
    m_socket->writeDatagram(stream.data(), stream.size(), QHostAddress(tr("192.168.1.%1").arg(255)), PXY_PORT);
}

void UBProxy::readPendingDatagrams() {
    while (m_socket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(m_socket->pendingDatagramSize());
        m_socket->readDatagram(datagram.data(), datagram.size());

        m_server->sendData(datagram);
    }
}
