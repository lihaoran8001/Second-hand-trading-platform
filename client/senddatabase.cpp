#include "senddatabase.h"

SendDataBase *SendDataBase::getDatabaseInstence(QString myuser)
{
    static SendDataBase sqldb(myuser);
    return &sqldb;
}
//插入一个订单信息
bool SendDataBase::insertSend(int number,QString object,QString start,QString aim,QString time,QString value)
{
    QString sql = QString("insert into t_send values(%1, '%2', '%3', '%4', '%5', '%6')")
            .arg(number)
            .arg(object)
            .arg(start)
            .arg(aim)
            .arg(time)
            .arg(value);
    // 1.打开数据
    if (!db_.open())
    {
        qDebug() << "open:" << db_.lastError().text();
        return false;
    }
    // 2.执行sql
    QSqlQuery query(db_);
    if (!query.exec(sql))
    {
        qDebug() << "insert:" << query.lastError().text();
        return false;
    }
    //关闭数据库
    db_.close();
    return true;
}
//根据number删除订单信息
bool SendDataBase::deleteSend(int number)
{
    QString sql = QString("delete from t_send where number = %1").arg(number);
    //打开数据库
    if(!db_.open())
    {
        qDebug() << "open fail" << db_.lastError().text();
        exit(-1);
    }
    //执行插入操作
    QSqlQuery query(db_);
    if (!query.exec(sql))
    {
        qDebug() << "delete:" << query.lastError().text();
        return false;
    }
    //关闭数据库
    db_.close();
    return true;
}
//根据number调整信息
bool SendDataBase::modifySend(int number, QString object)
{
    QString sql = QString("UPDATE t_send SET object = '%1' WHERE number = %2").arg (object).arg (number);
    //打开数据库
    if(!db_.open())
    {
        qDebug() << "open fail" << db_.lastError().text();
        exit(-1);
    }
    //执行插入操作
    QSqlQuery query(db_);
    if (!query.exec(sql))
    {
        qDebug() << "modify:" << query.lastError().text();
        return false;
    }
    //关闭数据库
    db_.close();
    return true;
}
//返回所有结果
/*QString *[6]SendDataBase::Send()
{
    QSqlQuery query(db_);
    query.exec("select number from t_send");
    int a = query.size();// 获取查询结果中记录的个数
    QString *[6]c;
    for(int i=0;i<a;i++)
    {
       QString sql = QString("select * from t_send where number = %1").arg(i);
        QSqlQuery query2(db_);
        query2.exec(sql);
        for(int j=0;j<6;j++)
        {
           c[i][j]=query2.value(j).toString();
        }

    }

    return c;


}*/
SendDataBase::SendDataBase(QString muser)
{
    //先判断连接是否存在
    if(QSqlDatabase::contains("testConnection"))
    {
        db_ = QSqlDatabase::addDatabase("testConnection");
    }
    else
    {
        //1.加载数据库驱动
        db_ = QSqlDatabase::addDatabase("QSQLITE", "testConnection");
        qDebug () << db_.connectionName();//打印连接名称

        //2.设置数据库名
        QString title=muser+"send.db";
        db_.setDatabaseName(title);
        qDebug () << db_.databaseName();
    }

    //3.打开数据库
       if(db_.open())
       {
           qDebug() << "open success";
       }
       else
       {
           qDebug() << "open:" << db_.lastError().text();
           return;
       }
       //4.操作数据库：执行sql语句(integer类型的主键会自增)
       QString sql = "create table if not exists t_send(number int not null, object varchar(20), start varchar(20),aim varchar(20), time varchar(20), value varchar(20))";
       QSqlQuery query(db_);
       if (query.exec(sql))
       {
           qDebug() << "create success.";
       }


       db_.close();
}
