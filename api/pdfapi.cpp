#include "pdfapi.h"
#include "myhelper.h"

PdfAPI *PdfAPI::_instance = 0;
PdfAPI::PdfAPI(QObject *parent) : QObject(parent)
{

}

void PdfAPI::SavePDF(QString file, QString title, QString type, QList<QString> columnNames, QList<int> columnWidths, QStringList content)
{
    //计算行数列数
    int columnCount = columnNames.count();
    int rowCount = content.count();

    //清空原有数据,确保每次都是新的数据
    html.clear();

    //表格开始
    html.append("<table border='0.5' cellspacing='0' cellpadding='3'>");

    //标题占一行,居中显示
    html.append(QString("<tr><td colspan='%1'>").arg(columnCount));
    html.append("<p align='center' style='vertical-align:middle;font-weight:bold;font-size:15px;'>");
    html.append(title);
    html.append("</p></td></tr>");

    //循环写入字段名,字段名占一行,居中显示
    html.append("<tr>");
    for (int i = 0; i < columnCount; i++) {
        html.append(QString("<td width='%1' bgcolor='lightgray'>").arg(columnWidths.at(i)));
        html.append("<p align='center' style='vertical-align:middle;'>");
        html.append(columnNames.at(i));
        html.append("</p></td>");
    }
    html.append("</tr>");

    //循环一行行构建数据
    for (int i = 0; i < rowCount; i++) {
        QStringList value = content.at(i).split(";");
        html.append("<tr>");
        for (int j = 0; j < columnCount; j++) {
            html.append(QString("<td width='%1'>").arg(columnWidths.at(j)));
            html.append(value.at(j));
            html.append("</td>");
        }
        html.append("</tr>");
    }

    html.append("</table>");

    //调用打印机打印PDF
    QPrinter printer;
    //设置纸张规格
    printer.setPageSize(QPrinter::A4);
    //设置横向纵向及页边距
    if (type == "横向") {
        printer.setOrientation(QPrinter::Landscape);
        printer.setPageMargins(10, 10, 10, 11, QPrinter::Millimeter);
    } else {
        printer.setOrientation(QPrinter::Portrait);
        printer.setPageMargins(10, 10, 10, 15, QPrinter::Millimeter);
    }
    //设置输出格式为PDF
    printer.setOutputFormat(QPrinter::PdfFormat);
    //设置输出文件保存位置
    printer.setOutputFileName(file);

    QTextDocument textDocument;
    textDocument.setHtml(html.join(""));
    textDocument.print(&printer);
    textDocument.end();
}
