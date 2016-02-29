#ifndef SENSORDATA
#define SENSORDATA

#include <QWidget>
#include "qcustomplot.h"

namespace Ui {
class frmSensorData;
}

class frmSensorData : public QWidget
{
    Q_OBJECT
public:
    frmSensorData(QWidget *parent = NULL);
    ~frmSensorData();

private slots:
    void on_ckMove_stateChanged(int state);
    void on_ckBackground_stateChanged(int state);
    void on_ckLegend_stateChanged(int state);
    void on_ckXGrid_stateChanged(int state);
    void on_ckYGrid_stateChanged(int state);
    void on_ckTemperatureData_stateChanged(int state);
    void on_ckHumidityData_stateChanged(int state);
    void on_ckLightData_stateChanged(int state);

private:
    Ui::frmSensorData *ui;
    QList<QCustomPlot *> plots;

    void InitPlot();
    void InitPlot1();
    void InitPlot2();
    void InitPlot3();
};

#endif
