#include "frmdata.h"
#include "ui_frmdata.h"
#include <QDebug>
#include "sensordata.h"
#include "webdata.h"
#include "api/myhelper.h"
#include "api/dbapi.h"
#include <QTimer>
#include <QtSql>


#define HOSTNAME "120.24.19.217"
#define PORT 3306
#define DATABASENAME "mycloud"
#define USERNAME "root"
#define PASSWD "root"

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
    timer->start(4000);

    methodSensorData = "sensorDataRequest";
    argSensorData.insert("sensorData", "sensordata");

    connect(webData, SIGNAL(sigSensorData(getSensorData)), this, SLOT(slotSensorData(getSensorData)));
    connect(webData, SIGNAL(sigSensorClose(QString)), this, SLOT(slotSensorClose(QString)));
    connect(timer, SIGNAL(timeout()), this, SLOT(slotTimer()));

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(HOSTNAME);
    db.setPort(PORT);
    db.setDatabaseName(DATABASENAME);
    db.setUserName(USERNAME);
    db.setPassword(PASSWD);
//    if(!db.open())
//        myHelper::ShowMessageBoxError("连接远程数据库失败，查询传感器历史数据功能无法使用");
}

void frmData::InitForm()
{
    QList<QPushButton *> btns = ui->widget_left->findChildren<QPushButton *>();
    foreach (QPushButton *btn, btns) {
        connect(btn, SIGNAL(clicked()), this, SLOT(button_clicked()));
    }

    ui->btnData->click();

    columnNames_Data.append("ID");
    columnWidths_Data.append(100);

    pageCount = 25;
    whereSql = "where 1=1";
    //设置需要显示数据的表格和翻页的按钮
    DBAPI::Instance()->SetControl(ui->tableData, ui->labInfo, ui->btnFirst, ui->btnPre, ui->btnNext, ui->btnLast);

    QDate d = QDate::currentDate();
    ui->dateStart->setDate(d);
    ui->dateEnd->setDate(d);

    ui->tableData->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableData->horizontalHeader()->setStretchLastSection(true);
    ui->tableData->setAlternatingRowColors(true);
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
 //   frmSensorData *sensor = new frmSensorData;
   // ui->tabWidget->addTab(sensor,"test");
}

void frmData::slotSensorData(getSensorData sensorData)
{
    QList<QString> key = map.keys();
    bool flag = false;
    for(int i = 0; i < key.size(); i++)
    {
        if(key.at(i) == sensorData.sensorMac)
        {
            flag = true;
            break;
        }
    }
    if(flag == false)
    {
        frmSensorData *tmpSensorData = new frmSensorData;
        ui->tabWidget->addTab(tmpSensorData, sensorData.sensorMac);
        map.insert(sensorData.sensorMac, tmpSensorData);
    }

    map.value(sensorData.sensorMac)->getSensorData(sensorData.sensorMac, sensorData.sensorTemperature, sensorData.sensorHumidity,
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

void frmData::on_btnSelect_clicked()
{
    DBAPI::Instance()->BindDataSelect("user", "userid", "desc", whereSql, pageCount, columnNames_Data, columnWidths_Data);
}
