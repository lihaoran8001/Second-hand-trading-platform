#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include "myuser.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    static QTcpSocket* getSocketadd();
    ~MainWindow();
    static int* getCid();
   // myuser* getu();
private slots:
    void on_ZhuButton_clicked();//注册按钮被点击
    void on_DengButton_clicked();//注册按钮被点击
    void Read();//读取服务器数据
    void receiveshowmainwindow();//接收登陆界面显示
signals:
    senduser(QString,QString);
private:
    Ui::MainWindow *ui;
    QTcpSocket* tcpClient;
    int* cid;
    myuser* Myuser;
};



#endif // MAINWINDOW_H
