#ifndef WEBDATA_H
#define WEBDATA_H

#include "qtsoap.h"
#include "getsensordata.h"

class WebData : public QObject
{
    Q_OBJECT

public:
    WebData(QObject *parent = 0);
    ~WebData();

signals:
    void sigSensorData(getSensorData sensorData);
    void sigSensorClose(QString sensorMac);

public slots:
    void submitRequest(QString method, QMap<QString, QString> arg);
    void getResponse();

private:
    QtSoapHttpTransport http;
    getSensorData sensorData;
};

#endif
