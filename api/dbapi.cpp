#include "dbapi.h"
#include "myhelper.h"

QTableView *TableView;      //显示数据的表格对象
QLabel *LabInfo;            //显示翻页信息
QAbstractButton *BtnFirst;  //第一页按钮对象
QAbstractButton *BtnPre;    //上一页按钮对象
QAbstractButton *BtnNext;   //下一页按钮对象
QAbstractButton *BtnLast;   //末一页按钮对象
DBAPI *DBAPI::_instance = 0;

/* 说明:数据库查询及翻页模块
 * 功能:数据库查询及翻页处理
 */
DBAPI::DBAPI(QObject *parent) :
    QObject(parent)
{
    StartIndex = 0;
    TempSql = "";
    Sql = "";
    RowsCount = 0;
    RowsCountAll = 0;
    PageCount = 0;
    PageCurrent = 1;
}

int DBAPI::SelectCount(QString tableName, QString where)
{
    QString sql = QString("select count(*) from %1 %2")
            .arg(tableName).arg(where);
    QSqlQuery query;
    query.exec(sql);
    query.next();
    return query.value(0).toInt();
}

void DBAPI::BindData(QTableView *tableView, QSqlQueryModel *queryModel, QString tableName,
                     QString selectColumns, QString order, QString where,
                     QList<QString> columnNames, QList<int> columnWidths)
{
    QString sql = QString("select %1 from %2 %3 order by %4")
            .arg(selectColumns).arg(tableName).arg(where).arg(order);

    queryModel->setQuery(sql);
    tableView->setModel(queryModel);
    int columnCount=queryModel->columnCount();

    //依次设置列标题列宽
    for (int i = 0; i < columnCount; i++) {
        queryModel->setHeaderData(i, Qt::Horizontal, columnNames.at(i));
        tableView->setColumnWidth(i, columnWidths.at(i));
    }
}

//设置显示数据的表格控件,当前翻页信息的标签控件等
void DBAPI::SetControl(QTableView *tableView, QLabel *labInfo,
                       QAbstractButton *btnFirst, QAbstractButton *btnPre,
                       QAbstractButton *btnNext, QAbstractButton *btnLast)
{
    TableView = tableView;
    LabInfo = labInfo;
    BtnFirst = btnFirst;
    BtnPre = btnPre;
    BtnNext = btnNext;
    BtnLast = btnLast;
    TableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    QueryModel = new QSqlQueryModel(TableView);

    //挂载翻页按钮事件
    connect(BtnFirst, SIGNAL(clicked()), this, SLOT(First()));
    connect(BtnPre, SIGNAL(clicked()), this, SLOT(Previous()));
    connect(BtnNext, SIGNAL(clicked()), this, SLOT(Next()));
    connect(BtnLast, SIGNAL(clicked()), this, SLOT(Last()));
}

//绑定数据到下拉框
void DBAPI::BindData(QString columnName, QString orderColumn, QString tableName, QComboBox *cbox)
{
    QSqlQuery query;
    query.exec("select " + columnName + " from " + tableName + " order by " + orderColumn + " asc");
    while (query.next()) {
        cbox->addItem(query.value(0).toString());
    }
}

void DBAPI::BindData(QString sql)
{
    QueryModel->setQuery(sql);
    TableView->setModel(QueryModel);
    LabInfo->setText(QString("共 %1 条数据  每页 %2 条数据  共 %3 页  第 %4 页").arg(RowsCountAll).arg(RowsCount).arg(PageCount).arg(PageCurrent));
}

//分页绑定查询数据到表格,指定排序列
void DBAPI::BindDataSelect(QString tableName, QString orderColumn,
                           QString orderType, QString where, int rowsCount,
                           QList<QString> columnNames, QList<int> columnWidths)
{
    StartIndex = 0; //重置开始索引
    PageCurrent = 1;
    RowsCount = rowsCount;

    //开始分页绑定数据前,计算好总数据量以及行数
    TempSql = "select count(*) from " + tableName + " " + where;
    QSqlQuery query;
    query.prepare(TempSql);
    query.exec();
    query.first();
    RowsCountAll = query.value(0).toInt();

    int yushu = RowsCountAll % RowsCount;
    //不存在余数,说明是整行,例如300%5==0
    if (yushu == 0) {
        if (RowsCountAll > 0 && RowsCountAll < RowsCount) {
            PageCount = 1;
        } else {
            PageCount = RowsCountAll / RowsCount;
        }
    } else {
        PageCount = RowsCountAll / RowsCount + 1;
    }

    //增加翻页按钮可用不可用处理,如果只有一页数据,则翻页按钮不可用
    if (PageCount <= 1) {
        BtnFirst->setEnabled(false);
        BtnLast->setEnabled(false);
        BtnNext->setEnabled(false);
        BtnPre->setEnabled(false);
    } else {
        BtnFirst->setEnabled(true);
        BtnLast->setEnabled(true);
        BtnNext->setEnabled(true);
        BtnPre->setEnabled(true);
    }

    TempSql = "select * from " + tableName + " " + where + " order by " + orderColumn + " " + orderType;
    Sql = QString("%1 limit %2,%3;").arg(TempSql).arg(StartIndex).arg(RowsCount); //组织分页SQL语句
    BindData(Sql);
    int columnCount=TableView->model()->columnCount();

    //依次设置列标题列宽
    for (int i = 0; i < columnCount ; i++) {
        QueryModel->setHeaderData(i, Qt::Horizontal, columnNames.at(i));
        TableView->setColumnWidth(i, columnWidths.at(i));
    }
}

//第一页
void DBAPI::First()
{
    if (PageCount > 1) {
        StartIndex = 0;
        PageCurrent = 1;
        Sql = QString("%1 limit %2,%3;").arg(TempSql).arg(StartIndex).arg(RowsCount); //组织分页SQL语句
        BindData(Sql);
        BtnLast->setEnabled(true);
        BtnNext->setEnabled(true);
    }

    BtnFirst->setEnabled(false);
    BtnPre->setEnabled(false);
}

//上一页
void DBAPI::Previous()
{
    if (PageCurrent > 1) {
        PageCurrent--;
        StartIndex -= RowsCount;
        Sql = QString("%1 limit %2,%3;").arg(TempSql).arg(StartIndex).arg(RowsCount); //组织分页SQL语句
        BindData(Sql);
        BtnLast->setEnabled(true);
        BtnNext->setEnabled(true);
    }

    if (PageCurrent == 1) {
        BtnFirst->setEnabled(false);
        BtnPre->setEnabled(false);
    }
}

//下一页
void DBAPI::Next()
{
    if (PageCurrent < PageCount) {
        PageCurrent++;
        StartIndex += RowsCount;
        Sql = QString("%1 limit %2,%3;").arg(TempSql).arg(StartIndex).arg(RowsCount); //组织分页SQL语句
        BindData(Sql);
        BtnFirst->setEnabled(true);
        BtnPre->setEnabled(true);
    }

    if (PageCurrent == PageCount) {
        BtnLast->setEnabled(false);
        BtnNext->setEnabled(false);
    }
}

//末一页
void DBAPI::Last()
{
    if (PageCount > 0) {
        StartIndex = (PageCount - 1) * RowsCount;
        PageCurrent = PageCount;
        Sql = QString("%1 limit %2,%3;").arg(TempSql).arg(StartIndex).arg(RowsCount); //组织分页SQL语句
        BindData(Sql);
        BtnFirst->setEnabled(true);
        BtnPre->setEnabled(true);
    }

    BtnLast->setEnabled(false);
    BtnNext->setEnabled(false);
}
