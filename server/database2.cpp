#include"database2.h"

DataBase2 *DataBase2::getDatabaseInstence()
{
    static DataBase2 sqldb;
    return &sqldb;
}
bool DataBase2::whether(int num)
{
    QString sql = QString("select * from t_order2 where number = %1").arg(num);
    //打开数据库
        if(!db_.open())
        {
            qDebug() << "open fail" << db_.lastError().text();
            exit(-1);
        }
        //执行插入操作
        QSqlQuery query(db_);
        query.exec(sql);
        if(query.next())
        {
            return true;
        }
        else
        {
            return false;
        }

}
//插入一个订单信息
bool DataBase2::insertUsr(int number,QString id,QString object,QString start,QString aim,QString time,QString value,QString credit,QString id2)
{   
    QString sql = QString("insert into t_order2 values(%1, '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9')")
            .arg(number)
            .arg(id)
            .arg(object)
            .arg(start)
            .arg(aim)
            .arg(time)
            .arg(value)
            .arg(credit)
            .arg(id2);
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
bool DataBase2::deleteUsr(int number)
{
    QString sql = QString("delete from t_order2 where number = %1;").arg(number);
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
//根据number调整派送人
bool DataBase2::modifyUsr(int number, QString id2)
{
    QString sql = QString("UPDATE t_order2 SET id2 = '%1' WHERE number = %2").arg (id2).arg (number);
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
//返回查询结果
QString *DataBase2::re(int number)
{
    QString sql = QString("select * from t_order2 where number = %1").arg(number);
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
    QString *c=new QString[8];
    for(int i=0;i<8;i++)
    {
        c[i]=query.value(i+1).toString();
    }
    db_.close();
    return c;
}
//根据id返回记录条数
int DataBase2::idRecord(QString id)
{
        int a=0;
        QString sql=QString("select * from t_order2 where id = '%1'").arg(id);
        if(!db_.open())
        {
            qDebug() << "open fail" << db_.lastError().text();
            exit(-1);
        }
        QSqlQuery query(db_);
        query.exec(sql);
        while(query.next())
        {
            a=a+1;
        }
        db_.close();
        return a;

}
//根据id返回查询结果
QString *DataBase2::idFind(QString id)
{
    int a=idRecord(id);
    QString *b=new QString[a*9];
    QString sql = QString("select * from t_order2 where id = '%1'").arg(id);
    if(!db_.open())
    {
        qDebug() << "open fail" << db_.lastError().text();
        exit(-1);
    }
    QSqlQuery query2(db_);
    query2.exec(sql);
    for(int i=0;i<a;i++)
    {
        query2.next();
        int n=query2.value(0).toInt();
        b[i*9]=QString::number(n);
        for(int j=1;j<9;j++)
        {
           b[i*9+j]=query2.value(j).toString();
        }
    }
    return b;
}
//根据id2返回记录条数
int DataBase2::id2Record(QString id2)
{
       int a=0;
        QString sql=QString("select * from t_order2 where id2 = '%1'").arg(id2);
        if(!db_.open())
        {
            qDebug() << "open fail" << db_.lastError().text();
            exit(-1);
        }
        QSqlQuery query(db_);
        query.exec(sql);
        while(query.next())
        {
            a=a+1;
        }
        db_.close();
        return a;

}
//根据id2返回查询结果
QString *DataBase2::id2Find(QString id2)
{
    int a=id2Record(id2);
    QString* b=new QString[a*9];
    QString sql = QString("select * from t_order2 where id2 = '%1'").arg(id2);
    if(!db_.open())
    {
        qDebug() << "open fail" << db_.lastError().text();
        exit(-1);
    }
     QSqlQuery query2(db_);
     query2.exec(sql);
     for(int i=0;i<a;i++)
     {
         query2.next();
         int n=query2.value(0).toInt();
         b[i*9]=QString::number(n);
         for(int j=1;j<9;j++)
         {
            b[i*9+j]=query2.value(j).toString();
         }
     }

    return b;
}
//根据起始地，目的地返回记录条数
int DataBase2::Record(QString start,QString aim)
{
    int a=0;
   if(start=="")
    {
       aim="\"%"+aim+"%\"";
        QString sql ="SELECT * from t_order2 WHERE aim LIKE "+aim;
        if(!db_.open())
        {
            qDebug() << "open fail" << db_.lastError().text();
            exit(-1);
        }
        QSqlQuery query(db_);
        query.exec(sql);
        while(query.next())
        {
            a=a+1;
        }
        db_.close();
    }
    if(aim=="")
  {
        QString sql ="SELECT * from t_order2 WHERE aim LIKE "+start;
    if(!db_.open())
    {
        qDebug() << "open fail" << db_.lastError().text();
        exit(-1);
    }
    QSqlQuery query(db_);
    query.exec(sql);
    while(query.next())
    {
        a=a+1;
    }
    db_.close();
}
  if(start!=""&&aim!="")
{
      aim="\"%"+aim+"%\"";
      start="\"%"+start+"%\"";
        QString sql="SELECT * from t_order2 WHERE start LIKE "+start+ "and aim LIKE "+aim;
        if(!db_.open())
        {
            qDebug() << "open fail" << db_.lastError().text();
            exit(-1);
        }
        QSqlQuery query(db_);
        query.exec(sql);
        while(query.next())
        {
            a=a+1;
        }
        db_.close();
}
    return a;
}
//根据起始地 目的地查询
 QString *DataBase2::pFind(QString start,QString aim)
    {
        int a= Record(start,aim);
        QString *b=new QString[a*9];
        if(start=="")
        {
            aim="\"%"+aim+"%\"";
            QString sql ="SELECT * from t_order2 WHERE aim LIKE "+aim;
            if(!db_.open())
            {
                qDebug() << "open fail" << db_.lastError().text();
                exit(-1);
            }
             QSqlQuery query2(db_);
             query2.exec(sql);
            for(int i=0;i<a;i++)
            {
                query2.next();
                int n=query2.value(0).toInt();
                 b[i*9]=QString::number(n);
                for(int j=1;j<9;j++)
                {
                   b[i*9+j]=query2.value(j).toString();
                }
            }
        }
       if(aim=="")
      {
         start="\"%"+start+"%\"";
         QString sql ="SELECT * from t_order2 WHERE aim LIKE "+start;
        if(!db_.open())
        {
            qDebug() << "open fail" << db_.lastError().text();
            exit(-1);
        }
        QSqlQuery query2(db_);
        query2.exec(sql);
       for(int i=0;i<a;i++)
       {
          query2.next();
          int n=query2.value(0).toInt();
          b[i*9]=QString::number(n);
           for(int j=1;j<9;j++)
           {
              b[i*9+j]=query2.value(j).toString();
           }
       }

    }
        if(start!=""&&aim!="")
{
            aim="\"%"+aim+"%\"";
            start="\"%"+start+"%\"";
        QString sql="SELECT * from t_order2 WHERE start LIKE "+start+ "and aim LIKE "+aim;
            if(!db_.open())
            {
                qDebug() << "open fail" << db_.lastError().text();
                exit(-1);
            }
            QSqlQuery query2(db_);
            query2.exec(sql);
           for(int i=0;i<a;i++)
           {
              query2.next();
              int n=query2.value(0).toInt();
               b[i*9]=QString::number(n);
               for(int j=1;j<9;j++)
               {
                  b[i*9+j]=query2.value(j).toString();
               }
           }

}
    return b;
 }


DataBase2::DataBase2()
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
        db_.setDatabaseName("order2.db");
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
       QString sql = "create table if not exists t_order2(number int not null, id varchar(20), object varchar(20), start varchar(20),aim varchar(20), time varchar(20), value varchar(20), credit varchar(20), id2 varchar(20))";
       QSqlQuery query(db_);
       if (query.exec(sql))
       {
           qDebug() << "create success.";
       }

       db_.close();
}

void DataBase2::delete_all()
{
    QString deleteSql = QString ("DELETE FROM t_order2");
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
