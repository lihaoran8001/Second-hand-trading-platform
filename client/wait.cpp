#include "wait.h"
#include "ui_wait.h"
#include "start.h"
wait::wait(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::wait)
{
    ui->setupUi(this);
}

wait::~wait()
{
    delete ui;
}

void wait::on_pushButton_clicked()
{
    this->close();
}

void wait::setcontent(QString i,QString c,QString p)
{
    ui->label_4->setText(i);
    ui->label_7->setText(c);
    ui->label_5->setText(p);
}
