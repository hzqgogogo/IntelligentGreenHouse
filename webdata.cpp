#include "webdata.h"
#include <QDebug>

WebData::WebData(QObject *parent)
{
    connect(&http, SIGNAL(responseReady()), this, SLOT(getResponse()));

    http.setAction("http://WebXml.com.cn/qqCheckOnline");
    http.setHost("www.webxml.com.cn");
}

WebData::~WebData()
{

}

void WebData::submitRequest()
{
    QtSoapMessage request;

    request.setMethod("qqCheckOnline", "http://WebXml.com.cn/");
    request.addMethodArgument("qqCode", "", "");

    http.submitRequest(request, "/webservices/qqOnlineWebService.asmx");
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
                    qDebug() << "hzq:" << node.toElement().tagName() << "::" << node.toElement().text();
                }
            }
        }
        n = n.nextSibling();
    }
}
