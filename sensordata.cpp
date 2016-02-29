#include "sensordata.h"
#include "ui_sensordata.h"
#include "api/app.h"

#define TextColor QColor(255,255,255)

#define TextWidth 1
#define LineWidth 2
#define DotWidth 10
#define Plot_NoColor QColor(0,0,0,0)

#define Plot1_DotColor QColor(5,189,251)
#define Plot1_LineColor QColor(41,138,220)
#define Plot1_BGColor QColor(41,138,220,80)

#define Plot2_DotColor QColor(236,110,0)
#define Plot2_LineColor QColor(246,98,0)
#define Plot2_BGColor QColor(246,98,0,80)

#define Plot3_DotColor QColor(65,225,36)
#define Plot3_LineColor QColor(70,210,30)
#define Plot3_BGColor QColor(70,210,30,80)

frmSensorData::frmSensorData(QWidget *parent)
    : QWidget(parent), ui(new Ui::frmSensorData)
{
    ui->setupUi(this);

    plots.append(ui->plot_temperature);
    plots.append(ui->plot_humidity);
    plots.append(ui->plot_light);

    InitPlot();
    InitPlot1();
    InitPlot2();
    InitPlot3();
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

void frmSensorData::InitPlot1()
{
    plots.at(0)->addGraph();
    plots.at(0)->graph(0)->setName("温度值(单位:℃)");
    plots.at(0)->graph(0)->setPen(QPen(Plot1_LineColor, LineWidth));
    plots.at(0)->graph(0)->setScatterStyle(
                QCPScatterStyle(QCPScatterStyle::ssCircle,
                                QPen(Plot1_DotColor, LineWidth),
                                QBrush(Plot1_DotColor), DotWidth));
    plots.at(0)->xAxis->setRange(0, 100);
    plots.at(0)->yAxis->setRange(0, 40);
}

void frmSensorData::InitPlot2()
{
    plots.at(1)->addGraph();
    plots.at(1)->graph(0)->setName("湿度值(单位:%)");
    plots.at(1)->graph(0)->setPen(QPen(Plot2_LineColor,LineWidth));
    plots.at(1)->graph(0)->setScatterStyle(
                QCPScatterStyle(QCPScatterStyle::ssCircle,
                                QPen(Plot2_DotColor,LineWidth),
                                QBrush(Plot2_DotColor), DotWidth));
    plots.at(1)->xAxis->setRange(0, 100);
    plots.at(1)->yAxis->setRange(0, 100);
}

void frmSensorData::InitPlot3()
{
    plots.at(2)->addGraph();
    plots.at(2)->graph(0)->setName("光照值(单位：lx)");
    plots.at(2)->graph(0)->setPen(QPen(Plot3_LineColor, LineWidth));
    plots.at(2)->graph(0)->setScatterStyle(
                QCPScatterStyle(QCPScatterStyle::ssCircle,
                                QPen(Plot3_DotColor,LineWidth),
                                QBrush(Plot3_DotColor), DotWidth));
    plots.at(2)->xAxis->setRange(0, 100);
    plots.at(2)->yAxis->setRange(0, 1000);
}

void frmSensorData::on_ckMove_stateChanged(int state)
{
    bool value = (state == 0 ? false : true);
    foreach(QCustomPlot *plot, plots){
        if (value) {
            plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
        } else {
            plot->setInteractions(QCP::iSelectOther);
        }
        plot->replot();
    }
}

void frmSensorData::on_ckBackground_stateChanged(int state)
{
    bool value = (state == 0 ? false : true);
    if (value) {
        plots[0]->graph(0)->setBrush(QBrush(Plot1_BGColor));
        plots[1]->graph(0)->setBrush(QBrush(Plot2_BGColor));
        plots[2]->graph(0)->setBrush(QBrush(Plot3_BGColor));
    } else {
        plots[0]->graph(0)->setBrush(QBrush(Plot_NoColor));
        plots[1]->graph(0)->setBrush(QBrush(Plot_NoColor));
        plots[2]->graph(0)->setBrush(QBrush(Plot_NoColor));
    }
    plots[0]->replot();
    plots[1]->replot();
    plots[2]->replot();
}

void frmSensorData::on_ckLegend_stateChanged(int state)
{
    bool value = (state == 0 ? false : true);
    foreach(QCustomPlot *plot, plots){
        plot->legend->setVisible(value);
        plot->replot();
    }
}

void frmSensorData::on_ckXGrid_stateChanged(int state)
{
    bool value = (state == 0 ? false : true);
    foreach(QCustomPlot *plot, plots){
        plot->xAxis->grid()->setSubGridVisible(value);
        plot->replot();
    }
}

void frmSensorData::on_ckYGrid_stateChanged(int state)
{
    bool value = (state == 0 ? false : true);
    foreach(QCustomPlot *plot, plots){
        plot->yAxis->grid()->setSubGridVisible(value);
        plot->replot();
    }
}

void frmSensorData::on_ckTemperatureData_stateChanged(int state)
{
    bool value = (state == 0 ? false : true);
    if(value){
        plots.at(0)->show();
    }
    else{
        plots.at(0)->hide();
    }
}

void frmSensorData::on_ckHumidityData_stateChanged(int state)
{
    bool value = (state == 0 ? false : true);
    if(value){
        plots.at(1)->show();
    }
    else{
        plots.at(1)->hide();
    }
}

void frmSensorData::on_ckLightData_stateChanged(int state)
{
    bool value = (state == 0 ? false : true);
    if(value){
        plots.at(2)->show();
    }
    else{
        plots.at(2)->hide();
    }
}
