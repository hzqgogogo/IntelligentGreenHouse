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

private:
    Ui::frmSensorData *ui;
    QList<QCustomPlot *> plots;

    void InitPlot();
};

#endif
