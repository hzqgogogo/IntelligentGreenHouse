#include "frmmain.h"
#include "ui_frmmain.h"
#include "api/myhelper.h"

frmMain::frmMain(QWidget *parent):
    QDialog(parent),
    ui(new Ui::frmMain)
{
    ui->setupUi(this);
    InitStyle();
}

frmMain::~frmMain()
{
    delete ui;
}

bool frmMain::eventFilter(QObject *obj, QEvent *evt)
{
    if (evt->type() == QEvent::MouseButtonDblClick && obj == ui->widget_title) {
        this->on_btnMenu_Max_clicked();
        return true;
    }
    return QObject::eventFilter(obj, evt);
}

void frmMain::on_btnMenu_Max_clicked()
{

}

void frmMain::InitStyle()
{
    this->max = false;
    this->location = this->geometry();
    this->setProperty("Form", true);
    this->setProperty("CanMove", true);
    this->setWindowTitle(ui->lab_Title->text());
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);

    IconHelper::Instance()->SetIcoMain(ui->lab_Ico, 40);
    IconHelper::Instance()->SetIcoMin(ui->btnMenu_Min);
    IconHelper::Instance()->SetIcoNormal(ui->btnMenu_Max);
    IconHelper::Instance()->SetIcoClose(ui->btnMenu_Close);

    connect(ui->btnMenu_Min, SIGNAL(clicked()), this, SLOT(showMinimized()));
    connect(ui->btnMenu_Close, SIGNAL(clicked()), this, SLOT(close()));

    ui->widget_title->installEventFilter(this);
}

void frmMain::InitForm()
{

}
