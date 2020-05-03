#ifndef HAOPING_H
#define HAOPING_H

#include <QDialog>

namespace Ui {
class haoping;
}

class haoping : public QDialog
{
    Q_OBJECT

public:
    explicit haoping(QWidget *parent = 0);
    ~haoping();


private slots:
void on_pushButton_clicked();//一星按钮被点击

void on_pushButton_2_clicked();//二星按钮被点击

void on_pushButton_3_clicked();

void on_pushButton_4_clicked();//四星按钮被点击

void on_pushButton_5_clicked();//五星按钮被点击

void on_confirmButton_clicked();//确定按钮被点击

signals:
    void sendscore(int);

private:
    Ui::haoping *ui;
    int score;
};

#endif // HAOPING_H
