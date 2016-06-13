#ifndef UBPROXY_H
#define UBPROXY_H

#include <QObject>

class UBProxy : public QObject
{
    Q_OBJECT
public:
    explicit UBProxy(QObject *parent = 0);

signals:

public slots:
};

#endif // UBPROXY_H