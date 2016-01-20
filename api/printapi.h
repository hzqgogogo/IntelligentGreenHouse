#ifndef PRINTAPI_H
#define PRINTAPI_H

#include <QObject>
#include <QMutex>
#include <QStringList>

class QPrinter;

class PrintAPI : public QObject
{
    Q_OBJECT
private:
    explicit PrintAPI(QObject *parent = 0);
    static PrintAPI *_instance;
    QStringList html;

public:
    static PrintAPI *Instance() {
        static QMutex mutex;
        if (!_instance) {
            QMutexLocker locker(&mutex);
            if (!_instance) {
                _instance = new PrintAPI;
            }
        }
        return _instance;
    }

    void PrintA4(QString title, QString type, QList<QString> columnNames,
                 QList<int> columnWidths, QStringList content);

signals:

private slots:
    void printView(QPrinter *printer);

};

#endif // PRINTAPI_H
