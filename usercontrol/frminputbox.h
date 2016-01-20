#ifndef FRMINPUTBOX_H
#define FRMINPUTBOX_H

#include <QDialog>

namespace Ui
{
    class frmInputBox;
}

class frmInputBox : public QDialog
{
    Q_OBJECT

public:
    explicit frmInputBox(QWidget *parent = 0);
    ~frmInputBox();

    void SetMessage(QString title);
    void SetPassword(bool pwd);
    QString GetValue()const {
        return value;
    }

private slots:
    void on_btnOk_clicked();

private:
    Ui::frmInputBox *ui;
    QString value;

private:
    void InitStyle();

};

#endif // FRMINPUTBOX_H
