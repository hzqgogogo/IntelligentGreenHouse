#include "frmmore.h"
#include "ui_frmmore.h"

frmMore::frmMore(QWidget *parent)
    : QWidget(parent), ui(new Ui::frmMore)
{
    ui->setupUi(this);
}

frmMore::~frmMore()
{
    delete ui;
}
