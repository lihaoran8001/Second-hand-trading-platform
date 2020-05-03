#include "start.h"
#include "ui_start.h"
#include "mainwindow.h"
#include "dialogzhuce.h"
#include "bill.h"
#include "mysend.h"
#include "myreceive.h"
#include "search.h"
#include <QMessageBox>
#include <QVBoxLayout>
#include <QTextCodec>
#include <QPushButton>
#include "revise.h"

Start::Start(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Start)
{
    ui->setupUi(this);
    tcpClient=MainWindow::getSocketadd(); //设置网络连接
    base=DataBase::getDatabaseInstence();//设置数据库
    if(base->delete_all())
    {
    Myuser=myuser::getuser();  //设置使用用户
    ui->label_3->setText(Myuser->getid());
    ui->label_4->setText(Myuser->getcre());  //将用户Id 和 信用值显示在左上角
    pArea1= new QScrollArea(this);
    pArea1->setWidget(ui->widget);
    pArea1->setGeometry(158,38,854,654);
    pArea1->setStyleSheet("background-color: rgba(255, 255, 255, 0)");
    ui->widget->setGeometry(0,0,850,650);   //将主界面放在QScrollArea里
    Mysend=new mysend(this);  //初始化我已发出的订单的widget
    pArea2= new QScrollArea(this);
    pArea2->setWidget(Mysend);     //将我的发单界面放在QScrollArea2里
    pArea2->setGeometry(158,38,854,654);
    pArea2->setStyleSheet("background-color: rgba(255, 255, 255, 0)");
    Mysend->setGeometry(0,0,850,650);
    pArea2->hide();//设置mysend位置
    Myreceive=new myreceive(this);    //初始化我已接受的订单的widget
    pArea3= new QScrollArea(this);
    pArea3->setWidget(Myreceive);  //将我的收单界面放在QScrollArea3里
    pArea3->setGeometry(158,38,854,654);
    pArea3->setStyleSheet("background-color: rgba(255, 255, 255, 0)");
    Myreceive->setGeometry(0,0,850,650);
    pArea3->hide();    //设置myreceive位置
    Mysearch=new searchshow(this);
    Mysearch->setGeometry(159,39,852,652);
    Mysearch->hide();
    connect(this,SIGNAL(sendcanms(int)),Mysend,SLOT(receivesendcanms(int)));  //连接 使我发出订单时 mysend 会填上这个订单
    connect(this,SIGNAL(sendcanmsc(int,QString,QString,QString)),Mysend,SLOT(receivesendcanmsc(int,QString,QString,QString))); //我发出的订单被接收时传递接收者的信息
    connect(this,SIGNAL(cancel(int)),Mysend,SLOT(receivecancel(int)));  // 我的订单取消时 mysend 会除去这个订单
    connect(this,SIGNAL(sendcanmr(int)),Myreceive,SLOT(receivesendcanmr(int)));  //接受订单时   myreceive会添加这个订单
    connect(this,SIGNAL(yiwancheng(int)),Myreceive,SLOT(receiveyiwancheng(int)));   //完成订单是   myreceive相应订单产生变化
    connect(this,SIGNAL(sendcanmysearch(int)),Mysearch,SLOT(receivesendcanmysearch(int)));//
    connect(Mysend,SIGNAL(mysendok()),this,SLOT(remysendok()));  //发送的订单初始化完成
    connect(Myreceive,SIGNAL(myreceiveok()),this,SLOT(remyreceiveok()));  //接受的订单初始化完成
    connect(Mysearch,SIGNAL(connecttcp()),this,SLOT(reconnecttcp()));  //连接读取函数与服务器
    connect(Mysearch,SIGNAL(disconnecttcp()),this,SLOT(redisconnecttcp()));  //断开读取函数与服务器
    real=-1;  //设置real避免出错
    B=NULL;   //设置B 避免delete两次同一个指针
    ui->pushButton_5->setToolTip("修改资料");
    ui->pushButton_4->setToolTip("主页");
    }
}

Start::~Start()
{
    delete ui;
}

void Start::on_pushButton_clicked()  //我要发单
{
    this->hide();   //窗口隐藏
    Dialogzhuce * Dialogzhucedlg = new Dialogzhuce(this);  //建立发送窗口
    connect(Dialogzhucedlg,SIGNAL(showstart()),this,SLOT(receiveshowstart()));  //连接发送窗口和此窗口的显示函数
    Dialogzhucedlg->show();   //发送窗口显示
}

void Start::read_and_show()   //读取订单的函数
{
    QByteArray buffer=tcpClient->readAll();   //读取所有数据
    QString msg=QString(buffer);   //类型转换
    QString order=msg.section('/',1,1);   //获得添加或者删除
    if(order=="1")  //添加
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
        int cr=Cre.toInt();  //获取订单信息
    //获取订单的信息
        if((base->insertUsr(c,Id,Obj,From,To,Time,Mon,cr))==1) //数据库中插入该订单
        {
            real++;  //订单数加一
            bill** A=new bill*[real+1];
            for(int i=0;i<real;i++)
                A[i]=B[i];   //建立新的指针指向订单数加一后的新数组
            delete []B;     //释放原来的数组内存
            B=A;  //将新数组赋给我的指针
    //将指针内容扩充
            B[real]=new bill(ui->widget);  //建立新的订单窗口
            B[real]->receivesendcan(c,Id,Obj,From,To,Time,Mon,Cre);  //新订单窗口接受参数
            emit changeaddrplus();  //发送订单位置下降信号
            if((real+1)*260>650)
                ui->widget->resize(850,(real+1)*260+30);   //将显示重新设置尺寸
            B[real]->setGeometry(50,30,750,230);  //设置新订单窗口的位置大小
            connect(this,SIGNAL(changeaddrplus()),B[real],SLOT(receivechangeaddrplus()));  //连接此订单和位置变化的函数
            if(Id==Myuser->getid())  //判断此订单是否是我发的
            {
                B[real]->change();   //订单形态转换
                emit sendcanms(c);   //向我的发单发送信号添加该订单
            }
            B[real]->show();  //新订单显示
        }
    }
    //添加一个订单
    else if(order=="2")  //订单减少
    {
        QString owner=msg.section('/',2,2);  //获取所有人
        QString count=msg.section('/',3,3);  //获取订单编号
        QString recei=msg.section('/',4,4);  //获取订单接收人
        int c=count.toInt();
        emit sendcanmysearch(c);  //向我的搜索里减少该订单
        for(int i=0;i<=real;i++)
            if((B[i]->getcount())==c)  //如果主界面有改订单
            {
                if(real>2)
                    ui->widget->resize(850,real*260+10);  //重新设置主界面的尺寸
                else
                    ui->widget->resize(850,650);
                B[i]->close();  //该订单窗口关闭
                changeaddrless(i);  //所有订单向上
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
        if(owner!=Myuser->getid())  //如果不是我发的订单
        {
            if(recei==Myuser->getid())  //如果接收者是我
            {
                emit sendcanmr(c);   //我的接单里添加该订单
            }
        }
        else  //如果是我发的订单
        {
            if(recei=="") //如果没有人接 说明自己取消该订单
            {
                emit cancel(c);  //我的发单减少该订单
            }
            else //有人接
            {
                QString cr=msg.section('/',5,5);
                QString p=msg.section('/',6,6);
                emit sendcanmsc(c,recei,cr,p);  //我的发单中该订单添加接收者信息 并变化形式
            }
        }
    }
    else  //如果是某人完成订单
    {
        QString count=msg.section('/',2,2);
        QString id=msg.section("/",3,3);
        QString id2=msg.section("/",4,4);
        int c=count.toInt();
        if(id==Myuser->getid())  //如果是我的订单被完成
        {
            emit cancel(c);  //我的发单中该订单消失
        }
        else
        {
            if(id2==Myuser->getid())   //如果接受者是我
                emit yiwancheng(c);   //我的收单减少该订单
        }
    }
}
    //减少一个订单

void Start::receiveshowstart()
{
    this->show();
}

void Start::receiveshowstarttcp()//重新显示该界面并连接读取函数和服务器
{
    this->show();
    connect(tcpClient,SIGNAL(readyRead()),this,SLOT(read_and_show()));
}

void Start::on_pushButton_2_clicked()
{
    pArea1->hide();
    pArea3->hide();
    pArea2->show();
    Mysearch->hide();
}

void Start::on_pushButton_3_clicked()
{
    pArea1->hide();
    pArea2->hide();
    pArea3->show();
    Mysearch->hide();
}

void Start::on_pushButton_4_clicked()
{
    pArea1->show();
    pArea2->hide();
    pArea3->hide();
    Mysearch->hide();
}

void Start::on_searchButton_clicked()
{
    pArea1->hide();
    pArea2->hide();
    pArea3->hide();
    Mysearch->show();
}

void Start::changeaddrless(int c)//所有订单位置上升
{
    for(int i=0;i<c;i++)
        B[i]->receivechangeaddrless();
}

void Start::on_pushButton_5_clicked()//修改界面显示
{
    this->hide();
    disconnect(tcpClient,SIGNAL(readyRead()),this,SLOT(read_and_show()));
    Revise* Revisedlg = new Revise(this);
    connect(Revisedlg,SIGNAL(showstart()),this,SLOT(receiveshowstarttcp()));
    Revisedlg->show();
}

void Start::remysendok()//我的发单初始化成功
{
    disconnect(tcpClient,SIGNAL(readyRead()),Mysend,SLOT(readinitialms()));
    connect(tcpClient,SIGNAL(readyRead()),Myreceive,SLOT(readinitialmr()));
    int *cid=MainWindow::getCid();
    QString id=Myuser->getid();
    QString mycid=QString::number(*cid);
    QString order="/havelogged2/"+mycid+"/"+id;
    tcpClient->write(order.toUtf8());
}

void Start::remyreceiveok()//我的收单初始化完成
{
    disconnect(tcpClient,SIGNAL(readyRead()),Myreceive,SLOT(readinitialmr()));
    connect(tcpClient,SIGNAL(readyRead()),this,SLOT(read_and_show()));
    int *cid=MainWindow::getCid();
    QString id=Myuser->getid();
    QString mycid=QString::number(*cid);
    QString order="/havelogged3/"+mycid+"/"+id;
    tcpClient->write(order.toUtf8());
}

void Start::reconnecttcp()
{
    connect(tcpClient,SIGNAL(readyRead()),this,SLOT(read_and_show()));
}

void Start::redisconnecttcp()
{
    disconnect(tcpClient,SIGNAL(readyRead()),this,SLOT(read_and_show()));
}
