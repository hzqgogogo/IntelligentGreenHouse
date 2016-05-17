#include "frmlogin.h"
#include "ui_frmlogin.h"
#include "api/myhelper.h"
#include "frmmain.h"
#include "api/appinit.h"
#include <QMovie>

frmLogin::frmLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmLogin)
{
    ui->setupUi(this);
    this->InitStyle();
    this->InitForm();
}

frmLogin::~frmLogin()
{
    delete ui;
}

void frmLogin::InitStyle()
{
    this->setProperty("Form", true);
    this->setProperty("CanMove", true);
    ui->labTitle->setText(App::AppTitle);
    ui->lab_Title->setText(App::AppTitle);
    this->setWindowTitle(ui->lab_Title->text());
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
    IconHelper::Instance()->SetIcoMain(ui->lab_Ico);
    IconHelper::Instance()->SetIcoClose(ui->btnMenu_Close);
    connect(ui->btnMenu_Close, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->btnClose,SIGNAL(clicked()),this,SLOT(close()));
    QMovie *movie = new QMovie(QString(":/image/12.gif"));
    ui->labTitle->setMovie(movie);
    movie->start();
}

void frmLogin::InitForm()
{
    //加载用户信息链表到内存,当用户选择用户名和输入密码时,从内存中比较密码,速度极快.
    //将对应用户的密码和类型存入链表,在用户登录时对比,比从数据库中查询速度要快.
    this->GetUserPwd(UserName, UserPwd);
    ui->cboxUserName->addItems(UserName);
    errorCount = 0;
}

void frmLogin::GetUserPwd(QStringList &userName, QStringList &userPwd)
{
    QSqlQuery query(AppInit::DbConn);
    QString sql = "select UserName,UserPwd from UserInfo";
    query.exec(sql);
    while (query.next()) {
        userName << query.value(0).toString();
        userPwd << query.value(1).toString();
    }
}

void frmLogin::on_btnLogin_clicked()
{
    QString userPwd = ui->txtUserPwd->text();
    if (userPwd == "") {
        myHelper::ShowMessageBoxError("密码不能为空,请重新输入!");
        ui->txtUserPwd->setFocus();
        return;
    }

    int index = ui->cboxUserName->currentIndex();

    if (userPwd == UserPwd[index]) {
        App::CurrentUserName = UserName[index];
        App::CurrentUserPwd = UserPwd[index];
        this->hide();
        frmMain *frm = new frmMain;        
        frm->show();
    } else {
        errorCount++;
        if (errorCount >= 3) {
            myHelper::ShowMessageBoxError("密码输入错误次数超过三次,系统将自动退出!");
            exit(0);
        } else {
            myHelper::ShowMessageBoxError("密码错误,请重新输入!");
            ui->txtUserPwd->setFocus();
        }
    }
}

void frmLogin::on_cboxUserName_activated(int index)
{
    ui->txtUserPwd->setFocus();
}


