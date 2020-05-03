#ifndef SENDDATABASE_H
#define SENDDATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>

class SendDataBase
{
public:

    static SendDataBase *getDatabaseInstence(QString);  //静态的获取数据库对象的函数
    //插入一个订单信息
    bool insertSend(int number,QString object,QString start,QString aim,QString time,QString value);
    //根据number删除订单信息
    bool deleteSend(int number);
    //根据number调整物品
    bool modifySend(int number, QString object);
    //返回所有结果

private:
    SendDataBase(QString);
    QSqlDatabase db_;
};

#endif // SENDDATABASE_H
