#ifndef DATABASE2_H
#define DATABASE2_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>


class DataBase2
{
public:

    static DataBase2 *getDatabaseInstence();  //静态的获取数据库对象的函数
    //插入一个订单信息
    bool insertUsr(int number,QString id,QString object,QString start,QString aim,QString time,QString value,QString credit,QString id2);
    //根据number删除订单信息
    bool deleteUsr(int number);
    //根据number调整派送人
    bool modifyUsr(int number, QString id2);
    //返回查询结果
    QString *re(int number);
    //根据发单人id返回记录条数
    int idRecord(QString id);
    //根据发单人id返回查询结果
    QString *idFind(QString id);
    //根据派送人id返回记录条数
    int id2Record(QString id2);
      //根据派送人id返回查询结果
      QString *id2Find(QString id2);
      //根据起始地，目的地返回记录条数
      int Record(QString start,QString aim);
      //根据起始地，目的地返回查询结果
      QString *pFind(QString start,QString aim);

      bool whether(int num);
    void delete_all();
private:
    DataBase2();
    QSqlDatabase db_;
};
#endif // DATABASE2_H
