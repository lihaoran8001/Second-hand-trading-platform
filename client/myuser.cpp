#include "myuser.h"

myuser::myuser(QString id,QString cre,QString pho)
{
    myuserid=id;
    myusercredit=cre;
    myuserphone=pho;
}

myuser* myuser::getuser(QString id,QString cre,QString pho)
{
    static myuser muser(id,cre,pho);
    return &muser;
}

QString myuser::getid()
{
    return myuserid;
}

QString myuser::getcre()
{
    return myusercredit;
}

QString myuser::getpho()
{
    return myuserphone;
}
