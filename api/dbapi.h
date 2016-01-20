#ifndef DBAPI_H
#define DBAPI_H

#include <QObject>

class QtSql;
class QTableView;
class QLabel;
class QAbstractButton;
class QComboBox;
class QSqlQueryModel;

class DBAPI : public QObject
{
    Q_OBJECT
private:
    explicit DBAPI(QObject *parent = 0);
    static DBAPI *_instance;

    void BindData(QString sql);

    int StartIndex;             //分页开始索引,每次翻页都变动
    QString TempSql;            //临时SQL语句
    QString Sql;
    QSqlQueryModel *QueryModel; //查询模型

    int RowsCount;              //每页显示行数
    int RowsCountAll;           //总行数
    int PageCount;              //总页数
    int PageCurrent;            //当前第几页

public:
    static DBAPI *Instance() {
        if (!_instance) {
            _instance = new DBAPI;
        }
        return _instance;
    }

    //查询对应记录条数
    int SelectCount(QString tableName, QString where);

    //绑定查询数据,带分页/行数/条件/排序/列名/列宽
    void BindData(QTableView *tableView, QSqlQueryModel *queryModel, QString tableName, QString selectColumns,
                  QString order, QString where, QList<QString> columnNames, QList<int> columnWidths);

    //设置需要显示数据的表格,数据翻页对应的按钮
    void SetControl(QTableView *tableView, QLabel *labInfo,
                    QAbstractButton *btnFirst, QAbstractButton *btnPre,
                    QAbstractButton *btnNext, QAbstractButton *btnLast);

    //绑定查询数据,带分页/行数/条件/排序/列名/列宽
    void BindDataSelect(QString tableName, QString orderColumn,
                        QString orderType, QString where, int rowsCount,
                        QList<QString> columnNames, QList<int> columnWidths);

    //绑定数据到下拉框
    void BindData(QString columnName, QString orderColumn, QString tableName, QComboBox *cbox);

signals:

private slots:
    void First();       //第一页
    void Previous();    //上一页
    void Next();        //下一页
    void Last();        //末一页

};

#endif // DBAPI_H
