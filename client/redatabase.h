#ifndef REDATABASE_H
#define REDATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>

class ReDataBase
{
public:

    static ReDataBase *getDatabaseInstence(QString);  //静态的获取数据库对象的函数
    //插入一个订单信息
    bool insertRe(int number,QString name, QString object,QString start,QString aim,QString time,QString value,int credit);
    //根据number删除订单信息
    bool deleteRe(int number);
    //根据number调整物品
    bool modifyRe(int number, QString object);
    //返回所有结果
    /*QString **Re();*/
private:
    ReDataBase(QString);
    QSqlDatabase db_;
};

#endif // REDATABASE_H
