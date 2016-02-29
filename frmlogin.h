#ifndef FRMLOGIN_H
#define FRMLOGIN_H

#include <QDialog>

namespace Ui
{
    class frmLogin;
}

class frmLogin : public QDialog
{
    Q_OBJECT

public:
    explicit frmLogin(QWidget *parent = 0);
    ~frmLogin();

private slots:
    void on_btnLogin_clicked();
    void on_cboxUserName_activated(int index);

private:
    Ui::frmLogin *ui;

    int errorCount;     //密码错误次数    
    void InitStyle();   //初始化无边框窗体
    void InitForm();    //初始化窗体数据

    QStringList UserName, UserPwd;
    void GetUserPwd(QStringList &userName, QStringList &userPwd);

};

#endif // FRMLOGIN_H
