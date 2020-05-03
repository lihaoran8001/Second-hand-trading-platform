#ifndef SEARCH_H
#define SEARCH_H

#include <QDialog>
#include <QTcpSocket>

namespace Ui {
class search;
}

class search : public QDialog
{
    Q_OBJECT

public:
    explicit search(QWidget *parent = 0);
    ~search();

private slots:
    void on_cancelButton_clicked();
    void on_confirmButton_clicked();
signals:
    void showstart();
    void showstartc();
private:
    Ui::search *ui;
    QTcpSocket* Tcpclient;
    int* cid;
};

#endif // SEARCH_H
