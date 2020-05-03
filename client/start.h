#ifndef START_H
#define START_H

#include <QMainWindow>
#include <QTcpSocket>
#include "bill.h"
#include "database.h"
#include "mysend.h"
#include "myreceive.h"
#include "searchshow.h"
#include "billchange.h"
#include "myuser.h"

namespace Ui {
class Start;
}

class Start : public QMainWindow
{
    Q_OBJECT

public:
    explicit Start(QWidget *parent = 0);
    ~Start();
    void changeaddrless(int);

private slots:
    void on_pushButton_clicked();  //我要发单按钮点击
    void read_and_show();    //读取订单信息
    void reconnecttcp();     //重新连接read_and_show()和readyread
    void redisconnecttcp();  //断开两者连接
    void remysendok();      //我的发送初始化完成
    void remyreceiveok();   //我的接单初始化完成
    void on_pushButton_2_clicked();   //我的发单按钮点击
    void on_pushButton_3_clicked();   //我的接单按钮点击
    void on_pushButton_4_clicked();   //主界面按钮点击
    void on_pushButton_5_clicked();   //修改资料界面按钮点击
    void on_searchButton_clicked();   //搜索界面按钮点击
    void receiveshowstart();    //显示主界面
    void receiveshowstarttcp();   //显示主界面并连接服务器

signals:
    void changeaddrplus();    //所有订单下降
    void sendcanms(int);      //向我的发单界面发送订单编号
    void sendcanmr(int);       //向我的接单界面发送订单编号
    void sendcanmysearch(int);     //向搜索界面发送订单编号
    void sendcanmsc(int,QString,QString,QString);   //向我的发单界面发送有人接单的订单的编号
    void cancel(int);    //向我的发单界面发送要消失的订单编号
    void yiwancheng(int);   //向我的收单界面发送要消失的订单的编号
private:
    Ui::Start *ui;
    QTcpSocket* tcpClient;
    DataBase* base;
    bill** B;
    mysend* Mysend;
    myreceive* Myreceive;
    searchshow* Mysearch;
    int real;
    myuser* Myuser;
    QScrollArea *pArea1;
    QScrollArea *pArea2;
    QScrollArea *pArea3;
};

#endif // START_H
