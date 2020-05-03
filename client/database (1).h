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

    static DataBase *getDatabaseInstence();  //静态的获取数据库对象的函数
    //插入一个订单信息
    bool insertUsr(int number,QString id,QString object,QString start,QString aim,QString time,QString value,QString credit);
    //根据number删除订单信息
    bool deleteUsr(int number);
    //根据number调整物品
    bool modifyUsr(int number, QString object);
private:
    DataBase();
QSqlDatabase db_;
};

#endif // DATABASE_H
