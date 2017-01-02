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
    static QByteArray data;

    data += stream;

    while (data.contains(PACKET_END)) {
        int bytes = data.indexOf(PACKET_END);

        UBNetPacket packet;
        packet.depacketize(data.left(bytes));

        QByteArray pkt = packet.packetize().append(PACKET_END);

        m_socket->writeDatagram(pkt.data(), pkt.size(), QHostAddress(tr("192.168.1.%1").arg(packet.getDesID())), PXY_PORT);

        data = data.mid(bytes + qstrlen(PACKET_END));
    }

//    m_socket->writeDatagram(stream.data(), stream.size(), QHostAddress::Broadcast, PXY_PORT);
//    m_socket->writeDatagram(stream.data(), stream.size(), QHostAddress(tr("192.168.1.%1").arg(255)), PXY_PORT);
}

void UBProxy::readPendingDatagrams() {
    QByteArray stream;

    while (m_socket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(m_socket->pendingDatagramSize());
        m_socket->readDatagram(datagram.data(), datagram.size());

        stream += datagram;
    }

    m_server->sendData(stream);
}
