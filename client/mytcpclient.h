#ifndef MYTCPCLIENT_H
#define MYTCPCLIENT_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>


class MyTcpClient
{
    Q_OBJECT

public:
    explicit MyTcpClient();
    ~MyTcpClient();

private:
    QTcpSocket *tcpClient;

private slots:
    //客户端槽函数
    void ReadData();
    void ReadError(QAbstractSocket::SocketError);

    void on_btnConnect_clicked();
    void on_btnSend_clicked();
    void on_pushButton_clicked();
};

#endif // MYTCPCLIENT_H
