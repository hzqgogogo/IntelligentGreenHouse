#ifndef APP_H
#define APP_H

class QString;
class QStringList;

class App
{
public:
    static QString AppTitle;        //应用程序名称
    static QString AppName;         //应用程序英文名称
    static QString AppPath;         //应用程序路径
    static int AppFontSize;         //应用程序字体大小
    static QString AppFontName;     //应用程序字体名称

    static int IcoMain;             //左上角图标
    static int IcoMenu;             //下来菜单图标
    static int IcoMin;              //最小化图标
    static int IcoMax;              //最大化图标
    static int IcoNormal;           //正常图标
    static int IcoClose;            //关闭图标

    static int DeskWidth;           //运行环境桌面宽度
    static int DeskHeight;          //运行环境桌面高度

    static QString CurrentUserName; //当前用户名
    static QString CurrentUserPwd;  //当前用户密码

    static QString AppStyle;        //应用程序样式
    static QString AppCom;          //串口号

    static void ReadConfig();       //读取配置文件,在main函数最开始加载程序载入
    static void WriteConfig();      //写入配置文件,在更改配置文件程序关闭时调用

};

#endif // APP_H
