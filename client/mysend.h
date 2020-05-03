#ifndef MYSEND_H
#define MYSEND_H

#include <QWidget>
#include "database.h"
#include "bill.h"
#include "mainwindow.h"

namespace Ui {
class mysend;
}

class mysend : public QWidget
{
    Q_OBJECT

public:
    explicit mysend(QWidget *parent = 0);
    ~mysend();
    void changeaddrless(int);

private slots:
    void receivesendcanms(int);//接收我的发送订单添加编号
    void receivesendcanmsc(int,QString,QString,QString);//被接受的订单接单人数据设置
    void receivecancel(int);//我的订单取消
    void receiveshowwait(QString,QString,QString);//显示订单接单人窗口
    void readinitialms();//我的发单初始化
signals:
    void sendcan(int,QString,QString,QString,QString,QString,QString,QString);//向订单传输数据
    void changeaddrplusms();//订单位置下降
    void change();//
    void mysendok();//我的发单初始化完成
private:
    Ui::mysend *ui;
    DataBase* base;
    QTcpSocket* Tcpclient;
    bill** B;
    myuser* Myuser;
    int real;
};

#endif // MYSEND_H
