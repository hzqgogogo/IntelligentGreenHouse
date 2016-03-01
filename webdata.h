#ifndef WEBDATA_H
#define WEBDATA_H

#include "qtsoap.h"

class WebData : public QObject
{
    Q_OBJECT

public:
    WebData(QObject *parent = 0);
    ~WebData();

public slots:
    void submitRequest();
    void getResponse();

private:
    QtSoapHttpTransport http;
};

#endif
