#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QTcpSocket>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_pushButton_clicked();//取消按钮点击
    void on_pushButton_2_clicked();//确定按钮点击
    void read();//读取服务器的信息
    void iscanclicked();//确定按钮是否被点击
    void on_lineEdit_9_editingFinished();//两次密码输入是否相同
    void on_lineEdit_10_editingFinished();//密码输入是否正确
    void on_lineEdit_6_editingFinished();//账号输入是否正确
    void on_lineEdit_11_editingFinished();//电话号码是否正规

signals:
    void sendsignal();
    void showmainwindow();//登陆界面显示

private:
    Ui::Dialog *ui;
    QTcpSocket* tcpClient;
    int com[4];
    int* cid;
};

#endif // DIALOG_H

