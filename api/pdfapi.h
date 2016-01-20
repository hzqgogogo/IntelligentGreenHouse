#ifndef PDFAPI_H
#define PDFAPI_H

#include <QObject>
#include <QMutex>
#include <QStringList>

class PdfAPI : public QObject
{
    Q_OBJECT
private:
    explicit PdfAPI(QObject *parent = 0);
    static PdfAPI *_instance;
    QStringList html;

public:
    static PdfAPI *Instance() {
        static QMutex mutex;
        if (!_instance) {
            QMutexLocker locker(&mutex);
            if (!_instance) {
                _instance = new PdfAPI;
            }
        }
        return _instance;
    }

    void SavePDF(QString file, QString title, QString type,
                 QList<QString> columnNames, QList<int> columnWidths, QStringList content);

};

#endif // PDFAPI_H
