#ifndef FRMMORE_H
#define FRMMORE_H

#include <QWidget>

namespace Ui {
class frmMore;
}

class frmMore : public QWidget
{
    Q_OBJECT

public:
    frmMore(QWidget *parent = NULL);
    ~frmMore();

private slots:
    void on_btnMore_clicked();

private:
    Ui::frmMore *ui;

    void InitForm();
};

#endif
