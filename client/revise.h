#ifndef REVISE_H
#define REVISE_H

#include <QDialog>
#include "mainwindow.h"
#include "myuser.h"

namespace Ui {
class Revise;
}

class Revise : public QDialog
{
    Q_OBJECT

public:
    explicit Revise(QWidget *parent = 0);
    ~Revise();
    void iscanclicked();

private slots:
    void on_confirmButton_clicked();//确定按钮点击

    void on_cancelButton_clicked();//取消按钮点击

    void on_lineEdit_editingFinished();//密码栏输入完成

    void on_lineEdit_4_editingFinished();//电话号码栏输入完成

    void on_lineEdit_2_editingFinished();//新密码栏输入完成

    void on_lineEdit_3_editingFinished();//确定新密码输入完成

    void read();//接收修改是否成功

signals:
    void showstart();

private:
    Ui::Revise *ui;
    QTcpSocket* Tcpclient;
    myuser* Myuser;
    int* cid;
    int com[4];
};

#endif // REVISE_H
