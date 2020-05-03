#include "mysend.h"
#include "ui_mysend.h"
#include "wait.h"
#include <QMessageBox>
#include <QStyle>

mysend::mysend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mysend)
{
    ui->setupUi(this);
    base=DataBase::getDatabaseInstence();
    Tcpclient=MainWindow::getSocketadd();
    Myuser=myuser::getuser();
    connect(Tcpclient,SIGNAL(readyRead()),this,SLOT(readinitialms()));
    int *cid=MainWindow::getCid();
    QString id=Myuser->getid();
    QString mycid=QString::number(*cid);
    QString order="/havelogged1/"+mycid+"/"+id;
    Tcpclient->write(order.toUtf8());
    real=-1;
    B=NULL;
}

mysend::~mysend()
{
    delete ui;
}

void mysend::receivesendcanms(int c)
{
    int needs=1;
    for(int i=0;i<=real;i++)
        if(B[i]->getcount()==c)
            needs=0;
    if(needs==1)
    {
    QString* str=base->find(c);
    QString i = str[0];
    QString o = str[1];
    QString f = str[2];
    QString t = str[3];
    QString ti = str[4];
    QString m = str[5];
    QString b= str[6];
    real++;
    bill** A=new bill*[real+1];
    for(int i=0;i<real;i++)
        A[i]=B[i];
    delete []B;
    B=A;
//将指针内容扩充
    B[real]=new bill(this);
    B[real]->receivesendcan(c,i,o,f,t,ti,m,b);
    emit changeaddrplusms();
    if((real+1)*260>650)
        this->resize(850,(real+1)*260+10);
    B[real]->setGeometry(50,30,750,230);
    B[real]->change();
    B[real]->show();
    connect(this,SIGNAL(changeaddrplusms()),B[real],SLOT(receivechangeaddrplus()));
    }
}

void mysend::receivesendcanmsc(int c,QString id,QString cr,QString p)
{
    for(int i=0;i<=real;i++)
        if(c==B[i]->getcount())
        {
            connect(B[i],SIGNAL(showwait(QString,QString,QString)),this,SLOT(receiveshowwait(QString,QString,QString)));
            B[i]->change3();
            B[i]->setreceivei(id);
            B[i]->setreceivec(cr);
            B[i]->setreceivep(p);
        }
}//

void mysend::receivecancel(int c)
{
    for(int i=0;i<=real;i++)
    {
        if(B[i]->getcount()==c)
        {
            if(real>2)
                this->resize(850,real*260+10);
            else
                this->resize(850,650);
            B[i]->close();
            changeaddrless(i);
            //该订单消失
            if(real>0)
            {
            bill** A=new bill*[real];
            for(int j=0;j<i;j++)
                A[j]=B[j];
            for(int j=i+1;j<=real;j++)
                A[j-1]=B[j];
            delete []B;
            B=A;
            }
            else
            {
                delete B;
                B=NULL;
            }
            real--;
            //缩减指针内容
        }
    }
}

void mysend::changeaddrless(int c)
{
    for(int i=0;i<c;i++)
        B[i]->receivechangeaddrless();
}

void mysend::receiveshowwait(QString i,QString c,QString p)
{
    wait* Wait=new wait;
    Wait->setcontent(i,c,p);
    Wait->show();
}

void mysend::readinitialms()
{
    QByteArray buffer=Tcpclient->readAll();
    QString msg=QString(buffer);
    QString title=msg.section('/',1,1);
    if(title=="newbill")
    {
        QString coun=msg.section('/',2,2);
        int c=coun.toInt();
        QString i = msg.section('/',3,3);
        QString o = msg.section('/',4,4);
        QString f = msg.section('/',5,5);
        QString t = msg.section('/',6,6);
        QString ti = msg.section('/',7,7);
        QString m = msg.section('/',8,8);
        QString cre= msg.section('/',9,9);
        int b=cre.toInt();
        if((base->insertUsr(c,i,o,f,t,ti,m,b))==1)
        {
            real++;
            bill** A=new bill*[real+1];
            for(int i=0;i<real;i++)
                A[i]=B[i];
            delete B;
            B=A;
            //将指针内容扩充
            B[real]=new bill(this);
            B[real]->receivesendcan(c,i,o,f,t,ti,m,cre);
            if((real+1)*260>650)
                this->resize(850,(real+1)*260+10);
            emit changeaddrplusms();
            B[real]->setGeometry(50,30,750,230);
            B[real]->change();
            B[real]->show();
            connect(this,SIGNAL(changeaddrplusms()),B[real],SLOT(receivechangeaddrplus()));
            QString reid=msg.section('/',10,10);
            if(reid!="")
            {
                QString recre=msg.section('/',11,11);
                QString repho=msg.section('/',12,12);
                connect(B[real],SIGNAL(showwait(QString,QString,QString)),this,SLOT(receiveshowwait(QString,QString,QString)));
                B[real]->change3();
                B[real]->setreceivei(reid);
                B[real]->setreceivec(recre);
                B[real]->setreceivep(repho);
             }
        }
    }
    else if(title=="nobill")
        emit mysendok();
}


