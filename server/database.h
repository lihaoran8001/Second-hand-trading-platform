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
    //插入一个用户信息
    bool insertUsr(QString id,QString pwd,QString phone,QString credit);
    //根据id查找用户
    bool findUsr(QString id);
    //匹配id和pwd
    bool judge(QString id, QString pwd);
    //用户修改密码
    void revise(QString id, QString pwd);
    //修改cre
    void revise_cre(QString id,QString newcre);
      //修改pnb
    void revise_pnb(QString id,QString pnb);
    //注销一条用户信息
    void delete_one(QString id);
    //删除所有用户档案
    void delete_all();

    QString getCredit(QString);
    QString getphone(QString);
private:
    DataBase();
    QSqlDatabase db_;
};

#endif // DATABASE_H
