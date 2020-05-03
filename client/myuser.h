#ifndef MYUSER_H
#define MYUSER_H


#include <QMainWindow>

class myuser
{
public:
    myuser(QString="",QString="",QString="");//我的用户初始化
    static myuser* getuser(QString="",QString="",QString="");//获得我的用户的指针
    QString getid();//获得我的id
    QString getcre();//获得我的信用值
    QString getpho();//获得我的电话号码
private:
    QString myuserid;
    QString myusercredit;
    QString myuserphone;
};

#endif // MYUSER_H
