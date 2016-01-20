#include "frminputbox.h"
#include "ui_frminputbox.h"
#include "api/myhelper.h"

frmInputBox::frmInputBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmInputBox)
{
    ui->setupUi(this);
    this->InitStyle();
    myHelper::FormInCenter(this);
}

frmInputBox::~frmInputBox()
{
    delete ui;
}

void frmInputBox::InitStyle()
{
    this->setWindowTitle(ui->lab_Title->text());
    this->setProperty("Form", true);
    this->setProperty("CanMove", true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
    IconHelper::Instance()->SetIcoMain(ui->lab_Ico, App::AppFontSize + 2);
    IconHelper::Instance()->SetIcoClose(ui->btnMenu_Close);
    connect(ui->btnMenu_Close, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(close()));
}

void frmInputBox::SetMessage(QString title)
{
    ui->labInfo->setText(title);
}

void frmInputBox::SetPassword(bool pwd)
{
    if (pwd) {
        ui->txtValue->setEchoMode(QLineEdit::Password);
    }
}

void frmInputBox::on_btnOk_clicked()
{
    value = ui->txtValue->text();
    done(1);
    this->close();
}
