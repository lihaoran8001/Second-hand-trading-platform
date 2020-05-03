#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTimer>

#include "server.h"
#include"database.h"
#include"database2.h"
namespace Ui {
class Dialog;
}

class Server;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    void Read_And_Check(QString,QString,QString);//读取账户数据并判断正确性
    void Store_User_Info(QString,QString,QString,QString);//存储客户用于注册的信息
    void Read_Check_Revise(QString,QString,QString,QString,QString);//读取数据，并检查账号密码一致性，并对密码进行修改
    void Read_And_Delete(QString,QString,QString);//读取数据，并检查账号密码一致性，并进行账户注销
    void Handle_the_orders(QString,QString,QString,QString,QString,QString);//用户发单
    void Received_orders(QString,QString); //用户接受订单
    void Cancel_orders(QString);//用户取消订单
    void Finish_orders(QString,QString);//订单已完成
    void Renew_orders(QString,QString);//恢复订单数据
    void Renew_orders2(QString,QString);//恢复订单数据2
    void Renew_order3(QString);
    void searchfun(QString,QString,QString);//回应搜索

signals:
    void sendData(QByteArray data, int id);

public slots:
    void revData(QString peerHost, QByteArray data);

private slots:
    void showConnection();
    void showDisconnection(int socketDescriptor);
    void clearMsg();
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Dialog *ui;

    int count;

    Server *server;

    int ordercount;
};

#endif // DIALOG_H
