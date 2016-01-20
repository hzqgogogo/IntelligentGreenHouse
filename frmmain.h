#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QDialog>

namespace Ui {
    class frmMain;
}

class frmMain : public QDialog
{
    Q_OBJECT

public:
    explicit frmMain(QWidget *parent = NULL);
    ~frmMain();

protected:
    bool eventFilter(QObject *obj, QEvent *evt);

private slots:
    void on_btnMenu_Max_clicked();

private:
    Ui::frmMain *ui;
    bool max;
    QRect location;

    void InitStyle();
    void InitForm();
};

#endif
