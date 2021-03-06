#ifndef FRMDATA_H
#define FRMDATA_H

#include <QWidget>
#include <QMap>
#include "getsensordata.h"

namespace Ui {
class frmData;
}


class WebData;
class QTimer;
class frmSensorData;
class frmData : public QWidget
{
    Q_OBJECT

public:
    explicit frmData(QWidget *parent = NULL);
    ~frmData();

private slots:
    void button_clicked();
    void slotSensorData(getSensorData sensorData);
    void slotSensorClose(QString sensorMac);
    void slotTimer();
    void on_btnSelect_clicked();

private:
    Ui::frmData *ui;
    WebData *webData;
    QTimer *timer;
    QMap<QString, frmSensorData *> map;
    QString methodSensorData;
    QMap<QString, QString> argSensorData;
    QList<QString> columnNames_Data;
    QList<int> columnWidths_Data;
    int pageCount;
    QString whereSql;

    void frmDataInit();
    void InitForm();
};

#endif
