#include "bill.h"
#include "ui_bill.h"
#include "mainwindow.h"
#include "wait.h"
#include "start.h"
#include "haoping.h"

bill::bill(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::bill)
{
    ui->setupUi(this);
    tcpclient=MainWindow::getSocketadd();
    Myuser=myuser::getuser();
    cid=MainWindow::getCid();
    ui->pushButton_3->hide();  //隐藏接单员按钮
    ui->label_15->hide();
    ui->label_16->hide();       //隐藏接单员按钮相关的图层
}

bill::~bill()
{
    delete ui;
}

void bill::receivechangeaddrplus()
{
    this->setGeometry(this->x(),this->y()+260,750,230);
}

void bill::receivechangeaddrless()
{
    this->setGeometry(this->x(),this->y()-260,750,230);
}

void bill::receivesendcan(int c, QString i, QString o, QString f, QString t, QString ti, QString m,QString b)
{
    count=c;
    ui->label->setText(f);
    ui->label_2->setText(t);
    ui->label_3->setText(ti);
    ui->label_4->setText(m);
    ui->label_5->setText(o);
    ui->label_6->setText(i);
    ui->label_7->setText(b);
}

int bill::getcount()
{
    return count;
}

void bill::on_pushButton_2_clicked()
{
    QString ci=QString::number(*cid);
    QString str=QString::number(count);
    QString reid=Myuser->getid();
    QString buf="/woyaojiedan/"+ci+"/"+str+"/"+reid;
    tcpclient->write(buf.toUtf8());   //向服务器发送此订单的编号和自己的id
}

void bill::change()
{
    disconnect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(on_pushButton_2_clicked())); //断开此按钮原有连接
    ui->pushButton_2->setText("取消");    //改变此按钮的文本
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(cancelbill()));   //将此按钮建立新连接
}

void bill::change2()
{
    delete ui->pushButton_2;
    delete ui->label_13;
    delete ui->label_14;   //释放原按钮及其相关图层
    QLabel* sending= new QLabel(this);
    sending->setText("已接单");
    sending->setGeometry(590,190,93,28);
    sending->show();
}

void bill::change3()
{
    disconnect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(cancelbill()));
    ui->pushButton_2->setText("完成");
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(jiedanyuan()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(pingfen()));
    ui->pushButton_3->show();
    ui->label_15->show();
    ui->label_16->show();
}

void bill::cancelbill()
{
    QString str=QString::number(count);
    QString c=QString::number(*cid);
    QString buf="/woyaoquxiao/"+c+'/'+str;
    tcpclient->write(buf.toUtf8());
}

void bill::jiedanyuan()
{
    emit showwait(receiveri,receiverc,receiverp);
}

void bill::wancheng(int score)
{
    QString str=QString::number(count);
    QString c=QString::number(*cid);
    QString mysc=QString::number(score);
    QString buf="/yiwancheng/"+c+"/"+str+"/"+mysc;
    tcpclient->write(buf.toUtf8());
}

void bill::setreceivei(QString re)
{
    receiveri=re;
}

void bill::setreceivec(QString re)
{
    receiverc=re;
}

void bill::setreceivep(QString re)
{
    receiverp=re;
}

void bill::pingfen()
{
    haoping* myhp=new haoping;
    connect(myhp,SIGNAL(sendscore(int)),this,SLOT(wancheng(int)));
    myhp->show();
}
