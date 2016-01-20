#include "showdatetime.h"
#include "myhelper.h"

ShowDateTime::ShowDateTime(QObject *parent) : QObject(parent)
{
    day = 0;
    hour = 0;
    minute = 0;
    seconds = 0;
    timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(showDateTime()));
}

ShowDateTime::~ShowDateTime()
{

}

void ShowDateTime::SetLab(QLabel *labDateTime, QLabel *labLive)
{
    this->labDateTime = labDateTime;
    this->labLive = labLive;
    this->setInfo();
}

void ShowDateTime::Start()
{
    timer->start();
}

void ShowDateTime::Stop()
{
    timer->stop();
}

void ShowDateTime::showDateTime()
{
    seconds++;
    if (seconds == 60) {
        minute++;
        seconds = 0;
    }
    if (minute == 60) {
        hour++;
        minute = 0;
    }
    if (hour == 24) {
        day++;
        hour = 0;
    }
    setInfo();
}

void ShowDateTime::setInfo()
{
    this->labLive->setText(QString("已运行 : %1天%2时%3分%4秒  |  ").arg(day).arg(hour).arg(minute).arg(seconds));
    this->labDateTime->setText(QDateTime::currentDateTime().toString("当前时间 : yyyy年MM月dd日 HH:mm:ss  "));    
}
