#include "revise.h"
#include "ui_revise.h"
#include "start.h"
Revise::Revise(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Revise)
{
    ui->setupUi(this);
    Tcpclient=MainWindow::getSocketadd();
    connect(Tcpclient,SIGNAL(readyRead()),this,SLOT(read()));
    Myuser=myuser::getuser();
    cid=MainWindow::getCid();
    for(int i=0;i<3;i++)
        com[i]=0;//初始正确输入的文本框状态
    com[3]=1;
    ui->lineEdit_4->setText(Myuser->getpho());
    ui->confirmButton->setEnabled(false);
    ui->lineEdit->setEchoMode(QLineEdit::Password);
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    ui->lineEdit_3->setEchoMode(QLineEdit::Password);
    /*//按钮控件圆角化
    ui->pushButton->setIconSize(QSize(60, 60));
    // 通过样式去除边框;
    ui->pushButton->setStyleSheet("border:none;background-color:gray;border-radius:25px;");*/
}

Revise::~Revise()
{
    delete ui;
}

void Revise::on_confirmButton_clicked()
{
    int c=*cid;
    QString ci=QString::number(c);
    QString i=Myuser->getid();
    QString oldpass=ui->lineEdit->text();
    QString pass=ui->lineEdit_2->text();
    QString phone=ui->lineEdit_4->text();
    QString buffer="/xiugaiziliao/"+ci+"/"+i+"/"+oldpass+"/"+pass+"/"+phone;
    Tcpclient->write(buffer.toUtf8());
}

void Revise::read()
{
    QByteArray buffer=Tcpclient->readAll();
    if(QString(buffer)=="xiugaichenggong")
    {
         QMessageBox::information(this, "提示", "修改成功！", QMessageBox::Ok);
         disconnect(Tcpclient, SIGNAL(readyRead()), this, SLOT(read()));
         this->close();
         emit showstart();
    }
    else if(QString(buffer)=="mimacuowu")
    {
        QMessageBox::information(this, "提示", "密码错误！", QMessageBox::Ok);
    }
}


void Revise::on_cancelButton_clicked()
{
    this->close();
    disconnect(Tcpclient,SIGNAL(readyRead()),this,SLOT(read()));
    emit showstart();
}

void Revise::on_lineEdit_editingFinished()
{
    QString str=ui->lineEdit->text();
    int i=str.length();
    if(i<16&&i>4)
    {
        int j=0;
        for(;j<i-1;j++)
        {
            if(!((str[j]>64&&str[j]<91)||(str[j]>96&&str[j]<123)||(str[j]>47&&str[j]<58)))
            {
                ui->label_6->setText("密码含有不规范字符");
                ui->label_6->setStyleSheet("color:#00ff00;");
                break;
            }
        }
        if(j==i-1)
        {
            ui->label_6->setText("√");
            ui->label_6->setStyleSheet("color:#00ff00;");
            com[0]=1;
        }
    }
    else
    {
        ui->label_6->setText("密码长度不符");
        ui->label_6->setStyleSheet("color:#ff0000;");
        com[0]=0;
    }
    iscanclicked();
}

void Revise::on_lineEdit_4_editingFinished()
{
    QString  str=ui->lineEdit_4->text();
    int i=str.length();
    if(i==11)
    {
        int j=0;
        for(;j<i-1;j++)
        {
            if(str[j]>57||str[j]<48)
            {
                ui->label_9->setText("号码输入不规范");
                ui->label_9->setStyleSheet("color:#ff0000;");
                break;
            }
        }
        if(j==i-1)
        {
            ui->label_9->setText("√");
            ui->label_9->setStyleSheet("color:#00ff00;");
            com[3]=1;
        }
    }
    else
    {
        ui->label_9->setText("号码长度不符");
        ui->label_9->setStyleSheet("color:#ff0000;");
        com[3]=0;
    }
    iscanclicked();
}

void Revise::on_lineEdit_2_editingFinished()
{
    QString str=ui->lineEdit_2->text();
    int i=str.length();
    if(i<16&&i>4)
    {
        int j=0;
        for(;j<i-1;j++)
        {
            if(!((str[j]>64&&str[j]<91)||(str[j]>96&&str[j]<123)||(str[j]>47&&str[j]<58)))
            {
                ui->label_7->setText("密码含有不规范字符");
                ui->label_7->setStyleSheet("color:#00ff00;");
                break;
            }
        }
        if(j==i-1)
        {
            ui->label_7->setText("√");
            ui->label_7->setStyleSheet("color:#00ff00;");
            com[1]=1;
            if(ui->lineEdit_2->text()==ui->lineEdit_3->text())
            {
                ui->label_8->setText("√");
                ui->label_8->setStyleSheet("color:#00ff00;");
                com[2]=1;
            }
        }
    }
    else
    {
        ui->label_7->setText("密码长度不符");
        ui->label_7->setStyleSheet("color:#ff0000;");
        com[1]=0;
    }
    iscanclicked();
}

void Revise::on_lineEdit_3_editingFinished()
{
    if(ui->lineEdit_3->text()==ui->lineEdit_2->text())
    {
        ui->label_8->setText("√");
        ui->label_8->setStyleSheet("color:#00ff00;");
        com[2]=1;
    }
    else
    {
        ui->label_8->setText("两次密码输入不同");
        ui->label_8->setStyleSheet("color:#ff0000;");
        com[2]=0;
    }
    iscanclicked();
}

void Revise::iscanclicked()
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
        ui->confirmButton->setEnabled(true);
    else
        ui->confirmButton->setEnabled(false);
}
