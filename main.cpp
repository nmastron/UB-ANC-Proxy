#include <QCoreApplication>

#include "UBProxy.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    UBProxy pxy;

    return a.exec();
}
