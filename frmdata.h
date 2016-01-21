#ifndef FRMDATA_H
#define FRMDATA_H

#include <QWidget>

namespace Ui {
class frmData;
}

class frmData : public QWidget
{
    Q_OBJECT

public:
    explicit frmData(QWidget *parent = NULL);
    ~frmData();

private slots:
    void button_clicked();

private:
    Ui::frmData *ui;

    void InitForm();
};

#endif
