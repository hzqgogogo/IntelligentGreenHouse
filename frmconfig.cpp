#include "frmconfig.h"
#include "ui_frmconfig.h"

frmConfig::frmConfig(QWidget *parent)
    : QWidget(parent), ui(new Ui::frmConfig)
{
    ui->setupUi(this);
}

frmConfig::~frmConfig()
{
    delete ui;
}
