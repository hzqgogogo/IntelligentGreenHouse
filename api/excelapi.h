#ifndef EXCEL_H
#define EXCEL_H

#include <QObject>
#include <QMutex>
#include <QStringList>

class ExcelAPI : public QObject
{
    Q_OBJECT
private:
    explicit ExcelAPI(QObject *parent = 0);
    static ExcelAPI *_instance;
    QStringList html;

public:
    static ExcelAPI *Instance() {
        static QMutex mutex;
        if (!_instance) {
            QMutexLocker locker(&mutex);
            if (!_instance) {
                _instance = new ExcelAPI;
            }
        }
        return _instance;
    }

    void ToExcel(QString fileName, QString sheetName, QString title,
                 QList<QString> columnNames, QList<int> columnWidths, QStringList content);

signals:

public slots:

};

#endif // EXCEL_H
