#include "app.h"
#include "myhelper.h"

QString App::AppTitle = "智能大棚";
QString App::AppName = "Intelligence";
QString App::AppPath = "";
int App::AppFontSize = 10;
QString App::AppFontName = "Microsoft YaHei";

int App::IcoMain = 0xf099;
int App::IcoMenu = 0xf0d7;
int App::IcoMin = 0xf068;
int App::IcoMax = 0xf079;
int App::IcoNormal = 0xf0b2;
int App::IcoClose = 0xf00d;

int App::DeskWidth = 1440;
int App::DeskHeight = 900;

QString App::CurrentUserName = "admin";
QString App::CurrentUserPwd = "admin";

QString App::AppStyle = ":/qss/blue.css";
QString App::AppCom="COM1";

void App::ReadConfig()
{
    QString fileName = App::AppPath + "/Config.ini";
    //如果配置文件不存在,则以初始值继续运行,并生成配置文件
    if (!myHelper::FileIsExist(fileName)) {
        App::AppTitle = App::AppTitle.toLatin1();
        WriteConfig();
        return;
    }

    QSettings *set = new QSettings(fileName, QSettings::IniFormat);
    set->beginGroup("AppConfig");

    App::AppTitle = set->value("AppTitle").toString();
    App::AppStyle = set->value("AppStyle").toString();
    App::AppCom= set->value("AppCom").toString();

    set->endGroup();
}

void App::WriteConfig()
{
    QString fileName = App::AppPath + "/MCS_Config.ini";
    QSettings *set = new QSettings(fileName, QSettings::IniFormat);
    set->beginGroup("AppConfig");

    set->setValue("AppTitle", App::AppTitle);
    set->setValue("AppStyle", App::AppStyle);
    set->setValue("AppCom", App::AppCom);

    set->endGroup();
}
