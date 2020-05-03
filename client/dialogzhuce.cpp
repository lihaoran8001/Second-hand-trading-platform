#include "dialogzhuce.h"
#include "ui_dialogzhuce.h"
#include "wait.h"
#include "mainwindow.h"
#include "start.h"
#include <QMessageBox>
Dialogzhuce::Dialogzhuce(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialogzhuce)
{
    ui->setupUi(this);
    tcpClient=MainWindow::getSocketadd();
    cid=MainWindow::getCid();
    Myuser=myuser::getuser();
}

Dialogzhuce::~Dialogzhuce()
{
    delete ui;
}

bool Dialogzhuce::iscorrectinput()
{
    if(ui->lineEdit->text().isEmpty())
    {
        QMessageBox::information(this, "提示", "起始地址不能为空", QMessageBox::Ok);
        return false;
    }
    if(ui->lineEdit_2->text().isEmpty())
    {
        QMessageBox::information(this, "提示", "终止地址不能为空", QMessageBox::Ok);
        return false;
    }
    if(ui->lineEdit_3->text().isEmpty())
    {
        QMessageBox::information(this, "提示", "物品描述不能为空", QMessageBox::Ok);
        return false;
    }
    if(ui->lineEdit_8->text().isEmpty())
    {
        QMessageBox::information(this, "提示", "联系方式不能为空", QMessageBox::Ok);
        return false;
    }
    else
        return true;
}

void Dialogzhuce::on_pushButton_2_clicked()
{
    /*if(iscorrectinput())
    {*/
    QString yh;
    QString Cid=QString::number(*cid);
    QString header="orders";
    QString From=ui->lineEdit->text();
    QString To=ui->lineEdit_2->text();
    QString Obj=ui->lineEdit_3->text();
    QString Time=ui->lineEdit_4->text();
    QString Mon=ui->lineEdit_8->text();
    yh="/"+header+"/"+Cid+"/"+Myuser->getid()+"/"+Obj+"/"+From+"/"+To+"/"+Time+"/"+Mon;
    tcpClient->write(yh.toUtf8());
    this->close();
    emit showstart();
    //}
}

void Dialogzhuce::on_pushButton_clicked()
{
    this->close();
    emit showstart();
}

