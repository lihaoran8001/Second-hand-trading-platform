#ifndef BILL_H
#define BILL_H

#include <QWidget>
#include <QTcpSocket>
#include<QPushButton>
#include "myuser.h"

namespace Ui {
class bill;
}

class bill : public QWidget
{
    Q_OBJECT

public:
    explicit bill(QWidget *parent = 0);
    ~bill();
    int getcount();  //返回订单的编
    void receivechangeaddrless();   //所有订单位置向上升
    void change();  //自己发的订单时订单变换
    void change2();  //接受别人的订单后订单变化
    void change3();   //自己的订单被别人接收后订单的变化
    void receivesendcan(int, QString, QString, QString, QString, QString, QString, QString);   //接收参数
    void setreceivei(QString);   //设置接单人的id
    void setreceivec(QString);   //设置接单人的信用值
    void setreceivep(QString);   //设置接单人的电话号码
private slots:
    void receivechangeaddrplus();   //订单位置下降
    void on_pushButton_2_clicked();   //接订单时
    void cancelbill();     //取消订单时
    void wancheng(int);    //完成订单时
    void jiedanyuan();     //接单员信息显示
    void pingfen();        //给接单员评分
signals:
    void sendpingfen();  //发送建立评分界面信号
    void clicked();
    void showwait(QString,QString,QString);  //发送建立接单员详细信息展示界面
private:
    Ui::bill *ui;
    int count;
    QTcpSocket* tcpclient;
    QString receiveri;
    QString receiverc;
    QString receiverp;
    int* cid;
    myuser* Myuser;
};

#endif // BILL_H
