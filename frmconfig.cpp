#include "frmconfig.h"
#include "ui_frmconfig.h"
#include "api/app.h"
#include "api/myhelper.h"
#include "api/appinit.h"
#include "webdata.h"

frmConfig::frmConfig(QWidget *parent)
    : QWidget(parent), ui(new Ui::frmConfig)
{
    ui->setupUi(this);
    InitForm();

    ui->host->setText(WebData::host);
    ui->port->setText(WebData::port);
}

frmConfig::~frmConfig()
{
    delete ui;
}

void frmConfig::InitForm()
{
    ui->btnConfig->click();

    for (int i = 2015; i <= 2025; i++) {
        ui->cboxYear->addItem(QString::number(i));
    }
    for (int i = 1; i <= 12; i++) {
        ui->cboxMonth->addItem(QString::number(i));
    }
    for (int i = 1; i <= 31; i++) {
        ui->cboxDay->addItem(QString::number(i));
    }
    for (int i = 0; i < 24; i++) {
        ui->cboxHour->addItem(QString::number(i));
    }
    for (int i = 0; i < 60; i++) {
        ui->cboxMin->addItem(QString::number(i));
        ui->cboxSec->addItem(QString::number(i));
    }

    QString now = QDateTime::currentDateTime().toString("yyyy-M-d-H-m-s");
    QStringList str = now.split("-");
    ui->cboxYear->setCurrentIndex(ui->cboxYear->findText(str.at(0)));
    ui->cboxMonth->setCurrentIndex(ui->cboxMonth->findText(str.at(1)));
    ui->cboxDay->setCurrentIndex(ui->cboxDay->findText(str.at(2)));
    ui->cboxHour->setCurrentIndex(ui->cboxHour->findText(str.at(3)));
    ui->cboxMin->setCurrentIndex(ui->cboxMin->findText(str.at(4)));
    ui->cboxSec->setCurrentIndex(ui->cboxSec->findText(str.at(5)));
}

void frmConfig::on_btnConfig_clicked()
{
    ui->btnConfig->setChecked(true);
}

void frmConfig::on_btnUpdata_clicked()
{
    QString PwdOld = ui->leOldPasswd->text();
    QString PwdNew = ui->leNewPasswd->text();
    QString PwdNewX = ui->lePasswdAgain->text();

    if (PwdOld != App::CurrentUserPwd) {
        myHelper::ShowMessageBoxError("原密码错误,请重新输入!");
        ui->leOldPasswd->setFocus();
        return;
    }

    if (PwdNew == "") {
        myHelper::ShowMessageBoxError("新密码不能为空,请重新输入!");
        ui->leNewPasswd->setFocus();
        return;
    }

    if (PwdNewX == "") {
        myHelper::ShowMessageBoxError("确认密码不能为空,请重新输入!");
        ui->lePasswdAgain->setFocus();
        return;
    }

    if (PwdNew != PwdNewX) {
        myHelper::ShowMessageBoxError("新密码和确认密码不一致,请重新输入!");
        ui->leNewPasswd->setFocus();
        return;
    }

    QSqlQuery query(AppInit::DbConn);
    QString sql = QString("update UserInfo set UserPwd='%1' where UserName='%2'")
            .arg(PwdNewX).arg(App::CurrentUserName);
    query.exec(sql);

    //重置当前用户新密码,用于退出判断
    App::CurrentUserPwd = PwdNewX;
    QString TempMsg = "密码修改成功";
    myHelper::ShowMessageBoxInfo(QString("%1,请牢记新密码【%2】!").arg(TempMsg).arg(PwdNewX));
}

void frmConfig::on_btnSetTime_clicked()
{
    QString year = QString("%1").arg(ui->cboxYear->currentText());
    QString month = QString("%1").arg(ui->cboxMonth->currentText().toInt(), 2, 10, QChar('0'));
    QString day = QString("%1").arg(ui->cboxDay->currentText().toInt(), 2, 10, QChar('0'));
    QString hour = QString("%1").arg(ui->cboxHour->currentText().toInt(), 2, 10, QChar('0'));
    QString min = QString("%1").arg(ui->cboxMin->currentText().toInt(), 2, 10, QChar('0'));
    QString sec = QString("%1").arg(ui->cboxSec->currentText().toInt(), 2, 10, QChar('0'));
    myHelper::SetSystemDateTime(year, month, day, hour, min, sec);
}

void frmConfig::on_btnEnter_clicked()
{
    WebData::port = ui->port->text();
    WebData::host = ui->host->text();
    WebData::soapAction = "http://" + WebData::host +
            ":" + WebData::port + "/FFBUS_WS/service/FFBUS";

    App::WriteConfig();
}
