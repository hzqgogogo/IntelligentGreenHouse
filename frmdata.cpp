#include "frmdata.h"
#include "ui_frmdata.h"
#include <QDebug>
#include "sensordata.h"
#include "webdata.h"
#include <QTimer>

frmData::frmData(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::frmData)
{
    ui->setupUi(this);

    frmDataInit();
    InitForm();
}

frmData::~frmData()
{
    delete ui;
}

void frmData::frmDataInit()
{
    webData = new WebData(this);
    timer = new QTimer(this);
    timer->start(5000);

    methodSensorData = "sensorDataRequest";
    argSensorData.insert("sensorData", "sensordata");

    connect(webData, SIGNAL(sigSensorData(getSensorData)), this, SLOT(slotSensorData(getSensorData)));
    connect(webData, SIGNAL(sigSensorClose(QString)), this, SLOT(slotSensorClose(QString)));
    connect(timer, SIGNAL(timeout()), this, SLOT(slotTimer()));
}

void frmData::InitForm()
{
    QList<QPushButton *> btns = ui->widget_left->findChildren<QPushButton *>();
    foreach (QPushButton *btn, btns) {
        connect(btn, SIGNAL(clicked()), this, SLOT(button_clicked()));
    }

    ui->btnData->click();
}

void frmData::button_clicked()
{
    QPushButton *btn = (QPushButton *)sender();
    QString name = btn->text();
    QList<QPushButton *> btns = ui->widget_left->findChildren<QPushButton *>();
    foreach (QPushButton *b, btns) {
        b->setChecked(false);
    }

    btn->setChecked(true);

    if(name == "传感器数据")
        ui->stackedWidget->setCurrentIndex(0);
    else if(name == "历史数据查询")
        ui->stackedWidget->setCurrentIndex(1);
    frmSensorData *sensor = new frmSensorData;
    ui->tabWidget->addTab(sensor,"test");
}

void frmData::slotSensorData(getSensorData sensorData)
{
    QList<QString> key = map.keys();
    bool flag = false;
    for(int i = 0; i < key.size(); i++)
    {
        if(key.at(i) == sensorData.sensorMac)
        {
            flag == true;
            break;
        }
    }
    if(flag == false)
    {
        frmSensorData *tmpSensorData = new frmSensorData;
        ui->tabWidget->addTab(tmpSensorData, sensorData.sensorMac);
        map.insert(sensorData.sensorMac, tmpSensorData);
    }

    map.value(sensorData.sensorMac)->getSensorData(sensorData.sensorTemperature, sensorData.sensorHumidity,
                                                   sensorData.sensorLight, sensorData.sensorSwitch);
}

void frmData::slotSensorClose(QString sensorMac)
{
    QList<QString> key = map.keys();

    for(int i = 0; i < key.size(); i++)
    {
        if(key.at(i) == sensorMac)
        {
            delete map.take(sensorMac);
        }
    }
}

void frmData::slotTimer()
{
    webData->submitRequest(methodSensorData, argSensorData);
}
