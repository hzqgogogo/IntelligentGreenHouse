#include "webdata.h"
#include <QDebug>

#define SENSORDATAREPONSE "sensorDataReponse"
#define SENSORSTATE "sensorData"
#define SENSORMAC "sensorMac"
#define SENSORTEMPERATURE "sensorTemperature"
#define SENSORHUMIDITY "sensorHumidity"
#define SENSORLIGHT "sensorLight"
#define SENSORSWITCH "sensorSwitch"

#define SENSORSWITCHREPONSE "sensorSwitchReponse"
#define RESULT "result"

#define SOAPACTION "http://WebXml.com.cn/qqCheckOnline"
#define HOST "www.webxml.com.cn"
#define NAMESPACE "http://WebXml.com.cn/"
#define POST "/webservices/qqOnlineWebService.asmx"

WebData::WebData(QObject *parent)
{
    connect(&http, SIGNAL(responseReady()), this, SLOT(getResponse()));

    http.setAction(SOAPACTION);
    http.setHost(HOST);
}

WebData::~WebData()
{

}

void WebData::submitRequest(QString method, QMap<QString, QString> arg)
{
    QtSoapMessage request;

    request.setMethod("qqCheckOnline", NAMESPACE);
    request.addMethodArgument("qqCode", "", "");

    http.submitRequest(request, POST);
//    QList<QString> key;
//    key = arg.keys();
//    QtSoapMessage request;
//    request.setMethod(method, NAMESPACE);
//    for(int i = 0; i < arg.count(); i++)
//    {
//        request.addMethodArgument(key.at(i), "", arg.value(key.at(i)));
//    }
//    http.submitRequest(request, POST);
}

void WebData::getResponse()
{
    const QtSoapMessage &resp = http.getResponse();
    if (resp.isFault()) {
        qDebug() << resp.faultString().value().toString();
        return;
    }

    const QtSoapType &res = resp.returnValue();
    if (!res.isValid()) {
        qDebug() << "Invalid return value";
        return;
    }

    // 通过QDomDocument是可以解析获取到的数据的
    QString xml = resp.toXmlString();
    qDebug() << xml;
    QDomDocument doc;
    doc.setContent(xml);
    //    QDomNodeList nodeList =doc.elementsByTagName("qqCheckOnlineResult");

    //    if(nodeList.size())
    //    {
    //        QDomNode resultNode =nodeList.at(0);
    //        qDebug() << resultNode.toElement().text();
    //    }
    QDomNodeList nodeList = doc.elementsByTagName("qqCheckOnlineResponse");
    QDomNode n = nodeList.at(0);
    while(!n.isNull())
    {
        if(n.isElement())
        {
            QDomElement e = n.toElement();
            QDomNodeList list = e.childNodes();
            for(int i = 0; i < list.count(); i++)
            {
                QDomNode node = list.at(i);
                if(node.isElement())
                {
//                    qDebug() << "hzq:" << node.toElement().tagName() << "::" << node.toElement().text();
                    QString tagName = node.toElement().tagName();
                    QString text = node.toElement().text();
                    if(tagName == SENSORSTATE)
                    {
                        if(text == "wait")
                        {
                            break;
                        }
                        else if(text == "close")
                        {
                            QString sensorMac;
                            sensorMac = list.at(i+1).toElement().text();
                            emit sigSensorClose(sensorMac);
                            break;
                        }
                    }
                    else if(tagName == SENSORMAC)
                    {
                        sensorData.sensorMac = text;
                    }
                    else if(tagName == SENSORTEMPERATURE)
                    {
                        sensorData.sensorTemperature = text;
                    }
                    else if(tagName == SENSORHUMIDITY)
                    {
                        sensorData.sensorHumidity = text;
                    }
                    else if(tagName == SENSORLIGHT)
                    {
                        sensorData.sensorLight = text;
                    }
                    else if(tagName == SENSORSWITCH)
                    {
                        sensorData.sensorSwitch = text;
                        emit sigSensorData(sensorData);
                    }
                }
            }
        }
        n = n.nextSibling();
    }
}
