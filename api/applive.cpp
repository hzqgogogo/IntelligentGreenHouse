#include "applive.h"
#include "app.h"

AppLive::AppLive(QObject *parent) : QObject(parent)
{
    udpServer  = new QUdpSocket(this);
}

AppLive::~AppLive()
{

}

void AppLive::Start(int port)
{
    udpServer->bind(port);
    connect(udpServer, SIGNAL(readyRead()), this, SLOT(ReadData()));
}

void AppLive::ReadData()
{
    QByteArray tempData;
    do {
        tempData.resize(udpServer->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        udpServer->readDatagram(tempData.data(), tempData.size(), &sender, &senderPort);
        QString data = QLatin1String(tempData);
        if (data == "hello") {
            udpServer->writeDatagram(QString("%1OK").arg(App::AppName).toLatin1(), sender, senderPort);
        }
    } while (udpServer->hasPendingDatagrams());
}
