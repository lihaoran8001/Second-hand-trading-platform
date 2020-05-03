#ifndef SEARCHSHOW_H
#define SEARCHSHOW_H

#include <QScrollArea>
#include <QTcpSocket>
#include "bill.h"
#include "database.h"
#include "myuser.h"

namespace Ui {
class searchshow;
}

class searchshow : public QScrollArea
{
    Q_OBJECT

public:
    explicit searchshow(QWidget *parent = 0);
    ~searchshow();
    void clear();  //清空searchshow的内存
    void changeaddrless(int);   //所有订单向下移动
    void setcolor();   //设置整个界面颜色

private slots:
    void readsearch();   //读取搜索结果
    void on_searchButton_clicked();    //搜索按钮点击
    void receivesendcanmysearch(int);    //向该界面发送消失订单的编号

signals:
    void changeaddrplus();//订单位置向下
    void connecttcp();//主界面连接服务器
    void disconnecttcp();//主界面断开与服务器连接

private:
    Ui::searchshow *ui;
    QTcpSocket* Tcpclient;
    bill** B;
    DataBase* base;
    myuser* Myuser;
    int real;
    int* cid;
};

#endif // SEARCHSHOW_H
