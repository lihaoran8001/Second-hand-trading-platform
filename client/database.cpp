#include "database.h"

DataBase *DataBase::getDatabaseInstence()
{
    static DataBase sqldb;
    return &sqldb;
}
//插入一个订单信息
bool DataBase::insertUsr(int number,QString id,QString object,QString start,QString aim,QString time,QString value,int credit)
{
    QString sql = QString("insert into t_order1 values(%1, '%2', '%3', '%4', '%5', '%6', '%7', %8)")
            .arg(number)
            .arg(id)
            .arg(object)
            .arg(start)
            .arg(aim)
            .arg(time)
            .arg(value)
            .arg(credit);
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
bool DataBase::deleteUsr(int number)
{
    QString sql = QString("delete number from t_order1 where number = :number;");
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
bool DataBase::modifyUsr(int number, QString object)
{
    QString sql = QString("UPDATE t_order1 SET object = '%1' WHERE number = %2").arg (object).arg (number);
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
bool DataBase::delete_all()
{
    QString sql=QString("delete from t_order1");
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
DataBase::DataBase()
{
    //先判断连接是否存在
    if(QSqlDatabase::contains("testConnection2"))
    {
        db_ = QSqlDatabase::addDatabase("testConnection2");
    }
    else
    {
        //1.加载数据库驱动
        db_ = QSqlDatabase::addDatabase("QSQLITE", "testConnection2");
        qDebug () << db_.connectionName();//打印连接名称

        //2.设置数据库名
        db_.setDatabaseName("myorder.db");
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
       QString sql = "create table if not exists t_order1(number int not null, id varchar(20), object varchar(20), start varchar(20),aim varchar(20), time varchar(20), value varchar(20), credit int not null)";
       QSqlQuery query(db_);
       if (query.exec(sql))
       {
           qDebug() << "create success.";
       }

       db_.close();
}
QString* DataBase::find(int number)
{
    QString* st=new QString[7];
    QString sql = QString("select * from t_order1 where number = %1").arg(number);
    //打开数据库
    if(!db_.open())
    {
        qDebug() << "open fail" << db_.lastError().text();
        exit(-1);
    }
    //执行插入操作
    QSqlQuery query(db_);
    query.exec(sql);
    query.next();
    st[0]=query.value(1).toString();
    st[1]=query.value(2).toString();
    st[2]=query.value(3).toString();
    st[3]=query.value(4).toString();
    st[4]=query.value(5).toString();
    st[5]=query.value(6).toString();
    st[6]=query.value(7).toString();
    return st;
}
