#include "appinit.h"
#include "myhelper.h"

AppInit::AppInit(QObject *parent) : QObject(parent)
{
    mousePressed = false;
    qApp->installEventFilter(this);
}

bool AppInit::eventFilter(QObject *obj, QEvent *evt)
{
    QWidget *w = (QWidget *)obj;
    if (!w->property("CanMove").toBool()) {
        return QObject::eventFilter(obj, evt);
    }

    QMouseEvent *event = static_cast<QMouseEvent *>(evt);
    if (event->type() == QEvent::MouseButtonPress) {
        if (event->button() == Qt::LeftButton) {
            mousePressed = true;
            mousePoint = event->globalPos() - w->pos();
            return true;
        }
    } else if (event->type() == QEvent::MouseButtonRelease) {
        mousePressed = false;
        return true;
    } else if (event->type() == QEvent::MouseMove) {
        if (mousePressed && (event->buttons() && Qt::LeftButton)) {
            w->move(event->globalPos() - mousePoint);
            return true;
        }
    }

    return QObject::eventFilter(obj, evt);
}

void AppInit::Load()
{
    myHelper::SetUTF8Code();
    myHelper::SetChinese();
    myHelper::SetFont();

    App::AppPath = QApplication::applicationDirPath();
    App::ReadConfig();
    myHelper::SetStyle(App::AppStyle);

    //程序启动后打开数据库连接,在任何窗体需要的地方调用数据库
    QString dbPath=App::AppPath + "/myData.db";
    if (!myHelper::FileIsExist(dbPath)){
        myHelper::ShowMessageBoxError("数据库不存在!程序将自动关闭!");
        exit(0);
    }

    QSqlDatabase DbConn;
    DbConn = QSqlDatabase::addDatabase("QSQLITE");
    DbConn.setDatabaseName(dbPath);
    if (!DbConn.open()) {
        myHelper::ShowMessageBoxError("数据库打开失败,请检查数据库是否存在或者连接是否正常!");
        exit(0);
    }
}
