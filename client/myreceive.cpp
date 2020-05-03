#include "myreceive.h"
#include "ui_myreceive.h"

myreceive::myreceive(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::myreceive)
{
    ui->setupUi(this);
    base=DataBase::getDatabaseInstence();
    Tcpclient=MainWindow::getSocketadd();
    Myuser=myuser::getuser();
    real=-1;
    B=NULL;
}

myreceive::~myreceive()
{
    delete ui;
}

void myreceive::receivesendcanmr(int c)
{
    QString* str=base->find(c);
    QString i = str[0];
    QString o = str[1];
    QString f = str[2];
    QString t = str[3];
    QString ti = str[4];
    QString m = str[5];
    QString b=str[6];
    real++;
    bill** A=new bill*[real+1];
    for(int i=0;i<real;i++)
         A[i]=B[i];
    delete []B;
    B=A;
//将指针内容扩充
    B[real]=new bill(this);
    B[real]->receivesendcan(c,i,o,f,t,ti,m,b);
    emit changeaddrplusmr();
    if((real+1)*260>650)
        this->resize(850,(real+1)*260+10);
    B[real]->change2();
    B[real]->setGeometry(50,30,750,230);
    B[real]->show();
    connect(this,SIGNAL(changeaddrplusmr()),B[real],SLOT(receivechangeaddrplus()));
}

void myreceive::receiveyiwancheng(int c)
{
    for(int i=0;i<=real;i++)
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
            //缩减指针内容
            }
            else
            {
                delete B;
                B=NULL;
            }
            real--;
        }
}

void myreceive::changeaddrless(int c)
{
    for(int i=0;i<c;i++)
        B[i]->receivechangeaddrless();
}

void myreceive::readinitialmr()
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
            emit changeaddrplusmr();
            B[real]->setGeometry(50,30,750,230);
            B[real]->change2();
            B[real]->show();
            connect(this,SIGNAL(changeaddrplusmr()),B[real],SLOT(receivechangeaddrplus()));
        }
    }
    else
        emit myreceiveok();
}



