#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>

class DataBase
{
public:

    static DataBase *getDatabaseInstence();
    //插入一个订单信息
    bool insertUsr(int number,QString id,QString object,QString start,QString aim,QString time,QString value,int credit);//将订单数据插入数据库
    //根据number删除订单信息
    bool deleteUsr(int number);
    //根据number调整物品
    bool modifyUsr(int number, QString object);
    //清空表的数据
    bool delete_all();
    QString* find(int);//根据编号查找订单相关信息
private:
    DataBase();
QSqlDatabase db_;
};

#endif // DATABASE_H
