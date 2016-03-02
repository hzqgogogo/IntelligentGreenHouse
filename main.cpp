#include <QApplication>
#include "frmmain.h"
#include "api/appinit.h"
#include "frmlogin.h"
#include <QtSql>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

//    QStringList drivers = QSqlDatabase::drivers();
//    foreach(QString driver, drivers)
//        qDebug()<<driver;

//    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
//    db.setHostName("120.24.19.217");
//    db.setPort(3306);
//    db.setDatabaseName("mycloud");
//    db.setUserName("root");
//    db.setPassword("root");

//    if(!db.open())
//        qDebug()<<"failed to connect to mysql";
//    else
//        qDebug()<<"success";

//    QString select_all_sql = "select * from user";
//    //查询所有数据
//    QSqlQuery sql_query;
//    sql_query.prepare(select_all_sql);

//    if(!sql_query.exec())
//    {
//        qDebug()<<sql_query.lastError();
//    }
//    else
//    {
//        while(sql_query.next())
//        {
//            int id = sql_query.value(0).toInt();
//            qDebug()<<QString("Id:%1").arg(id);
//        }
//    }

        AppInit *init = new AppInit;
        init->Load();

        frmLogin frm;
        frm.show();

    return app.exec();
}
