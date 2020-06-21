#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlTableModel>
#include<QSqlRecord>
#include<QLineEdit>
#include<QDebug>
#include<QSqlError>
#include<QMenu>
#include<QAction>
#include<QMessageBox>
#include<QSqlRelationalTableModel>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_tableView_customContextMenuRequested(const QPoint &pos);

    void on_submit_clicked();

    void slotRemove();


    void on_pushButton_clicked();

private:
    QSqlRelationalTableModel* model;
    QSqlDatabase db;
    Ui::MainWindow *ui;
    QSqlQuery query = QSqlQuery(db);
};
#endif // MAINWINDOW_H
