#ifndef DIALOGZHUCE_H
#define DIALOGZHUCE_H

#include <QDialog>
#include<QTcpSocket>
#include "myuser.h"

namespace Ui {
class Dialogzhuce;
}

class Dialogzhuce : public QDialog
{
    Q_OBJECT

public:
    explicit Dialogzhuce(QWidget *parent = 0);
    ~Dialogzhuce();

    bool iscorrectinput();//订单是否输入正确

private slots:
    void on_pushButton_2_clicked();//确定按钮被点击
    void on_pushButton_clicked();//取消按钮被点击

private:
    Ui::Dialogzhuce *ui;
    QTcpSocket* tcpClient;
    int* cid;
    myuser* Myuser;

signals:
    void showstart();
};

#endif // DIALOGZHUCE_H
