#include "frmconfig.h"
#include "ui_frmconfig.h"

frmConfig::frmConfig(QWidget *parent)
    : QWidget(parent), ui(new Ui::frmConfig)
{
    ui->setupUi(this);
    InitForm();
}

frmConfig::~frmConfig()
{
    delete ui;
}

void frmConfig::InitForm()
{
    ui->btnConfig->click();
}

void frmConfig::on_btnConfig_clicked()
{
    ui->btnConfig->setChecked(true);
}
