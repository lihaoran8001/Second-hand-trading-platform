#ifndef MYRECEIVE_H
#define MYRECEIVE_H

#include <QWidget>
#include "database.h"
#include "bill.h"
#include "mainwindow.h"

namespace Ui {
class myreceive;
}

class myreceive : public QWidget
{
    Q_OBJECT

public:
    explicit myreceive(QWidget *parent = 0);
    ~myreceive();
    void changeaddrless(int);

private slots:
    void receivesendcanmr(int);//接收我的接收添加
    void receiveyiwancheng(int);//接受已完成信号
    void readinitialmr();//接收我的接收初始化
signals:
    void sendcan(int,QString,QString,QString,QString,QString,QString,QString);//向订单传输数据
    void changeaddrplusmr();//订单位置下降
    void myreceiveok();//我的接受初始化结束
private:
    Ui::myreceive *ui;
    DataBase* base;
    QTcpSocket* Tcpclient;
    myuser* Myuser;
    int real;
    bill** B;
};

#endif // MYRECEIVE_H
