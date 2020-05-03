#include "searchshow.h"
#include "ui_searchshow.h"
#include "mainwindow.h"

searchshow::searchshow(QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::searchshow)
{
    ui->setupUi(this);
    Tcpclient=MainWindow::getSocketadd();
    base=DataBase::getDatabaseInstence();
    cid=MainWindow::getCid();
    Myuser=myuser::getuser();
    B=NULL;
    real=-1;
}

searchshow::~searchshow()
{
    delete ui;
}

void searchshow::readsearch()
{
    QByteArray buffer=Tcpclient->readAll();
    QString msg=QString(buffer);
    QString order=msg.section('/',1,1);
    if(order=="result")
    {
        QString count=msg.section('/',2,2);
        QString Id=msg.section('/',3,3);
        QString Obj=msg.section('/',4,4);
        QString From=msg.section('/',5,5);
        QString To=msg.section('/',6,6);
        QString Time=msg.section('/',7,7);
        QString Mon=msg.section('/',8,8);
        QString Cre=msg.section('/',9,9);
        int c=count.toInt();
        int cr=Cre.toInt();
    //获取订单的信息
        if((base->insertUsr(c,Id,Obj,From,To,Time,Mon,cr))==1)
        {
            real++;
            bill** A=new bill*[real+1];
            for(int i=0;i<real;i++)
                A[i]=B[i];
            delete []B;
            B=A;
    //将指针内容扩充
            B[real]=new bill(ui->uwidget);
            B[real]->receivesendcan(c,Id,Obj,From,To,Time,Mon,Cre);
            if((real+1)*260>530)
                ui->uwidget->resize(850,(real+1)*260+10);
            emit changeaddrplus();
            B[real]->setGeometry(50,0,750,230);
            connect(this,SIGNAL(changeaddrplus()),B[real],SLOT(receivechangeaddrplus()));
            if(Id==Myuser->getid())
            {
                B[real]->change();
            }
            B[real]->show();
        }
    }
    else
    {
        disconnect(Tcpclient,SIGNAL(readyRead()),this,SLOT(readsearch()));
        emit connecttcp();
    }
}

void searchshow::receivesendcanmysearch(int c)
{
    for(int i=0;i<=real;i++)
        if((B[i]->getcount())==c)
        {
            if(real>2)
                ui->uwidget->resize(850,real*260+10);
            else
                ui->uwidget->resize(850,530);
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

void searchshow::on_searchButton_clicked()
{
    this->clear();
    emit disconnecttcp();
    connect(Tcpclient,SIGNAL(readyRead()),this,SLOT(readsearch()));
    QString from=ui->FromEdit->text();
    QString to=ui->ToEdit->text();
    QString mycid=QString::number(*cid);
    QString buffer="/searchfor/"+mycid+"/"+from+"/"+to;
    Tcpclient->write(buffer.toUtf8());
}

void searchshow::clear()
{
    if(real!=-1)
    {
        for(int i=0;i<=real;i++)
            B[i]->close();
        delete []B;
        B=NULL;
    }
    real=-1;
}

void searchshow::changeaddrless(int c)
{
    for(int i=0;i<c;i++)
        B[i]->receivechangeaddrless();
}

void searchshow::setcolor()
{
    ui->searchwidget->setStyleSheet("background-color: rgba(255, 255, 255,100)");
}

