#include "app.h"
#include "myhelper.h"
#include "webdata.h"

QString App::AppTitle = "IPV6物联网管理系统";
QString App::AppName = "Intelligence";
QString App::AppPath = "";
int App::AppFontSize = 10;
QString App::AppFontName = "Microsoft YaHei";

int App::IcoMain = 0xf015;
int App::IcoMenu = 0xf0d7;
int App::IcoMin = 0xf068;
int App::IcoMax = 0xf079;
int App::IcoNormal = 0xf0b2;
int App::IcoClose = 0xf00d;

int App::DeskWidth = 1440;
int App::DeskHeight = 900;

QString App::CurrentUserName = "admin";
QString App::CurrentUserPwd = "admin";

QString App::AppStyle = ":/qss/dev.css";


void App::ReadConfig()
{
    QString fileName = App::AppPath + "/Config.ini";
    //如果配置文件不存在,则以初始值继续运行,并生成配置文件
    if (!myHelper::FileIsExist(fileName)) {
#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
        App::AppTitle = App::AppTitle.toLatin1();
#endif
        WriteConfig();
        return;
    }

    QSettings *set = new QSettings(fileName, QSettings::IniFormat);
    set->beginGroup("AppConfig");

    App::AppTitle = set->value("AppTitle").toString();
    WebData::host = set->value("Host").toString();
    WebData::port = set->value("Port").toString();

    set->endGroup();
}

void App::WriteConfig()
{
    QString fileName = App::AppPath + "/config.ini";
    QSettings *set = new QSettings(fileName, QSettings::IniFormat);
    set->beginGroup("AppConfig");

    set->setValue("AppTitle", App::AppTitle);
    set->setValue("Host", WebData::host);
    set->setValue("Port", WebData::port);

    set->endGroup();
}
