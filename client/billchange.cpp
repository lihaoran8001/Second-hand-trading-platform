#include "billchange.h"
#include "ui_billchange.h"
#include "mainwindow.h"

billchange::billchange(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::billchange)
{
    ui->setupUi(this);
    tcpClient=MainWindow::getSocketadd();
}

billchange::~billchange()
{
    delete ui;
}

void billchange::receivechangeaddrplus()
{
    this->setGeometry(this->x(),this->y()+260,750,230);
}

void billchange::receivechangeaddrless()
{
    this->setGeometry(this->x(),this->y()-260,750,230);
}

void billchange::receivesendcan(int c, QString f, QString t, QString o, QString ti, QString m, QString i,QString b)
{
    count=c;
    ui->label_2->setText(f);
    ui->label_3->setText(t);
    ui->label_4->setText(ti);
    ui->label_5->setText(m);
    ui->label_6->setText(o);
    ui->label_7->setText(i);
    ui->label_8->setText(b);
}

int billchange::getcount()
{
    return count;
}
void billchange::on_pushButton_clicked()
{
    QString str = QString::number(count);
    QString buf="/woyaoquxiao/"+str;
    tcpClient->write(buf.toUtf8());
}

void billchange::received()
{
}


