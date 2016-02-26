#ifndef FRMCONFIG_H
#define FRMCONFIG_H

#include <QWidget>

namespace Ui {
class frmConfig;
}

class frmConfig : public QWidget
{
    Q_OBJECT

public:
    frmConfig(QWidget *parent = NULL);
    ~frmConfig();

private slots:
    void on_btnConfig_clicked();

private:
    Ui::frmConfig *ui;

    void InitForm();
};

#endif
