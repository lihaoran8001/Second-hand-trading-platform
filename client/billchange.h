#ifndef BILLCHANGE_H
#define BILLCHANGE_H

#include <QWidget>
#include<QTcpSocket>

namespace Ui {
class billchange;
}

class billchange : public QWidget
{
    Q_OBJECT

public:
    explicit billchange(QWidget *parent = 0);
    ~billchange();
    int getcount();

private slots:
    void receivechangeaddrplus();
    void receivechangeaddrless();
    void receivesendcan(int,QString, QString, QString, QString, QString,QString,QString);
    void received();
    void on_pushButton_clicked();

private:
    Ui::billchange *ui;
    int count;
    QTcpSocket* tcpClient;
};

#endif // BILLCHANGE_H
