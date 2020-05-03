#include "redialog.h"
#include "ui_redialog.h"

ReDialog::ReDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReDialog) {
    ui->setupUi(this);
    createDB ();
    createTable ();
    queryTable ();
}
ReDialog::~ReDialog() {
    delete ui;
}
//创建数据库文件 <=等价于=>  $: sqlite3 menu.db
void ReDialog::createDB (void) {
    // 建立和sqlite数据库的连接
    db = QSqlDatabase::addDatabase ("QSQLITE");
    // 设置数据库文件的名称
    db.setDatabaseName ("re.db");
    // 对数据库进行操作之前必须先打开数据库
    if (db.open () == false) {
        // 如果打开失败，弹出提示错误信息的信息窗口
        QMessageBox::critical (this, "Database open error", db.lastError ().text ());
    }
}
// 创建数据表
void ReDialog::createTable (void) {
    // 构建创建数据表sql语句的字符串
    QString str (
                "CREATE TABLE User(id INT PRIMARY KEY NOT NULL, name TEXT NOT NULL, zh TEXT NOT NULL, mm TEXT NOT NULL, mail TEXT NOT NULL)");
    // 执行sql语句
    QSqlQuery query;
    query.exec (str);
}
// 查询数据  <==>  SELECT * FROM ...
void ReDialog::queryTable (void) {
    // 构造一个查询数据表的sql语句
    QString str ("SELECT * FROM User");
    // 执行sql语句并保存结果到model
    model.setQuery (str);
    // 显示结果到ui
    ui->tableView1->setModel (&model);
}
// 插入按钮
void ReDialog::on_insertButton1_clicked() {
    // 获取用户输入的学号、姓名、账号 密码 邮箱
    int id = ui->idEdit1->text ().toInt ();
    QString name = ui->nameEdit1->text ();
    QString zh = ui->zhEdit->text ();
    QString mm = ui->mmEdit->text();
    QString mail = ui->mailEdit->text();

    // 构造插入操作的sql语句
    QString insertSql = QString (
         "INSERT INTO User VALUES(%1, '%2', '%3', '%4', '%5')").arg (id).arg (name).arg (zh).arg (mm).arg (mail);
    // 执行插入的sql语句
    QSqlQuery query;
    query.exec (insertSql);
    // 查询并显示
    queryTable ();
}
// 删除数据，根据ID删除 1 条数据
void ReDialog::on_deleteButton1_clicked() {
    int id = ui->idEdit1->text ().toInt ();
    QString deleteSql = QString (
                        "DELETE FROM User WHERE id = %1").arg (id);
    // 执行插入的sql语句
    QSqlQuery query;
    query.exec (deleteSql);
    // 查询并显示
    queryTable ();
}
// 修改数据，根据ID修改密码
void ReDialog::on_modifyButton1_clicked() {
    int id = ui->idEdit1->text ().toInt ();
    QString mm=ui->mmEdit->text();
    QString ModifySql = QString (
                        "UPDATE User SET mm = '%1' WHERE id = %2").arg (mm).arg (id);
    // 执行插入的sql语句
    QSqlQuery query;
    query.exec (ModifySql);
    // 查询并显示
    queryTable ();
}
