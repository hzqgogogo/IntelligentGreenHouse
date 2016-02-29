#include "frmmain.h"
#include "ui_frmmain.h"
#include "api/myhelper.h"
#include "api/showdatetime.h"
#include "frmdata.h"
#include "frmconfig.h"
#include "frmmore.h"

frmMain::frmMain(QWidget *parent):
    QDialog(parent),
    ui(new Ui::frmMain)
{
    ui->setupUi(this);
    myHelper::FormInCenter(this);
    InitStyle();
    InitForm();
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
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(1000);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();

    if (max) {
        this->setGeometry(location);
        IconHelper::Instance()->SetIcoNormal(ui->btnMenu_Max);
        ui->btnMenu_Max->setToolTip("最大化");
        this->setProperty("CanMove", true);
        this->layout()->setMargin(1);
    } else {
        location = this->geometry();
        this->setGeometry(qApp->desktop()->availableGeometry());
        IconHelper::Instance()->SetIcoMax(ui->btnMenu_Max);
        ui->btnMenu_Max->setToolTip("还原");
        this->setProperty("CanMove", false);
        this->layout()->setMargin(0);
    }
    max = !max;
}

void frmMain::InitStyle()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(1000);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();

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
    connect(ui->btnMenu_Close, SIGNAL(clicked()), this, SLOT(closeWidget()));
    connect(ui->btnExit, SIGNAL(clicked()),this, SLOT(closeWidget()));

    ui->widget_title->installEventFilter(this);
    ui->btnMenu_Max->click();
}

void frmMain::InitForm()
{
    QFont font = QFont(App::AppFontName, App::AppFontSize - 1);
    QList<QLabel *> labs = ui->widget_bottom->findChildren<QLabel *>();
    foreach (QLabel * lab, labs) {
        lab->setFont(font);
    }

    ui->lab_Title->setText(App::AppTitle);
    this->setWindowTitle(ui->lab_Title->text());
    ui->labWelcome->setText(QString("  欢迎使用%1 %2  |  ").arg(App::AppTitle).arg("V1.0"));
    ui->labUser->setText(QString("当前用户 : %1【%2】 |  ").arg("admin").arg("管理员"));
    ShowDateTime *s = new ShowDateTime(this);
    s->SetLab(ui->labDateTime, ui->labLive);
    s->Start();

    QList<QToolButton *> btns = ui->widget_top->findChildren<QToolButton *>();
    foreach (QToolButton *btn, btns) {
        connect(btn, SIGNAL(clicked()), this, SLOT(button_clicked()));
    }

    frmData *data = new frmData;
    ui->stackedWidget->addWidget(data);
    frmMore *more = new frmMore;
    ui->stackedWidget->addWidget(more);
    frmConfig *config = new frmConfig;
    ui->stackedWidget->addWidget(config);

    ui->btnData->click();
}

void frmMain::button_clicked()
{
    QToolButton *btn = (QToolButton *)sender();
    QString text = btn->text();

    QList<QToolButton *> btns = ui->widget_top->findChildren<QToolButton *>();
    foreach(QToolButton *b, btns)
    {
        b->setChecked(false);
    }
    btn->setChecked(true);

    if(text == "数据显示")
        ui->stackedWidget->setCurrentIndex(0);
    else if(text == "更多")
        ui->stackedWidget->setCurrentIndex(1);
    else if(text == "设置")
        ui->stackedWidget->setCurrentIndex(2);
}

void frmMain::closeWidget()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(1000);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start();
    connect(animation, SIGNAL(finished()), this, SLOT(close()));
}
