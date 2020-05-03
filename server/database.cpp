#include "database.h"

DataBase *DataBase::getDatabaseInstence()
{
    static DataBase sqldb;
    return &sqldb;
}
//插入一个用户信息
bool DataBase::insertUsr(QString id,QString pwd,QString phone,QString credit)
{
    QString sql = QString("insert into t_usr2 values('%1', '%2', '%3', '%4')")
            .arg(id)
            .arg(pwd)
            .arg(phone)
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
//根据id查找用户
bool DataBase::findUsr(QString id)
{
    QString sql = QString("select id from t_usr2 where id = :id;");
    //打开数据库
    if(!db_.open())
    {
        qDebug() << "open fail" << db_.lastError().text();
        exit(-1);
    }
    //执行插入操作
    QSqlQuery query(db_);
    query.prepare(sql);
    query.bindValue(":id",QVariant(id));
    query.exec();
    //查询成功
    if(query.next())
    {
        if(id == query.value(0).toString()) //用户存在
        {
           return true;
        }
    }
    //关闭数据库
    db_.close();
    return false;
}
//匹配id和pwd
bool DataBase::judge(QString id, QString pwd)
{
    QString sql = QString("select id, pwd from t_usr2 where id = :id;");
    //打开数据库
    if(!db_.open())
    {
        qDebug() << "open fail" << db_.lastError().text();
        exit(-1);
    }
    //执行插入操作
    QSqlQuery query(db_);
    query.prepare(sql);
    query.bindValue(":id",QVariant(id));
    query.exec();
    //匹配密码
    if(query.next())
    {
        if(!(pwd == query.value(1).toString()))
        {
          return false;
        }
    }
    //关闭数据库
    db_.close();
    return true;
}
//根据id修改密码
void DataBase::revise(QString id, QString pwd)
{
     QString ModifySql = QString (
                        "UPDATE t_usr2 SET pwd = '%1' WHERE id = '%2'").arg (pwd).arg (id);
if(!db_.open())
    {
        qDebug() << "open fail" << db_.lastError().text();
        exit(-1);
    }
    // 执行插入的sql语句
    QSqlQuery query(db_);
    query.exec (ModifySql);
    db_.close();
}
//根据id删除用户信息
void DataBase::delete_one(QString id)
{
    QString deleteSql = QString (
                        "DELETE FROM t_usr2 WHERE id = '%1'").arg (id);
if(!db_.open())
    {
        qDebug() << "open fail" << db_.lastError().text();
        exit(-1);
    }
    // 执行插入的sql语句
    QSqlQuery query(db_);
    query.exec (deleteSql);
    db_.close();

}
//删除所有信息
void DataBase::delete_all()
{
    QString deleteSql = QString ("DELETE FROM t_usr2");
    if(!db_.open())
    {
        qDebug() << "open fail" << db_.lastError().text();
        exit(-1);
    }
    // 执行插入的sql语句
    QSqlQuery query(db_);
    query.exec (deleteSql);
    db_.close();
}

void DataBase::revise_pnb(QString id,QString pnb)
{

    QString ModifySql = QString (
                       "UPDATE t_usr2 SET phone = '%1' WHERE id = '%2'").arg (pnb).arg (id);
if(!db_.open())
   {
       qDebug() << "open fail" << db_.lastError().text();
       exit(-1);
   }
   // 执行插入的sql语句
   QSqlQuery query(db_);
   query.exec (ModifySql);
   db_.close();
}

void DataBase::revise_cre(QString id,QString newcre)
{
    QString ModifySql = QString (
                       "UPDATE t_usr2 SET credit = '%1' WHERE id = '%2'").arg (newcre).arg (id);
if(!db_.open())
   {
       qDebug() << "open fail" << db_.lastError().text();
       exit(-1);
   }
   // 执行插入的sql语句
   QSqlQuery query(db_);
   query.exec (ModifySql);
   db_.close();
}
DataBase::DataBase()
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
        db_.setDatabaseName("usr2.db");
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
       QString sql = "create table if not exists t_usr2(id varchar(20), pwd varchar(20), phone varchar(20), credit varchar(20));";
       QSqlQuery query(db_);
       if (query.exec(sql))
       {
           qDebug() << "create success.";
       }

       db_.close();
}
QString DataBase::getCredit(QString id)
{
QString sql = QString("select * from t_usr2 where id = :id;");
    //打开数据库
    if(!db_.open())
    {
        qDebug() << "open fail" << db_.lastError().text();
        exit(-1);
    }
    //执行插入操作
    QSqlQuery query(db_);
    query.prepare(sql);
    query.bindValue(":id",QVariant(id));
    query.exec();
    query.next();
    QString credit=query.value(3).toString();
  return credit;

}

QString DataBase::getphone(QString id)
{
QString sql = QString("select * from t_usr2 where id = :id;");
    //打开数据库
    if(!db_.open())
    {
        qDebug() << "open fail" << db_.lastError().text();
        exit(-1);
    }
    //执行插入操作
    QSqlQuery query(db_);
    query.prepare(sql);
    query.bindValue(":id",QVariant(id));
    query.exec();
    query.next();
    QString phone=query.value(2).toString();
    return phone;

}
