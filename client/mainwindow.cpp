#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "start.h"
#include <QMessageBox>


QTcpSocket* MainWindow::getSocketadd()
{
      static QTcpSocket Tcpclient;
      return &Tcpclient;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->MilineEdit->setEchoMode(QLineEdit::Password);
    tcpClient=getSocketadd();
    cid=getCid();
    tcpClient->abort();
    tcpClient->connectToHost("223.3.102.212", 8000);
    if(!tcpClient->waitForConnected(1000))
    {
        QMessageBox::information(this, "提示", "网络未连接！", QMessageBox::Ok);
        this->close();
    }
    connect(tcpClient, SIGNAL(readyRead()), this, SLOT(Read()));
    QString data="new";
    tcpClient->write(data.toUtf8());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ZhuButton_clicked()
{
    disconnect(tcpClient, SIGNAL(readyRead()), this, SLOT(Read()));
    this->hide();
    Dialog * Dialogdlg = new Dialog(this);
    connect(Dialogdlg,SIGNAL(showmainwindow()),this,SLOT(receiveshowmainwindow()));
    Dialogdlg->show();
}


void MainWindow::on_DengButton_clicked()
{
        QString header ="login";  //toPlainText（） 获取文本的意思
        QString Id=ui->ZhanglineEdit->text();
        QString PassWord=ui->MilineEdit->text();
        QString cidstr=QString::number(*cid);
        QString message="/"+header+"/"+Id+"/"+PassWord+"/"+cidstr;
        tcpClient->write(message.toUtf8());
}

void MainWindow::Read()
{
   QByteArray buff=tcpClient->readAll();
   QString data;
   data.prepend(buff);
   QString header=data.section('/',1,1);
   if(header=="new")
   {
       QString buffer=data.section('/',2,2);
       *cid=buffer.toInt();
       tcpClient->write(buffer.toUtf8());
   }
   if(header=="dlcg")
   {
       QString i=data.section('/',2,2);
       QString c=data.section('/',3,3);
       QString p=data.section('/',4,4);
       Myuser=myuser::getuser(i,c,p);
       disconnect(tcpClient,SIGNAL(readyRead()),this,SLOT(Read()));
       this->close();
       Start * Startdlg = new Start;
       Startdlg->show();
   }
   if(header=="mimacuowu")
   {
       QMessageBox::information(this, "提示", "密码输入错误！", QMessageBox::Ok);
   }
   if(header=="zhanghaocuowu")
   {
       QMessageBox::information(this, "提示", "账号输入错误！", QMessageBox::Ok);
   }
}

 void MainWindow::receiveshowmainwindow()
 {
     this->show();
     connect(tcpClient, SIGNAL(readyRead()), this, SLOT(Read()));
 }

 int *MainWindow::getCid()
 {
     static int cid;
     return &cid;
 }











