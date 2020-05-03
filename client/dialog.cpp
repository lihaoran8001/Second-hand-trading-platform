#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    for(int i=0;i<4;i++)
        com[i]=0;//初始正确输入的文本框状态
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,1);
    tcpClient=MainWindow::getSocketadd();//建立与服务器连接
    cid=MainWindow::getCid(); //获取Cid
    connect(tcpClient, SIGNAL(readyRead()), this, SLOT(read()));//初始读数据函数为发送注册请求
    ui->pushButton_2->setEnabled(false);//无法点击确定
    ui->lineEdit_9->setEchoMode(QLineEdit::Password);//密码设置为黑点
    ui->lineEdit_10->setEchoMode(QLineEdit::Password);//密码设置为黑点
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    this->close();
    emit showmainwindow();
}

void Dialog::on_pushButton_2_clicked()
{
    QString header ="register";  //toPlainText（） 获取文本的意思
    QString Id=ui->lineEdit_6->text();
    QString PassWord=ui->lineEdit_10->text();
    QString Phone=ui->lineEdit_11->text();
    int* cid=MainWindow::getCid();  //获取ID
    QString cidstr=QString::number(*cid);
    QString message;
    message ="/"+header+"/"+Id+"/"+PassWord+"/"+Phone+"/"+cidstr;
    tcpClient->write(message.toUtf8());  //将字符串发给服务器
}

void Dialog::read()
{
    QByteArray buffer=tcpClient->readAll();
    if(QString(buffer)=="zhucechenggong")
    {
         QMessageBox::information(this, "提示", "注册成功！", QMessageBox::Ok);
          this->close();  //注册窗口关闭
          emit showmainwindow();  //发送信号登陆界面出现
         disconnect(tcpClient, SIGNAL(readyRead()), this, SLOT(read()));   //断开服务器readyread与此界面的read
    }
    if(QString(buffer)=="zhanghaobeishiyong")
    {
        QMessageBox::information(this, "提示", "账号已经被使用！", QMessageBox::Ok);
    }
    if(QString(buffer)=="zhuceshibai")
    {
        QMessageBox::information(this, "提示", "服务器端注册失败！", QMessageBox::Ok);
    }
}




void Dialog::on_lineEdit_9_editingFinished() //确认密码两次输入相同
{
    if(ui->lineEdit_9->text()==ui->lineEdit_10->text())
    {
        ui->Comlabel->setText("√");//后面的label设为√
        ui->Comlabel->setStyleSheet("color:#00ff00;");//设置颜色
        com[2]=1;
    }
    else
    {
        ui->Comlabel->setText("两次密码输入不同");//提示出错原因
        ui->Comlabel->setStyleSheet("color:#ff0000;");//设置颜色
        com[2]=0;
    }
    iscanclicked();
}

void Dialog::on_lineEdit_10_editingFinished()
{
    QString str=ui->lineEdit_10->text();
    int i=str.length();
    if(i<16&&i>4)
    {
        int j=0;
        for(;j<i-1;j++)
        {
            if(!((str[j]>64&&str[j]<91)||(str[j]>96&&str[j]<123)||(str[j]>47&&str[j]<58)))
            {
                ui->Passlabel->setText("密码含有不规范字符");
                ui->Passlabel->setStyleSheet("color:#00ff00;");
                break;
            }
        }
        if(j==i-1)
        {
            ui->Passlabel->setText("√");
            ui->Passlabel->setStyleSheet("color:#00ff00;");
            com[1]=1;
            if(ui->lineEdit_9->text()==ui->lineEdit_10->text())
            {
                ui->Comlabel->setText("√");
                ui->Comlabel->setStyleSheet("color:#00ff00;");
                com[2]=1;
            }
        }
    }
    else
    {
        ui->Passlabel->setText("密码长度不符");
        ui->Passlabel->setStyleSheet("color:#ff0000;");
        com[1]=0;
    }
    iscanclicked();
}

void Dialog::on_lineEdit_6_editingFinished()
{
    QString  str=ui->lineEdit_6->text();
    int i=str.length();
    if(i<16&&i>4)
    {
        int j=0;
        for(;j<i-1;j++)
        {
            if(!((str[j]>64&&str[j]<91)||(str[j]>96&&str[j]<123)||(str[j]>47&&str[j]<58)))
            {
                ui->Idlabel->setText("账号含有不规范字符");
                ui->Idlabel->setStyleSheet("color:#ff0000;");
                break;
            }
        }
        if(j==i-1)
        {
            ui->Idlabel->setText("√");
            ui->Idlabel->setStyleSheet("color:#00ff00;");
            com[0]=1;
        }
    }
    else
    {
        ui->Idlabel->setText("账号长度不符");
        ui->Idlabel->setStyleSheet("color:#ff0000;");
        com[0]=0;
    }
    iscanclicked();
}

void Dialog::on_lineEdit_11_editingFinished()
{
    QString  str=ui->lineEdit_11->text();
    int i=str.length();
    if(i==11)
    {
        int j=0;
        for(;j<i-1;j++)
        {
            if(str[j]>57||str[j]<48)
            {
                ui->Phonelabel->setText("号码输入不规范");
                ui->Phonelabel->setStyleSheet("color:#ff0000;");
                break;
            }
        }
        if(j==i-1)
        {
            ui->Phonelabel->setText("√");
            ui->Phonelabel->setStyleSheet("color:#00ff00;");
            com[3]=1;
        }
    }
    else
    {
        ui->Phonelabel->setText("号码长度不符");
        ui->Phonelabel->setStyleSheet("color:#ff0000;");
        com[3]=0;
    }
    iscanclicked();
}

void Dialog::iscanclicked()
{
    int x=1;
    for(int i=0;i<4;i++)
    {
        if(com[i]==0)
        {
            x=0;
            break;
        }
    }
    if(x==1)
        ui->pushButton_2->setEnabled(true);
    else
        ui->pushButton_2->setEnabled(false);
}
