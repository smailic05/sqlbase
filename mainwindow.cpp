#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QSqlRelation>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db= QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("postgres");
    db.setPort(5432);
    db.setUserName("postgres");
    db.setPassword("560047");
    if (!db.open())
    {
        QMessageBox::warning(this,"lol",db.lastError().text());
        qDebug()<<db.lastError().text();
        qDebug()<<"ffff";
    }

   model = new QSqlRelationalTableModel(this,db);
   model->setTable("smartphone");
   model->setRelation(model->fieldIndex("ID"),QSqlRelation("smart_photo","smart_id","url"));
   model->select();
   ui->tableView->setModel(model);
   ui->comboBox->setModel(model);
   ui->comboBox->setModelColumn(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_tableView_customContextMenuRequested(const QPoint &pos)
{
     QMenu * menu = new QMenu(this);
     QAction * remove= new QAction(trUtf8("удалить"),this);
     connect(remove,SIGNAL(triggered()),this,SLOT(slotRemove()));
     menu->addAction(remove);
     menu->popup(ui->tableView->viewport()->mapToGlobal(pos));
}

void MainWindow::on_submit_clicked()
{
    QString brand = ui->linebrand->text();
    QString modely = ui->linemodel->text();
    QString capacity = ui->linecapacity->text();
    QString diagonal = ui->linediagonal->text();
    QString price = ui->lineprice->text();
    qDebug()<<"insert into smartphone(brand,model,capacity,diagonal,price) values ('"+brand+"','"+modely+"',"+ capacity+","+diagonal+","+price+");";
    query.exec("insert into smartphone(brand,model,capacity,diagonal,price) values ('"+brand+"','"+modely+"',"+ capacity+","+diagonal+","+price+");");
    model->select();
}

void MainWindow::slotRemove()
{
    int row = ui->tableView ->selectionModel()->currentIndex().row();
    if (QMessageBox::warning(this,
                                     trUtf8("Удаление записи"),
                                     trUtf8("Вы уверены, что хотите удалить эту запись?"),
                                     QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
       {

           db.rollback();

        } else
    {
        if(!model->removeRow(row)){
                        QMessageBox::warning(this,trUtf8("Уведомление"),
                                             trUtf8("Не удалось удалить запись\n"
                                                    "Возможно она используется другими таблицами\n"
                                                    "Проверьте все зависимости и повторите попытку"));
    }
        model->select();
    }
}




void MainWindow::on_pushButton_clicked()
{
    QString urlstr= ui->lineUrl->text();
    QString idurl=ui->lineEdit->text();
    qDebug()<<"insert into smart_photo(url,smart_id) values ('"+urlstr+"',"+idurl+");";
    db.exec("insert into smart_photo(url,smart_id) values ('"+urlstr+"',"+idurl+");");
    model->select();
}
