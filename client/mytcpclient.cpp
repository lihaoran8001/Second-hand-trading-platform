#include "mytcpclient.h"

MyTcpClient::MyTcpClient
{

    //初始化TCP客户端
    tcpClient = new QTcpSocket(this);   //实例化tcpClient(QTcpSocket类型的变量）
    tcpClient->abort();                 //取消原有连接（？？？它的原有连接连向哪里）
    ui->btnConnect->setEnabled(true);   //setEnabled（）推测能否被点击
    ui->btnSend->setEnabled(false);

    connect(tcpClient, SIGNAL(readyRead()), this, SLOT(ReadData()));  //连接槽函数和信号函数
    connect(tcpClient, SIGNAL(error(QAbstractSocket::SocketError)), \
            this, SLOT(ReadError(QAbstractSocket::SocketError)));
}

MyTcpClient::~MyTcpClient()
{
    delete ui;
}

void MyTcpClient::ReadData()
{
    QByteArray buffer = tcpClient->readAll();    //QByteArray （是一种字符数组的类型）
    if(!buffer.isEmpty())
    {
        ui->edtRecv->append(buffer);   //edtRecv  （整个消息框）   append（扩展自己的内存存储括号内的内容)
    }
}

void MyTcpClient::ReadError(QAbstractSocket::SocketError)
{
    tcpClient->disconnectFromHost();   //disconnectFromHost()  (未连接服务器）
    ui->btnConnect->setText(tr("连接"));   //tr()   (可以将收到的变量进性翻译）
    QMessageBox msgBox;
    msgBox.setText(tr("failed to connect server because %1").arg(tcpClient->errorString()));
    msgBox.exec();
}

void MyTcpClient::on_btnConnect_clicked()   //connect
{
    if(ui->btnConnect->text()=="连接")
    {
        tcpClient->connectToHost(ui->edtIP->text(), ui->edtPort->text().toInt());   //toint()  （将字符转换成int型）
        if (tcpClient->waitForConnected(1000))  // 连接成功则进入if{}
        {
            ui->btnConnect->setText("断开");
            ui->btnSend->setEnabled(true);
        }
    }
    else
    {
        tcpClient->disconnectFromHost();
        if (tcpClient->state() == QAbstractSocket::UnconnectedState \
                || tcpClient->waitForDisconnected(1000))  //已断开连接则进入if{}
        {
            ui->btnConnect->setText("连接");
            ui->btnSend->setEnabled(false);
        }
    }
}

void MyTcpClient::on_btnSend_clicked()
{
    QString data = ui->edtSend->toPlainText();  //toPlainText（） 获取文本的意思
    if(data != "")
    {
        tcpClient->write(data.toUtf8()); //qt5出去了.toAscii()
    }
}

void MyTcpClient::on_pushButton_clicked()
{
    ui->edtRecv->clear();    //清除内存的意思
}
