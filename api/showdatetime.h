#ifndef SHOWDATETIME_H
#define SHOWDATETIME_H

#include <QObject>

class QLabel;
class QTimer;

class ShowDateTime : public QObject
{
    Q_OBJECT
public:
    explicit ShowDateTime(QObject *parent = 0);
    ~ShowDateTime();

    void SetLab(QLabel *labDateTime, QLabel *labLive);
    void Start();
    void Stop();

private slots:
    void showDateTime();

private:
    int day;                //天数
    int hour;               //时钟数
    int minute;             //分钟数
    int seconds;            //秒钟数
    QTimer *timer;
    QLabel *labDateTime;
    QLabel *labLive;

    void setInfo();

signals:

public slots:
};

#endif // SHOWDATETIME_H
