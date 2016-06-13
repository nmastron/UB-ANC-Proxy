#ifndef UBPROXY_H
#define UBPROXY_H

#include <QObject>
#include <QByteArray>

class UBServer;
class QUdpSocket;

class UBProxy : public QObject
{
    Q_OBJECT
public:
    explicit UBProxy(QObject *parent = 0);

signals:

public slots:

protected slots:
    void netDataReadyEvent(QByteArray stream);
    void readPendingDatagrams();

private:
    QByteArray m_data;

    UBServer* m_server;
    QUdpSocket* m_socket;
};

#endif // UBPROXY_H
