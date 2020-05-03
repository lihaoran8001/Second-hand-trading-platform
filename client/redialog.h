#ifndef REDIALOG_H
#define REDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
namespace Ui {
class ReDialog;
}
class ReDialog : public QDialog {
    Q_OBJECT
public:
    explicit ReDialog(QWidget *parent = 0);
    ~ReDialog();
private slots:
    void on_insertButton1_clicked();
    void on_deleteButton1_clicked();
    void on_modifyButton1_clicked();
private:
    // 创建数据库
    void createDB (void);
    // 创建数据表
    void createTable (void);
    // 查询数据
    void queryTable (void);
private:
    QSqlDatabase db; // 建立QT程序和数据的连接
    QSqlQueryModel model; // 保存和遍历查询结果
private:
    Ui::ReDialog *ui;
};
#endif // REDIALOG_H
