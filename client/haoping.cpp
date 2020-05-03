#include "haoping.h"
#include "ui_haoping.h"

haoping::haoping(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::haoping)
{
    ui->setupUi(this);
    score=0;
    ui->confirmButton->setEnabled(false);
}

haoping::~haoping()
{
    delete ui;
}

void haoping::on_pushButton_5_clicked()
{
    QPixmap *pixmap=new QPixmap(":/image/s4.png");
    pixmap->scaled(ui->label->size(),Qt::KeepAspectRatio);
    ui->label->setScaledContents(true);
    ui->label->setPixmap(*pixmap);
    score=-3;
    ui->confirmButton->setEnabled(true);
}

void haoping::on_pushButton_4_clicked()
{
    QPixmap *pixmap=new QPixmap(":/image/s5.png");
    pixmap->scaled(ui->label->size(),Qt::KeepAspectRatio);
    ui->label->setScaledContents(true);
    ui->label->setPixmap(*pixmap);
    score=-2;
    ui->confirmButton->setEnabled(true);
}

void haoping::on_pushButton_3_clicked()
{
    QPixmap *pixmap=new QPixmap(":/image/s6.png");
    pixmap->scaled(ui->label->size(),Qt::KeepAspectRatio);
    ui->label->setScaledContents(true);
    ui->label->setPixmap(*pixmap);
    score=-1;
    ui->confirmButton->setEnabled(true);
}

void haoping::on_pushButton_2_clicked()
{
    QPixmap *pixmap=new QPixmap(":/image/s7.png");
    pixmap->scaled(ui->label->size(),Qt::KeepAspectRatio);
    ui->label->setScaledContents(true);
    ui->label->setPixmap(*pixmap);
    score=0;
    ui->confirmButton->setEnabled(true);
}

void haoping::on_pushButton_clicked()
{
    QPixmap *pixmap=new QPixmap(":/image/s555.png");
    pixmap->scaled(ui->label->size(),Qt::KeepAspectRatio);
    ui->label->setScaledContents(true);
    ui->label->setPixmap(*pixmap);
    score=1;
    ui->confirmButton->setEnabled(true);
}

void haoping::on_confirmButton_clicked()
{
    emit sendscore(score);
    this->close();
}
