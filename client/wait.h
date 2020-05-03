#ifndef WAIT_H
#define WAIT_H

#include <QDialog>

namespace Ui {
class wait;
}

class wait : public QDialog
{
    Q_OBJECT

public:
    explicit wait(QWidget *parent = 0);
    ~wait();
    void setcontent(QString,QString,QString);

private slots:
    void on_pushButton_clicked();

private:
    Ui::wait *ui;
};

#endif // WAIT_H
