#ifndef SENSORDATA
#define SENSORDATA

#include <QWidget>
#include "qcustomplot.h"

namespace Ui {
class frmSensorData;
}

class WebData;
class frmSensorData : public QWidget
{
    Q_OBJECT
public:
    frmSensorData(QWidget *parent = NULL);
    ~frmSensorData();
    void getSensorData(QString sensorMac, QString sensorTemperature, QString sensorHumidity, QString sensorLight, QString sensorSwitch);

private slots:
    void on_ckMove_stateChanged(int state);
    void on_ckBackground_stateChanged(int state);
    void on_ckLegend_stateChanged(int state);
    void on_ckXGrid_stateChanged(int state);
    void on_ckYGrid_stateChanged(int state);
    void on_ckTemperatureData_stateChanged(int state);
    void on_ckHumidityData_stateChanged(int state);
    void on_ckLightData_stateChanged(int state);
    void on_btnSwitch_clicked();

private:
    Ui::frmSensorData *ui;
    QList<QCustomPlot *> plots;
    bool isOff;
    int index;
    WebData *webData;
    QString methodSensorData;
    QMap<QString, QString> argSensorData;
    int ledState;
    int ledStateNum;

    void InitPlot();
    void InitPlot1();
    void InitPlot2();
    void InitPlot3();
    void dataInput1(float sensorTemperature);
    void dataInput2(float sensorHumidity);
    void dataInput3(float sensorLight);
    void setSwitchState(int flag);
};

#endif
