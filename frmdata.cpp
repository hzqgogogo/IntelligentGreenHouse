#include "frmdata.h"
#include "ui_frmdata.h"
#include <QDebug>

frmData::frmData(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::frmData)
{
    ui->setupUi(this);
    InitForm();
}

frmData::~frmData()
{
    delete ui;
}

void frmData::InitForm()
{
    QList<QPushButton *> btns = ui->widget_left->findChildren<QPushButton *>();
    foreach (QPushButton *btn, btns) {
        connect(btn, SIGNAL(clicked()), this, SLOT(button_clicked()));
    }

    ui->btnData->click();
}

void frmData::button_clicked()
{
    QPushButton *btn = (QPushButton *)sender();
    QList<QPushButton *> btns = ui->widget_left->findChildren<QPushButton *>();
    foreach (QPushButton *b, btns) {
        b->setChecked(false);
    }

    btn->setChecked(true);
}
