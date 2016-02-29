#include "frmconfig.h"
#include "ui_frmconfig.h"
#include "api/app.h"
#include "api/myhelper.h"

frmConfig::frmConfig(QWidget *parent)
    : QWidget(parent), ui(new Ui::frmConfig)
{
    ui->setupUi(this);
    InitForm();
}

frmConfig::~frmConfig()
{
    delete ui;
}

void frmConfig::InitForm()
{
    ui->btnConfig->click();
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

    QSqlQuery query;
    QString sql = QString("update UserInfo set UserPwd='%1' where UserName='%2'")
            .arg(PwdNewX).arg(App::CurrentUserName);
    query.exec(sql);

    //重置当前用户新密码,用于退出判断
    App::CurrentUserPwd = PwdNewX;
    QString TempMsg = "密码修改成功";
    myHelper::ShowMessageBoxInfo(QString("%1,请牢记新密码【%2】!").arg(TempMsg).arg(PwdNewX));
}
