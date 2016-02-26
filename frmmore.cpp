#include "frmmore.h"
#include "ui_frmmore.h"

frmMore::frmMore(QWidget *parent)
    : QWidget(parent), ui(new Ui::frmMore)
{
    ui->setupUi(this);
    InitForm();
}

frmMore::~frmMore()
{
    delete ui;
}

void frmMore::InitForm()
{
    ui->btnMore->click();
}

void frmMore::on_btnMore_clicked()
{
    ui->btnMore->setChecked(true);
}
