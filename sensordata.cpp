#include "sensordata.h"
#include "ui_sensordata.h"
#include "api/app.h"

#define TextColor QColor(255,255,255)

#define TextWidth 1
#define LineWidth 2
#define DotWidth 10
#define Plot1_DotColor QColor(5,189,251)
#define Plot1_LineColor QColor(41,138,220)

frmSensorData::frmSensorData(QWidget *parent)
    : QWidget(parent), ui(new Ui::frmSensorData)
{
    ui->setupUi(this);

    plots.append(ui->plot_temperature);
    plots.append(ui->plot_humidity);
    plots.append(ui->plot_light);

    InitPlot();
}

frmSensorData::~frmSensorData()
{
    delete ui;
}

void frmSensorData::InitPlot()
{
    //设置纵坐标名称
    plots.at(0)->yAxis->setLabel("温度数据统计");
    plots.at(1)->yAxis->setLabel("湿度数据统计");
    plots.at(2)->yAxis->setLabel("光照强度数据统计");

    QFont font = QFont(App::AppFontName, 8);
    foreach (QCustomPlot * plot, plots) {
        //设置字体大小
        plot->legend->setFont(font);
        plot->xAxis->setLabelFont(font);
        plot->yAxis->setLabelFont(font);
        plot->xAxis->setTickLabelFont(font);
        plot->yAxis->setTickLabelFont(font);

        //设置坐标颜色/坐标名称颜色
        plot->yAxis->setLabelColor(TextColor);
        plot->xAxis->setTickLabelColor(TextColor);
        plot->yAxis->setTickLabelColor(TextColor);
        plot->xAxis->setBasePen(QPen(TextColor, TextWidth));
        plot->yAxis->setBasePen(QPen(TextColor, TextWidth));
        plot->xAxis->setTickPen(QPen(TextColor, TextWidth));
        plot->yAxis->setTickPen(QPen(TextColor, TextWidth));
        plot->xAxis->setSubTickPen(QPen(TextColor, TextWidth));
        plot->yAxis->setSubTickPen(QPen(TextColor, TextWidth));

        //设置画布背景色
        QLinearGradient plotGradient;
        plotGradient.setStart(0, 0);
        plotGradient.setFinalStop(0, 350);
        plotGradient.setColorAt(0, QColor(80, 80, 80));
        plotGradient.setColorAt(1, QColor(50, 50, 50));
        plot->setBackground(plotGradient);

        //        //设置坐标背景色
        QLinearGradient axisRectGradient;
        axisRectGradient.setStart(0, 0);
        axisRectGradient.setFinalStop(0, 350);
        axisRectGradient.setColorAt(0, QColor(80, 80, 80));
        axisRectGradient.setColorAt(1, QColor(30, 30, 30));
        plot->axisRect()->setBackground(axisRectGradient);

        //设置图例提示位置及背景色
        plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop | Qt::AlignRight);
        plot->legend->setBrush(QColor(255, 255, 255, 200));
        plot->replot();
    }
}
