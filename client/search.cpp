#include "search.h"
#include "ui_search.h"
#include "mainwindow.h"

search::search(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::search)
{
    ui->setupUi(this);
    Tcpclient=MainWindow::getSocketadd();
    cid=MainWindow::getCid();
}

search::~search()
{
    delete ui;
}

void search::on_cancelButton_clicked()
{
    this->close();
    emit showstart();
}

void search::on_confirmButton_clicked()
{
    QString from=ui->FromEdit->text();
    QString to=ui->ToEdit->text();
    QString c=QString::number(*cid);
    QString buffer="/search/"+c+"/"+from+"/"+to;
    Tcpclient->write(buffer.toUtf8());
    this->close();
    emit showstartc();
}
